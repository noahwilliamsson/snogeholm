/*
 * adlink.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 * 
 */

#include <gtk/gtk.h>
#include <gnome.h>
#include "support.h"
#include "interface.h"

#include "adlink.h"

#include "common.h"

volatile gboolean vrotor = TRUE;
volatile gboolean vrotor_signal = FALSE;
#define NO_IOCARD 1

gint adlink_open(void) {
	adlink_fd = open("/dev/adlink0", O_RDONLY);
	if(adlink_fd < 0) {
		g_print("Cannot open /dev/adlink0\n");
		return -1;
	}

	return 0;
}


gint adlink_output(u_char value, gint flag) {
	u_char tmp;

	switch(flag) {
		case ADLINK_SET:
		if(ioctl(adlink_fd, ADLINK_IOCTL_SET_OUT, &value) < 0)
			return -1;

		break;

		case ADLINK_ADD:
		if(ioctl(adlink_fd, ADLINK_IOCTL_STATUS_OUT, &tmp) < 0)
			return -1;

		tmp |= (value & 0xff);
		if(ioctl(adlink_fd, ADLINK_IOCTL_SET_OUT, &tmp) < 0)
			return -1;

		break;

		case ADLINK_VADD:
		if(ioctl(adlink_fd, ADLINK_IOCTL_STATUS_IN, &tmp) < 0)
			return -1;

		tmp |= (value & 0xff);
		if(ioctl(adlink_fd, ADLINK_IOCTL_SET_IN, &tmp) < 0)
			return -1;

		break;

		case ADLINK_CLEAR:
		if(ioctl(adlink_fd, ADLINK_IOCTL_STATUS_OUT, &tmp) < 0)
			return -1;

		/* XXX - detta funkar inte */
		tmp &= ~(value&0xff);
		if(ioctl(adlink_fd, ADLINK_IOCTL_SET_OUT, &tmp) < 0)
			return -1;

		break;

		case ADLINK_VCLEAR:
		if(ioctl(adlink_fd, ADLINK_IOCTL_STATUS_IN, &tmp) < 0)
			return -1;

		/* XXX - detta funkar inte */
		tmp &= ~(value&0xff);
		if(ioctl(adlink_fd, ADLINK_IOCTL_SET_IN, &tmp) < 0)
			return -1;

		break;
	}

	usleep(8000);

	return 0;
}


gint adlink_monitor(gpointer data) {
	static u_char status_saved = 0xff, diff, tmp;
	gchar buf[0xff];
	int i;
	struct timeval tv;
	static int counter = 0;

	if(counter++ == 4)
		counter = 0;

	if(ioctl(adlink_fd, ADLINK_IOCTL_STATUS_IN, &diff)) {
#ifndef NO_IOCARD
		g_print("adlink_monitor(): ioctl() on adlink_fd failed!\n");
		return FALSE;
#endif
	}

	if(debug) {
		if(ioctl(adlink_fd, ADLINK_IOCTL_STATUS_OUT, &tmp)) {
#ifndef NO_IOCARD
			g_print("adlink_monitor(): ioctl() on adlink_fd failed!\n");
			return FALSE;
#endif
		}

		/* Outputs */
		memset(buf, 0, sizeof(buf));
		for(i = 0; i < 8; i++) {
			sprintf(buf+strlen(buf), "%d ", 
				(tmp & (1<<i)) != 0);
		}

		gtk_label_set_text(GTK_LABEL(lblOutput), buf);


		/* Inputs */
		memset(buf, 0, sizeof(buf));
		for(i = 0; i < 8; i++) {
			sprintf(buf+strlen(buf), "%d ", 
				(diff & (1<<i)) != 0);
		}

		gtk_label_set_text(GTK_LABEL(lblInput), buf);
	}

#ifndef NO_IOCARD
	if(diff == status_saved)
		return TRUE;
#else
	if(!vrotor_signal)
		return TRUE;
#endif

	status_saved = diff;

	/*	g_print("adlink_monitor(): Status changed!\n"); */


	run->round++;


	/*
	 * XXX - Flera triggningar som inträffar under tiden
	 * rotoringången är satt kan leda till konstiga saker.
	 *
	 */


	if(run->rotor_on && ((diff & INPUT_ROTOR) || vrotor_signal)) {
		if(debug)
			g_print("-- Rotor input signal activity.\n");

		if(run->init_round < run->init_rounds)
			run->init_round++;
		else {
			if(run->init_round == run->init_rounds) {
				run->init_round++;
				gtk_statusbar_pop(GTK_STATUSBAR(sbStatus), run->rotor_cid);

				/* Checked in callback.c in mnRotorStoppa_activate().. */
				run->rotor_cid = 0;
				g_print("-- ROTOR: spinup klar, slapper pa strom till spannaren..\n");
				spannare((gpointer)0x01);
			}

			/* Sched next instruction if running */
			if(run->running)
				schedule_instruction();
		}

		gettimeofday(&tv, NULL);

		if(debug) {
			struct timeval diff;
			long dtime;

			dtime = 0;
			i = 0;
			if(run->tstat[0].tv_sec) {
				for(i = 0; i < 4 && run->tstat[i+1].tv_sec; i++) {
					diff = time_diff(run->tstat[i], run->tstat[i+1]);
					dtime += diff.tv_sec * 1000000;
					dtime += diff.tv_usec;

					run->tstat[i] = run->tstat[i+1];
				}

				diff = time_diff(run->tstat[i], tv);

				dtime += diff.tv_sec * 1000000;
				dtime += diff.tv_usec;

				diff.tv_usec = (dtime % 1000000) / (i+1);
				diff.tv_usec /= 10000;
				diff.tv_sec = (dtime / 1000000) / (i+1);

				sprintf(buf, "%lus%02lu", diff.tv_sec, diff.tv_usec);
				gtk_label_set_text(GTK_LABEL(lblTiming), buf);
	
			}

			run->tstat[i] = tv;
		}
	}
		


	return TRUE;
}


gint virt_rotor_trigger(gpointer data) {
#if 0
	u_char a;

	a = INPUT_ROTOR;
	ioctl(adlink_fd, ADLINK_IOCTL_SET_IN, &a);
#endif

	vrotor_signal = TRUE;
	g_print("virt_rotor_trigger(): signal == TRUE for 70ms\n");
	gtk_timeout_add(70, virt_rotor_trigger_off, NULL);
	return vrotor;
}


gint virt_rotor_trigger_off(gpointer data) {
	g_print("virt_rotor_trigger_off(): signal == FALSE\n");
	vrotor_signal = FALSE;

	return FALSE;
}


gint spannare(gpointer data) {
	if((long)data == 1)
		adlink_output(OUTPUT_SPANNARE, ADLINK_ADD);
	else
		adlink_output(OUTPUT_SPANNARE, ADLINK_CLEAR);

	return 0;
}
