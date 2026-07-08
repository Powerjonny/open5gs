/*
 * Copyright (C) 2022 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ogs-core.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int ogs_file_read_full(
        const char *filename, void *buf, size_t nbytes, size_t *bytes_read)
{
    FILE *fp = NULL;
    size_t total_read = 0, amt;

    ogs_assert(filename);
    ogs_assert(buf);
    ogs_assert(nbytes);

    fp = fopen(filename, "rb");
    if (!fp) {
        ogs_error("Cannot find file [%s]", filename);
        return OGS_ERROR;
    }

    amt = fread(buf, 1, nbytes, fp);

    if (bytes_read != NULL)
        *bytes_read = amt;

    fclose(fp);

    if (amt > 0)
        return OGS_OK;

    ogs_error("Cannot read file [name:%s,amt:%d,total_read:%d]",
            filename, (int)amt, (int)total_read);
    return OGS_ERROR;
}

int ogs_file_open(const char *filename, ogs_file_t *file)
{
	ogs_assert(filename);
	ogs_assert(file);

	/* If file is still open, close it first */
	if(*file >= 0)
	{
		ogs_file_close(file);
	}

	/* Open target file with rw permissions */
	if((*file = open(filename, O_RDWR | O_CREAT | O_EXCL, 0660)) < 0)
	{
		/* File can not be created, because it still exists.
		   Open in append mode... . */
		if((*file = open(filename, O_RDWR | O_APPEND)) < 0)
		{
			ogs_error("Can not open file [%s]: %s.", filename, strerror(errno));
			return OGS_ERROR;
		}
	}

	return OGS_OK;
}

void ogs_file_close(ogs_file_t *file)
{
	ogs_assert(file);

	if(*file < 0)
	{
		return;
	}

	/* Synchronize cached data with underlying file system */
	sync();

	close(*file);
	*file = -1;
}

ssize_t ogs_file_write(ogs_file_t file, void *buf, size_t nbytes)
{
	ssize_t rbytes = 0, written = 0;
	uint8_t *ptr = (uint8_t*) buf;

	ogs_assert(buf);
	ogs_assert(nbytes);

	/* Check is target file is valid */
	if(file < 0)
	{
		ogs_warn("Invalid file descriptor received for writing. Do nothing.");
		return 0;
	}

	do
	{
again:
		rbytes = write(file, ptr + written, nbytes - written);
		if(rbytes < 0)
		{
			if(errno == EINTR)
			{
				goto again;
			}
			else
			{
				ogs_error("Error during writing %ld/%ld B to file: %s.", written, nbytes, strerror(errno));
				return written;
			}
		}

		else if(!rbytes)
		{
			break;
		}

		written += rbytes;

	} while(written < nbytes);

	return written;
}

int ogs_file_get_size(ogs_file_t file)
{
	struct stat st;

	memset(&st, 0, sizeof(st));
	if(fstat(file, &st) < 0)
	{
		ogs_error("File size could not be determined: %s.", strerror(errno));
		return -1;
	}

	return st.st_size;
}

int ogs_file_get_lines(ogs_file_t file)
{
	FILE *stream = NULL;
	int lines = 0;
	int fd;
	char buf[1024];

	/* Duplicate file descriptor and convert it to FILE stream */
	if((fd = dup(file)) < 0 || (stream = fdopen(fd, "r+")) == NULL)
	{
		ogs_error("Error during ogs_file_get_lines(): %s.", strerror(errno));
		return -1;
	}

	/* Set position to the beginning of the file */
	rewind(stream);

	/* Count lines via fgets(3) */
	while(fgets(buf, sizeof(buf), stream) != NULL)
	{
		lines++;
	}

	/* Close stream */
	fclose(stream);

	return lines;
}
