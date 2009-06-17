/*
 * elev.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 */

#include <gtk/gtk.h>
#include <gnome.h>
#include "support.h"
#include "interface.h"

#include "common.h"

#define MID_TO 1600
#define END_TO	3000


gint elev_change(int val) {

	if(val == run->elev_state)
		return 0;

	if(run->flags & I_LOCKED) {
		g_print("======= PROGRAM BUG ====: elev_change(%d) when LOCKED!!!! ====\n", val);
		return -1;
	}

	run->flags |= I_LOCKED;
	switch(val) {
		case ELEV_UP:
		adlink_output(OUTPUT_ELEV_UP, ADLINK_ADD);
		gtk_timeout_add(END_TO, elev_done, (gpointer)OUTPUT_ELEV_UP);
		break;

		case ELEV_DN:
		adlink_output(OUTPUT_ELEV_DN, ADLINK_ADD);
		gtk_timeout_add(END_TO, elev_done, (gpointer)OUTPUT_ELEV_DN);
		break;

		case ELEV_MD:
		g_print("-- state == %d -> %d\n", run->elev_state,  run->elev_state & ELEV_UP? ELEV_DN: ELEV_UP);

		if(run->elev_state == ELEV_DN) {
			adlink_output(OUTPUT_ELEV_UP, ADLINK_ADD);
			gtk_timeout_add(MID_TO, elev_done, (gpointer)OUTPUT_ELEV_UP);
		}
		else {
			adlink_output(OUTPUT_ELEV_DN, ADLINK_ADD);
			gtk_timeout_add(MID_TO, elev_done, (gpointer)OUTPUT_ELEV_DN);
		}

		break;

		default:
		g_print("-- elev_change(): invalid value\n");
		run->flags &= ~I_LOCKED;
		return 0;
		break;
	}

	printf("-- elev_change(%d): Elevation change in progress.. \n", val);
	run->elev_state = val;
	return 0;
}


gint elev_done(gpointer data) {


	/* What about.. OUTPUT_ELEV_DN|OUTPUT_ELEV_UP ? */
	adlink_output((gint)data & 0xff, ADLINK_CLEAR);

	printf("-- elev_done(): Elevation changed. Unlocking..\n");
	run->flags &= ~I_LOCKED;

	return FALSE;
}
