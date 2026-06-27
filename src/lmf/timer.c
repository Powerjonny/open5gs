/*
 * Copyright (C) 2025 by Juraj Elias <juraj.elias@gmail.com>
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

#include "timer.h"
#include "context.h"

static lmf_timer_cfg_t g_lmf_timer_cfg[MAX_NUM_OF_LMF_TIMER] = {
	/* USER PLANE CONNECTION RELEASE COMMAND sent */
    [LMF_TIMER_T5010] =
        { .have = true, .max_count = 4, .duration = ogs_time_from_sec(16) },
    /* USER PLANE CONNECTION ESTABLISHMENT COMMAND sent */
    [LMF_TIMER_T5012] =
        { .have = true, .max_count = 4, .duration = ogs_time_from_sec(10) }, /* can be re-defined via configuration file */
	/* USER PLANE CONNECTION MODIFICATION COMMAND sent */
    [LMF_TIMER_T5015] =
        { .have = true, .max_count = 4, .duration = ogs_time_from_sec(16) },
	/* Inactivity timer for an established LCS user plane connection */
	[LMF_TIMER_INACTIVITY] =
		{ .have = true, .max_count = 1, .duration = ogs_time_from_sec(10) }, /* can be re-defined via configuration file */
};

lmf_timer_cfg_t *lmf_timer_cfg(lmf_timer_e id)
{
    ogs_assert(id < MAX_NUM_OF_LMF_TIMER);
    if (g_lmf_timer_cfg[id].have != true) {
        ogs_fatal("No timer[%d] configuration", id);
        ogs_assert_if_reached();
    }
    return &g_lmf_timer_cfg[id];
}


const char *lmf_timer_get_name(int timer_id)
{
    switch(timer_id) {
    case LMF_TIMER_SBI_CLIENT_WAIT:
        return "LMF_TIMER_SBI_CLIENT_WAIT";
    case LMF_TIMER_LOCATION_REQUEST_TIMEOUT:
        return "LMF_TIMER_LOCATION_REQUEST_TIMEOUT";

	case LMF_TIMER_T5010:
        return "LMF_TIMER_T5010";
	case LMF_TIMER_T5012:
		return "LMF_TIMER_T5012";
	case LMF_TIMER_T5015:
        return "LMF_TIMER_T5015";
	case LMF_TIMER_INACTIVITY:
		return "LMF_TIMER_INACTIVITY";

    default:
        break;
    }

    return "UNKNOWN_TIMER";
}

/*
 * This function sends an event to the lmf-sm state machine -> there, it is forwarded to the UPP state machine
 * ... this working principle is adopted from the AMF implementation (src/amf/timer.*).
 */
static void upp_timer_event_send(
        lmf_timer_e timer_id, void *data)
{
    int rv;
    lmf_event_t *e = NULL;

    ogs_assert(data);

    e = lmf_event_new(LMF_EVENT_UPP_TIMER);
    ogs_assert(e);
    e->h.timer_id = timer_id;
    e->binding_id = OGS_POINTER_TO_UINT(data); //ID of LCS-UP context

    rv = ogs_queue_push(ogs_app()->queue, e);
    if (rv != OGS_OK) {
        ogs_error("ogs_queue_push() failed:%d in %s",
                (int)rv, lmf_timer_get_name(timer_id));
        ogs_event_free(e);
    }
}

/*
 * Callback function that is called when the timer T5010 has expired.
 */
void lmf_timer_t5010_expire(void *data)
{
    upp_timer_event_send(LMF_TIMER_T5010, data);
}

/*
 * Callback function that is called when the timer T5012 has expired.
 */
void lmf_timer_t5012_expire(void *data)
{
	upp_timer_event_send(LMF_TIMER_T5012, data);
}

/*
 * Callback function that is called when the timer T5015 has expired.
 */
void lmf_timer_t5015_expire(void *data)
{
    upp_timer_event_send(LMF_TIMER_T5015, data);
}

/*
 * Callback function that is invoked when an active LCS-UP connection is too long in idle state.
 */
void lmf_timer_inactivity_expire(void *data)
{
	upp_timer_event_send(LMF_TIMER_INACTIVITY, data);
}
