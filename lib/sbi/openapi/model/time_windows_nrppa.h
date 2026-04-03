/*
 * time_windows_nrppa.h
 *
 * Time windows when network assisted positioning is used.
 */

#ifndef _OpenAPI_time_windows_nrppa_H_
#define _OpenAPI_time_windows_nrppa_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_time_windows_nrppa_s OpenAPI_time_windows_nrppa_t;
typedef struct OpenAPI_time_windows_nrppa_s {
	char *measurement_list;
	char *srs_list;
} OpenAPI_time_windows_nrppa_t;

OpenAPI_time_windows_nrppa_t *OpenAPI_time_windows_nrppa_create(
	char *measurement_list, char *srs_list);
void OpenAPI_time_windows_nrppa_free(
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa);
OpenAPI_time_windows_nrppa_t *OpenAPI_time_windows_nrppa_parseFromJSON(
	cJSON *time_windows_nrppaJSON);
cJSON *OpenAPI_time_windows_nrppa_convertToJSON(
	OpenAPI_time_windows_nrppa_t *time_windows_nrppa);
OpenAPI_time_windows_nrppa_t *OpenAPI_time_windows_nrppa_copy(
	OpenAPI_time_windows_nrppa_t *dst, OpenAPI_time_windows_nrppa_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_time_windows_nrppa_H_ */
