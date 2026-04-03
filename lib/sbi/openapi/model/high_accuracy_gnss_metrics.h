/*
 * high_accuracy_gnss_metrics.h
 *
 * High Accuracy GNSS Positioning Metrics.
 */

#ifndef _OpenAPI_high_accuracy_gnss_metrics_H_
#define _OpenAPI_high_accuracy_gnss_metrics_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "fix_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_high_accuracy_gnss_metrics_s
        OpenAPI_high_accuracy_gnss_metrics_t;
typedef struct OpenAPI_high_accuracy_gnss_metrics_s {
	bool is_nr_of_used_satellites;
	int nr_of_used_satellites;
	bool is_hdopi;
	int hdopi;
	bool is_pdopi;
	int pdopi;
	bool is_age;
	int age;
	OpenAPI_fix_type_e fix_type;
} OpenAPI_high_accuracy_gnss_metrics_t;

OpenAPI_high_accuracy_gnss_metrics_t *OpenAPI_high_accuracy_gnss_metrics_create(
	bool is_nr_of_used_satellites, int nr_of_used_satellites, bool is_hdopi,
	int hdopi, bool is_pdopi, int pdopi, bool is_age, int age,
	OpenAPI_fix_type_e fix_type);
void OpenAPI_high_accuracy_gnss_metrics_free(
	OpenAPI_high_accuracy_gnss_metrics_t *high_accuracy_gnss_metrics);
OpenAPI_high_accuracy_gnss_metrics_t *
OpenAPI_high_accuracy_gnss_metrics_parseFromJSON(
	cJSON *high_accuracy_gnss_metricsJSON);
cJSON *OpenAPI_high_accuracy_gnss_metrics_convertToJSON(
	OpenAPI_high_accuracy_gnss_metrics_t *high_accuracy_gnss_metrics);
OpenAPI_high_accuracy_gnss_metrics_t *OpenAPI_high_accuracy_gnss_metrics_copy(
	OpenAPI_high_accuracy_gnss_metrics_t	*dst,
	OpenAPI_high_accuracy_gnss_metrics_t	*src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_high_accuracy_gnss_metrics_H_ */
