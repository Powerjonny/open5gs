#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "n1_n2_mess_transfer_error_reply.h"

char * OpenAPI_n1_n2_mess_transfer_error_reply_ToString(
	OpenAPI_n1_n2_mess_transfer_error_reply_e
	n1_n2_mess_transfer_error_reply) {
	const char *n1_n2_mess_transfer_error_replyArray[] = { "NULL",
		                                               "UE_NOT_REACHABLE",
		                                               "UNSPECIFIED" };
	size_t sizeofArray = sizeof(n1_n2_mess_transfer_error_replyArray) /
	                     sizeof(n1_n2_mess_transfer_error_replyArray[0]);
	if(n1_n2_mess_transfer_error_reply < sizeofArray) {
		return (char *) n1_n2_mess_transfer_error_replyArray[
			n1_n2_mess_transfer_error_reply];
	} else {
		return (char *) "Unknown";
	}
}

OpenAPI_n1_n2_mess_transfer_error_reply_e
OpenAPI_n1_n2_mess_transfer_error_reply_FromString(
	char *n1_n2_mess_transfer_error_reply) {
	int stringToReturn = 0;
	const char *n1_n2_mess_transfer_error_replyArray[] = { "NULL",
		                                               "UE_NOT_REACHABLE",
		                                               "UNSPECIFIED" };
	size_t sizeofArray = sizeof(n1_n2_mess_transfer_error_replyArray) /
	                     sizeof(n1_n2_mess_transfer_error_replyArray[0]);
	while(stringToReturn < sizeofArray) {
		if(strcmp(n1_n2_mess_transfer_error_reply,
		          n1_n2_mess_transfer_error_replyArray[stringToReturn])
		   == 0) {
			return stringToReturn;
		}
		stringToReturn++;
	}
	return 0;
}
