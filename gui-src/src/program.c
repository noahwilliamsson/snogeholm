/*
 * program.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */

#include <gtk/gtk.h>
#include <gnome.h>
#include "support.h"
#include "interface.h"

#include "program.h"

#include "common.h"


void program_init(void) {
	char buf[0xff];
	struct stat st;


	/* XXX - ... */
	sprintf(buf, "%s/.slim", getenv("HOME"));

	if(stat(buf, &st))
		mkdir(buf, S_IRWXU);
	else if(!S_ISDIR(st.st_mode)) {
		unlink(buf);
		mkdir(buf, S_IRWXU);
	}

	chdir(buf);
}


int program_save(GtkWidget *clist, gchar *name) {
	gchar *buf;
	gchar entry[0xff];
	int col, row, row_found = 1;
	FILE *fd;


	fd = fopen(name, "wt");
	if(!fd) {
		g_print("-- program_save: unable to save file (%s)\n", name);
		/* XXX - poppa upp err ruta! */
		return 0;
	}

	g_print("-- program_save: clist=%p\n", clist);


	/* XXX - fulhack! Max 1024 rader */
	for(row = 0; row < 1024; row++) {
		memset(entry, 0, 0xff);
		for(col = 0; col < 3; col++) {
			row_found = gtk_clist_get_text(GTK_CLIST(clist), row, col, &buf);
			if(col == 0 && !strcmp(buf, "Lägg"))
				row_found = 0;

			if(!row_found)
				break;

			sprintf(entry+strlen(entry), "%s|", buf);
		}

		if(!row_found)
			break;

		entry[strlen(entry)-1] = '\n';
		g_print("-- entry:%s", entry);
		fputs(entry, fd);
	}

	fclose(fd);
	if(!row) {
		unlink(name);
		return -1;
	}

	return 1;
}


void program_load(gchar *name, GtkWidget *clist) {
	gchar buf[1024], skytt[0xff], elev[0xff];
	int value;
	
	FILE *fd;


	fd = fopen(name, "rt");
	if(!fd) {
		/* XXX - poppa upp ngt och gnäll */
		/* Bör iofs inte kunna hända.
		 * rescan() borde kolla om man har read permz på den */

		g_print("-- program_load(): fopen() failed\n");
		return;
	}

	if(clist)
		gtk_clist_clear(GTK_CLIST(clist));

	if(run->program) {
		free(run->program);
		run->program = NULL;
	}

	do {
		memset(buf, 0, sizeof(buf));
		if(!fgets(buf, sizeof(buf)-1, fd))
			break;

		sscanf(buf, "%[^|]|%[^|]|%i\n", skytt, elev, &value);
		if(*skytt == 'P')
			*skytt = 0;
		else if(*skytt >= '1' && *skytt <= '8')
			*skytt -= '0';
		else if(*skytt >= 'A' && *skytt <= 'H')
			*skytt -= 'A' - 8;
		else {
			g_print("-- program_load(): INVALID LINE: %s|%s|%d\n", skytt, elev, value);
			continue;
		}

		if(!run->program) {
			run->program = (PROGRAM *)calloc(1, sizeof(PROGRAM));
			run->tot_instructions = 1;
		}
		else {
			run->tot_instructions++;
			run->program = (PROGRAM *)realloc(run->program, sizeof(PROGRAM)*(run->tot_instructions));
		}


		run->program[run->tot_instructions - 1].id = *skytt;

		if(*elev == 'L')
			run->program[run->tot_instructions - 1].elev = ELEV_DN;
		else if(*elev == 'M')
			run->program[run->tot_instructions - 1].elev = ELEV_MD;
		else
			run->program[run->tot_instructions - 1].elev = ELEV_UP;

		run->program[run->tot_instructions - 1].value = value;
			

		if(clist) {
			gchar buf[0xff], *values[3];

			if(*skytt == 0)
				sprintf(buf, "Paustid");
			else
				sprintf(buf, "%c", *skytt <= 8? *skytt + '0'
					: *skytt - 8 + 'A');
			values[0] = strdup(buf);


			if(run->program[run->tot_instructions - 1].elev == ELEV_DN)
				sprintf(buf, "Låg");
			else if(run->program[run->tot_instructions - 1].elev == ELEV_MD)
				sprintf(buf, "Mitten");
			else
				sprintf(buf, "Hög");

			values[1] = strdup(buf);

			sprintf(buf, "%d", run->program[run->tot_instructions - 1].value);
			values[2] = strdup(buf);

			gtk_clist_append(GTK_CLIST(clist), values);

			free(values[0]);
			free(values[1]);
			free(values[2]);
			values[0] = NULL;
		}

/*
		if(debug) {
			g_print("-- load(%d:%s:%d)\n", *skytt, elev, value);
			g_print("  `-- id:%d elev:%d value:%d\n", 
				run->program[run->tot_instructions - 1].id,
				run->program[run->tot_instructions - 1].elev, 
				run->program[run->tot_instructions - 1].value);
		}
*/

	} while(1);

	if(clist) {
		gchar *str[] = { "Lägg", "till", "ny rad" };
		gtk_clist_append(GTK_CLIST(clist), str);
	}
}


void program_rescan(GtkWidget *omMenu) {
	char buf[1024];
	DIR *dir;
	struct dirent *de;
	GtkWidget *item;
	GtkWidget *menu;


	sprintf(buf, "%s/.slim", getenv("HOME"));
	dir = opendir(buf);
	if(!dir) {
		g_print("-- program_rescan: opendir() failed!\n");
		return;
	}

	/* Remove old menu.. */
	menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(omMenu));
        gtk_menu_detach(GTK_MENU(menu));
	menu = gtk_menu_new();

	while((de = readdir(dir))) {
		if(de->d_type & ~(DT_REG|DT_LNK))
			continue;

		/* XXX - ugly hack :) */
		if(strstr(de->d_name, ".xpm"))
			continue;

		/* Add menu item */
		item = gtk_menu_item_new_with_label(de->d_name);

		gtk_signal_connect(GTK_OBJECT(item), "activate", 
				 GTK_SIGNAL_FUNC(on_omPrograms_activated), 
				 (gpointer)strdup(de->d_name));

		gtk_widget_show(item);

		gtk_menu_append(GTK_MENU(menu), item);

		if(debug)
			g_print("-- program_rescan: adding %s\n", de->d_name);
	}

	closedir(dir);

	/* Install new menuitems */
	gtk_option_menu_set_menu(GTK_OPTION_MENU(omMenu), menu);
}


void schedule_instruction(void) {
	gint to, next_to;	/* timeout */
	static gint shoot_diff = -0xff;
	gchar tmp[0xff];
	gchar *text[1];


	/*
	 * Kolla om föregående instruction är körd 
	 * genom run->flags & INST_PROCESSED eller ngt.. 
	 * Om id == 0, så ska inte exec köras utan ngt som resetar
	 * run->flags igen.. 
	 *
	 */

	if((run->flags & I_PENDING) 
		|| (run->flags & I_LOCKED)
		|| (run->flags & I_NOOP))
		return;


	if(run->program == NULL) {
		g_print("sched(): program == NULL $!@#\n");
		return;
	}


	if(shoot_diff == -0xff) {
		if(config_get("shoot_diff"))
			shoot_diff = atoi(config_get("shoot_diff"));
		else
			shoot_diff = 0;
	}


	if(run->program[run->instruction].elev != run->elev_state) {
		g_print("-- sched(%d): Changing elevation to %d\n",
			run->round, run->program[run->instruction].elev);
		elev_change(run->program[run->instruction].elev);
		return;
	}


	run->flags |= I_PENDING;


	/* --- BIG XXX ---- detta SKAPAR konflikt med dual_exec$!@# */


	/* Previous instruction executed, load next one */
	
	if(!run->value) {

		/* Decreased in exec_done() */
		if(!(run->value = run->program[run->instruction].value)) {
			g_print("schedule(): Invalid instruction$!@#. Shouldn't  happen!\n");
			run->instruction++;
			run->flags &= ~I_PENDING;
			return;
		}
	}


	/* Pause instruction */
	if(run->program[run->instruction].id == 0) {
		to = run->program[run->instruction].value;
		run->value = 1;
		run->pend_instructions++;
		gtk_timeout_add(to, exec_done, (gpointer)0x42);
		g_print("-- schedule_instruction(%d): Pausing %dms\n", run->round, to);

		return;
	}
	else if(run->program[run->instruction].id <= 8)
		to = (run->program[run->instruction].id - 1) * (2000/8) + shoot_diff;
	else
		to = (run->program[run->instruction].id - 8 - 1) * (2000/8) + (2000/16) + shoot_diff;




	next_to = try_optimize(to);
	g_print("-- schedule_instruction(%d): Timeout is %dms (skytt=%d, %d shots left)\n", 
		run->round, to, run->program[run->instruction].id, run->value);


	/* Update the red/green arcs in the main window */
	vis_update();


	run->pend_instructions++;
	gtk_timeout_add(to, exec_instruction, NULL);
	if(next_to) {
		run->pend_instructions++;
		gtk_timeout_add(next_to, exec_instruction, NULL);
		g_print("-- sched(%d): Optimze succeeded, to=%dms next_to=%dms\n", run->round, to, next_to);
	}
	else {
//		g_print("-- sched(%d): Optimize failed!\n", run->round);
	}



	/* XXX - nyfixat! */
	sprintf(tmp, "id=%d to=%d skytt=%d left=%d",
			run->instruction, to, 
			run->program[run->instruction].id,
			run->value);

	text[0] = strdup(tmp);
	g_print("%s\n", tmp);

	gtk_clist_prepend(GTK_CLIST(clInfo), text);
	free(text[0]);

			

/* XXX - nyfixat */
#if	0
	{
		int s, e;
		int to1, to2;

		if(run->program[run->instruction].id <= 9)
			to1 = run->program[run->instruction].id * (2000/8);
		else
			to1 = (run->program[run->instruction].id - 10) * (2000/8) + (2000/16);

		if(run->program[run->instruction+1].id <= 9)
			to2 = run->program[run->instruction+1].id * (2000/8);
		else
			to2 = (run->program[run->instruction+1].id - 10) * (2000/8) + (2000/16);


		if(((2000-to1) + to2) < 1500) {
			g_print("sched(): locking (NOOP), t/o diff < 1500\n");
			run->flags |= I_NOOP;

			/* Reset NOOP flag */
			gtk_timeout_add(to+1500, exec_done, (gpointer)0x9090);
		}

		if(run->value == 1) {
			e = run->program[run->instruction+1].elev;
			s = run->program[run->instruction+1].id;
		}
		else {
			e = run->program[run->instruction].elev;
			s = run->program[run->instruction].id;
		}

		g_print("-- schedule_instruction(): Nästa instruktion: "
			"skytt=%d elev=%d\n", s, e);
		/* XXX - nyfixat! */
		sprintf(tmp, "Skytt(%d): %d shots left.",
				run->program[run->instruction].id,
				run->value);

		text[0] = strdup(tmp);
		gtk_clist_prepend(GTK_CLIST(clInfo), text);
		free(text[0]);
	}
#endif

}


gint try_optimize(gint timeout) {
	gint elev1, elev2;
	gint offset;
	gint next_to;
	static gint shoot_diff = -0xff;


	/*
	 * if there's no subinstructions left (run->value == 1) 
	 *  except this one, two things are possible.
	 *
	 *  1. We might be able to process two instructions 
	 *     this round.
	 *  2. We might need to set NOOP flag if id == 8 this 
	 *     round and id == 1 next round.
	 *
	 */
		
	   
	/* offset to next instruction (0 or 1) */
	offset = (run->value - 1 == 0);
	
	/* If subinstructions left or end-of-program - return 0 */
	if(!offset || (offset && run->instruction + offset >= run->tot_instructions)) {
		g_print("-- optimize: subinstructions or e-o-p\n");
		return 0;
	}


	elev1 = run->program[run->instruction].elev;
	elev2 = run->program[run->instruction+offset].elev;

	/* changing elev requires at least one round */
	if(elev1 != elev2) {
		g_print("-- optimize: different elevations\n");
		return 0;
	}



	if(shoot_diff == -0xff) {
		if(config_get("shoot_diff"))
			shoot_diff = atoi(config_get("shoot_diff"));
		else
			shoot_diff = 0;
	}


	if(run->program[run->instruction+offset].id == 0) {
		g_print("-- optimize: pause instruction!\n");
	
		/* Pause - we can't optimize */
		return 0;
	}
	else if(run->program[run->instruction+offset].id <= 9)
		next_to = run->program[run->instruction+offset].id * (2000/8) + shoot_diff;
	else
		next_to = (run->program[run->instruction+offset].id - 10) * (2000/8) + (2000/16) + shoot_diff;

	if(timeout <= next_to) {

		g_print("-- optimize: dualexec=%d reload_time=%d\n", run->dual_execute, run->reload_time);
		/* We might be able to fire two times this round */
		if((next_to - timeout) > run->reload_time && run->dual_execute)
			/* Return the timeout value */
			return next_to;
	}
	else {
		/* We might need to block further processing
		   for a while  */
		if((timeout - next_to) < run->reload_time) {
			run->flags |= I_NOOP;

			/* Reset NOOP flag */
			gtk_timeout_add(timeout + run->reload_time, exec_done, (gpointer)0x9090);
			g_print("-- BLOCKED %dms!\n", timeout + run->reload_time);
		}

		g_print("-- optimize: no blocking needed\n");
	}


	return 0;
}


gint exec_instruction(gpointer data) {

/*
 * Om run->instruction + 1 == total_instructions
 * så kan vi använda spännaren för att skjuta sista
 * skottet.
 *
 */
	/* Programmet kan ha blivit återställt! */
	if(!run->program)
		return FALSE;


	g_print("-- exec_instruction(%d): SHOOT [in=%d:%d tot=%d]\n", run->round,
		run->instruction, run->program[run->instruction].value, run->tot_instructions);
	adlink_output(OUTPUT_SHOOT, ADLINK_ADD);

	/* Reset SHOOT output */
	gtk_timeout_add(50, exec_done, NULL);

	/* As we only want this to happen once, return FALSE */
	return FALSE;
}


gint exec_done(gpointer data) {

	/* Normal instruction, no pause */
	if(data == NULL) {
		g_print("-- exec_done(%d): DONE: ", run->round);
		adlink_output(OUTPUT_SHOOT, ADLINK_CLEAR);



		/* XXX - hack */
		g_print("i=%d tot=%d skytt=%d val=%d\n", run->instruction, run->tot_instructions, run->program[run->instruction].id, run->program[run->instruction].value);

		if(run->instruction + 1 == run->tot_instructions 
		   && run->program[run->instruction].value == 1) {
			g_print("-- exec_done(): CLEAR OUTPUT_SPANNARE\n");
			adlink_output(OUTPUT_SPANNARE, ADLINK_CLEAR);
			vis_update();
		}
	}


	/* XXX - tänk efter om vad som händer om 
	  den ordinarie exec_done råkar resetta I_NOOP innan 
	  timeout funktionen gör det? */


	if((run->flags & I_NOOP) && data == (gpointer)0x9090) {
		g_print("-- UNBLOCKED\n");
		run->flags &= ~I_NOOP;
		g_print("NOOP\n");
		return FALSE;
	}



	/* Clear the flag if there's no pending
	   instructions left this round. */

	run->pend_instructions--;
	if(!run->pend_instructions)
		run->flags &= ~I_PENDING;


	run->value--;
	if(!run->value)
		run->instruction++;

	if(run->instruction >= run->tot_instructions) {
		/* XXX - Sag till pa ngt vis att korning ar klar */
		/* XXX - kan inte poppa upp ruta i den hdr funktion om detta! */

		/* Clean up red/green arcs */
		vis_update();

		gtk_menu_item_activate(GTK_MENU_ITEM(mnProgramReset));
	}


	return FALSE;
}


struct timeval time_diff(struct timeval a, struct timeval b) {
	struct timeval diff;

	if(a.tv_usec > b.tv_usec) {
		diff.tv_usec = 1000000 - a.tv_usec + b.tv_usec;
		diff.tv_sec = b.tv_sec - a.tv_sec - 1;
	}
	else {
		diff.tv_usec = b.tv_usec - a.tv_usec;
		diff.tv_sec = b.tv_sec - a.tv_sec;
	}

/*	g_print("-- time_diff(): %lus%luu\n", diff.tv_sec, diff.tv_usec); */
	return diff;
}
