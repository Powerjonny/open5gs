/*
 * add_location_datas.h
 *
 * Additional Location Data.
 */

#ifndef _OpenAPI_add_location_datas_H_
#define _OpenAPI_add_location_datas_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "location_data.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_add_location_datas_s OpenAPI_add_location_datas_t;
typedef struct OpenAPI_add_location_datas_s {
	OpenAPI_list_t *add_location_datas;
} OpenAPI_add_location_datas_t;

OpenAPI_add_location_datas_t *OpenAPI_add_location_datas_create(
	OpenAPI_list_t *add_location_datas);
void OpenAPI_add_location_datas_free(
	OpenAPI_add_location_datas_t *add_location_datas);
OpenAPI_add_location_datas_t *OpenAPI_add_location_datas_parseFromJSON(
	cJSON *add_location_datasJSON);
cJSON *OpenAPI_add_location_datas_convertToJSON(
	OpenAPI_add_location_datas_t *add_location_datas);
OpenAPI_add_location_datas_t *OpenAPI_add_location_datas_copy(
	OpenAPI_add_location_datas_t *dst, OpenAPI_add_location_datas_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_add_location_datas_H_ */
