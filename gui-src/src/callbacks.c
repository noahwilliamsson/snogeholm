/*
 * callbacks.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "common.h"



void update_skytt_stats(void);

extern volatile gboolean vrotor;

void on_mainwin_destroy(GtkObject *object, gpointer user_data) {

	on_mnExitProgram_activate(NULL, NULL);
}


gboolean on_progwin_delete_event(GtkWidget *widget, GdkEvent *event,
				 gpointer user_data) {

	gtk_button_clicked(GTK_BUTTON(btnProgexit));
	return TRUE;
}


void on_btnProgexit_clicked(GtkButton *button, gpointer user_data) {

	g_print("Progexit: hiding progwin!\n");
	gtk_widget_hide(progwin);

	program_rescan(omPrograms);
}


void on_clProgNew_select_row(GtkCList *clist, gint row, gint column,
				GdkEvent *event, gpointer user_data) {
	gchar *buf;
	gchar id[10];
	int value;
	GtkWidget *menu;

	if(event && !(event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS))
		return;

	gtk_clist_get_text(GTK_CLIST(clProgNew), row, column, &buf);
	g_print("Row/Col[%d/%d]: Clicked twice. Text[%s]\n", row , column, buf);


	gtk_clist_get_text(GTK_CLIST(clProgNew), row, 0, &buf);
	if(strcmp(buf, "Lägg")) {
		menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(omSkytt));
		if(*buf >= '1' && *buf <= '8') {
			gtk_option_menu_set_history(GTK_OPTION_MENU(omSkytt), *buf - '1');
			gtk_menu_set_active(GTK_MENU(menu), *buf - '1');
		}
		else if(*buf >= 'A' && *buf <= 'H') {
			gtk_menu_set_active(GTK_MENU(menu), *buf - 'A' + 8);
			gtk_option_menu_set_history(GTK_OPTION_MENU(omSkytt), *buf - 'A' + 8);
		}
		else {
			gtk_option_menu_set_history(GTK_OPTION_MENU(omSkytt), 16);
			gtk_menu_set_active(GTK_MENU(menu), 16);
		}


		gtk_clist_get_text(GTK_CLIST(clProgNew), row, 1, &buf);
		menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(omElev));
		if(*buf == 'L') {
			gtk_menu_set_active(GTK_MENU(menu), 0);
			gtk_option_menu_set_history(GTK_OPTION_MENU(omElev), 0);
		}
		else if(*buf == 'M') {
			gtk_menu_set_active(GTK_MENU(menu), 1);
			gtk_option_menu_set_history(GTK_OPTION_MENU(omElev), 1);
		}
		else if(*buf == 'H') {
			gtk_menu_set_active(GTK_MENU(menu), 2);
			gtk_option_menu_set_history(GTK_OPTION_MENU(omElev), 2);
		}
		else {
			g_print("MYSKO!!!! buf=%s\n", buf);
		}
			
		gtk_clist_get_text(GTK_CLIST(clProgNew), row, 2, &buf);
		value = atoi(buf);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(sbDuvor), (gfloat)value);
	}

	sprintf(id, "%d", row);
	gtk_label_set_text(GTK_LABEL(lbl_ID), id);


	g_print("-- showing progedit win\n");
	update_skytt_stats();
	gtk_widget_show(GTK_WIDGET(progeditwin));
}


gboolean on_progeditwin_delete_event(GtkWidget *widget, GdkEvent *event,
                                        gpointer user_data) {

	g_print("-- Attempt to delete window - Calling EditCancel!\n");

	gtk_button_clicked(GTK_BUTTON(btnProgEditCancel));
	return TRUE;
}


void on_btnProgEditButtons_clicked(GtkButton *button, gpointer action) {
	gchar *values[3], *buf, tmp[0xff];
	gint row;

	g_print("-- EditExit: Hiding progeditwin(%p)!\n", action);
	gtk_widget_hide(progeditwin);

	/* Avbryt */
	if(!action)
		return;

	gtk_label_get(GTK_LABEL(lbl_ID), &buf);
	row = atoi(buf);

	/* Ta bort */
	if(action == (gpointer)2) {
		buf = NULL;
		gtk_clist_get_text(GTK_CLIST(clProgNew), row+1, 0, &buf);
		if(buf)
			gtk_clist_remove(GTK_CLIST(clProgNew), row);

		return;
	}
		

	gtk_label_get(GTK_LABEL(GTK_BIN(omSkytt)->child), values+0);
	gtk_label_get(GTK_LABEL(GTK_BIN(omElev)->child), values+1);
	sprintf(tmp, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sbDuvor)));
	values[2] = tmp;
	
	gtk_clist_insert(GTK_CLIST(clProgNew), row, values);
	gtk_clist_get_text(GTK_CLIST(clProgNew), row+1, 0, &buf);

	/* Ta bort efter om det inte är den speciella raden 'Lägg till'
	   Detta pga raden editerades och inte lades till! */
	if(strcmp(buf, "Lägg"))
		gtk_clist_remove(GTK_CLIST(clProgNew), row+1);
	else /* Låt Lägg till raden vara den sista synliga raden */
		gtk_clist_moveto(GTK_CLIST(clProgNew), row+1, 0, 0.99, 0.00);

	update_skytt_stats();
}


void on_btnProgsave_clicked(GtkButton *button, gpointer user_data) {
	gchar *txt = NULL;

	g_print("-- Saving program instructions\n");
	gtk_label_get(GTK_LABEL(lblProgeditName), &txt);
	if(strlen(txt))
		gtk_entry_set_text(GTK_ENTRY(enProgname), txt);
	else
		gtk_entry_set_text(GTK_ENTRY(enProgname), "Nytt");

	gtk_widget_show(progsavewin);
}


void on_btnProgsavename_clicked (GtkButton *button, gpointer user_data) {
	gchar *name;
	int status, cid;

	name = gtk_entry_get_text(GTK_ENTRY(enProgname));
	status = program_save(clProgNew, name);
	cid = gtk_statusbar_get_context_id(GTK_STATUSBAR(sbProgedit), "progedit");

	if(status == 1)
		gtk_statusbar_push(GTK_STATUSBAR(sbProgedit), cid, "Programmet sparat");
	else if(status == 0)
		gtk_statusbar_push(GTK_STATUSBAR(sbProgedit), cid, "Programmet EJ sparat");
	else if(status == -1)
		gtk_statusbar_push(GTK_STATUSBAR(sbProgedit), cid, 
					"Det tomma programmet togs bort");

	gtk_widget_hide(progsavewin);


	program_rescan(omProgedit);
}


void on_mnExitProgram_activate(GtkMenuItem *menuitem, gpointer user_data) {
	g_print("-- slim exiting!\n");

	/* DETTA KAN VARA FARLIGT */
	adlink_output(0x00, ADLINK_SET);
	gtk_main_quit();
}



void on_omPrograms_activated(GtkMenuItem *item, gpointer txt) {
	program_load((gchar *)txt, clProgNew);
	gtk_label_set_text(GTK_LABEL(lblProgeditName), (gchar *)txt);
	update_skytt_stats();
}


gboolean on_debugwin_delete_event(GtkWidget *widget, GdkEvent *event, 
	gpointer user_data) {

	gtk_widget_hide(debugwin);
	adlink_output(0x01, ADLINK_CLEAR);
	adlink_output(0x02, ADLINK_CLEAR);
	adlink_output(0x04, ADLINK_CLEAR);
	adlink_output(0x08, ADLINK_CLEAR);
	adlink_output(0x10, ADLINK_CLEAR);
	adlink_output(0x20, ADLINK_CLEAR);
	adlink_output(0x40, ADLINK_CLEAR);
	adlink_output(0x80, ADLINK_CLEAR);
	return TRUE;
}


void on_cb_manual_toggled(GtkToggleButton *togglebutton, gpointer user_data) {

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
		adlink_output(((u_long)user_data)&0xff, ADLINK_ADD);
	}
	else {
		adlink_output(((u_long)user_data)&0xff, ADLINK_CLEAR);
	}
}



/*
 * ++....
 * Menyalternativs handlers
 * ++''''
 *
 */


void on_mnRotorStarta_activate(GtkMenuItem *menuitem, gpointer user_data) {

		/* Gör det här menyvalet okänsligt */
		gtk_widget_set_sensitive(GTK_WIDGET(mnRotorStarta), FALSE);
		/* Gör det här menyvalet känsligt */
		gtk_widget_set_sensitive(GTK_WIDGET(mnRotorStoppa), TRUE);


		run->rotor_on = 1;
		run->init_round = 0;
		run->round = 0;


		g_print("-- ROTOR: spinup.\n");
		if(use_vrotor) {
			/* Starta den virtuella rotorn */
			gtk_timeout_add(2000, virt_rotor_trigger, NULL);
			vrotor = TRUE;
		}
		else
			adlink_output(OUTPUT_ROTOR, ADLINK_ADD);

		/* Set elev to a known state */
		run->elev_state = 0;
		elev_change(ELEV_UP);


		run->rotor_cid = gtk_statusbar_get_context_id(GTK_STATUSBAR(sbStatus), "rotor");
		gtk_statusbar_push(GTK_STATUSBAR(sbStatus), run->rotor_cid, 
					"Väntar på att rotorns hastighet ska stabiliseras");

}


void on_mnRotorStoppa_activate(GtkMenuItem *menuitem, gpointer user_data) {

		run->rotor_on = 0;
		run->elev_state = 0; /* invalid, force changed */
		g_print("on_mnRotorStoppa_activate(): cid=%d\n", run->rotor_cid);

		if(run->rotor_cid) {
			gtk_statusbar_pop(GTK_STATUSBAR(sbStatus), run->rotor_cid);
		}

		if(use_vrotor)
			/* Stoppa den virtuella rotorn */
			vrotor = FALSE;
		else
			adlink_output(OUTPUT_ROTOR|OUTPUT_SPANNARE, ADLINK_CLEAR);

		/* Gör det här menyvalet känsligt */
		gtk_widget_set_sensitive(GTK_WIDGET(mnRotorStarta), TRUE);

		/* Gör det här menyvalet okänsligt */
		gtk_widget_set_sensitive(GTK_WIDGET(mnRotorStoppa), FALSE);


		/* Pausa programkörningen! */

		/* XXX - cleara allting för säkerhets skull */
		g_print("-- clear outputs\n");
		adlink_output(0x00, ADLINK_SET);


		gtk_clist_clear(GTK_CLIST(clInfo));

}


void on_mnProgramRun_activate(GtkMenuItem *menuitem, gpointer user_data) {
	gchar *progname;

	if(run->rotor_on) {
		g_print("-- mnProgramRun: SETTING OUTPUT_SPANNARE\n");
		adlink_output(OUTPUT_SPANNARE, ADLINK_ADD);
		usleep(80000);
	}

	if(run->program == NULL) {
		gtk_label_get(GTK_LABEL(GTK_BIN(omPrograms)->child), &progname);
		g_print("-- [program]: load (%s)\n", progname);
		program_load(progname, NULL);
	}

	
	gtk_widget_set_sensitive(GTK_WIDGET(omPrograms), FALSE);

	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramRun), FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramPause), TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramReset), TRUE);

	gtk_clist_clear(GTK_CLIST(clInfo));

	run->running = 1;
}


void on_mnProgramPause_activate(GtkMenuItem *menuitem, gpointer user_data) {

	run->running = 0;

	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramRun), TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramPause), FALSE);
}


void on_mnProgramReset_activate(GtkMenuItem *menuitem, gpointer user_data) {

	g_print("on_mnProgramReset_activate(): ENTER!\n");
	/* Fråga om man är säker .. */
	gtk_widget_set_sensitive(GTK_WIDGET(omPrograms), TRUE);

	/* Ta bort det laddade programmet ur minnet.. */
	/* XXX - borde endast tas bort om det är ett nytt program.
	   Ska styras av när man väljer ett nytt alternativ i omPrograms */

	run->running = 0;
	run->instruction = 0;
	run->tot_instructions = 0;
	run->value = 0;

	/* XXX - om man resettar så kan programmet kraschar i exec_done!
	if(run->program) {
		free(run->program);
		run->program = NULL;
	}
	*/

	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramRun), TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramPause), FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(mnProgramReset), FALSE);
}


void on_mnProgramCreate_activate(GtkMenuItem *menuitem, gpointer user_data) {
	gchar *str[] = { "Lägg", "till", "ny rad" };

	gtk_clist_clear(GTK_CLIST(clProgNew));
	gtk_clist_append(GTK_CLIST(clProgNew), str);
	gtk_label_set_text(GTK_LABEL(lblProgeditName), "");

	/* Fyll omProgedit menyn.. */
	program_rescan(omProgedit);

	/* Uppdatera skytt statistiken */
	update_skytt_stats();

	/* Visa kodfönstret */
	gtk_widget_show(progwin);
}


void on_mnProgramModify_activate(GtkMenuItem *menuitem, gpointer user_data) {
	gchar *txt;

	/* Plocka text från det aktiva menyvalet */
	gtk_label_get(GTK_LABEL(GTK_BIN(omPrograms)->child), &txt);
	program_load(txt, clProgNew);
	gtk_label_set_text(GTK_LABEL(lblProgeditName), txt);

	/* Fyll omProgedit menyn.. */
	program_rescan(omProgedit);

	/* Uppdatera skytt statistiken */
	update_skytt_stats();

	/* Visa kodfönstret */
	gtk_widget_show(progwin);
}


void on_mnDebugShow_activate(GtkMenuItem *menuitem, gpointer user_data) {
	gtk_widget_show(debugwin);
}


void on_mnProperties_activate(GtkMenuItem *menuitem, gpointer user_data) {
	/* XXX
	 * Man ska kunna ställa in:
	 * Olika tider (offsets & /etc)
	 * Var den ska leta efter program
	 * Rubrik på fönstret (ist.f. slim)
	 * 
	 *
	 */

	config_load_to_clist(clSettings);
	gtk_widget_show(settingswin);
}


gboolean on_settingswin_delete_event(GtkWidget *widget, GdkEvent *event,
					gpointer user_data) {

	gtk_widget_hide(widget);

	config_save_from_clist(clSettings);

	/* Save our new configuration */
	config_save(0);

	/* Update the run struct */
	config_use();


	return TRUE;
}


void on_clSettings_select_row(GtkCList *clist, gint row, gint column,
				 GdkEvent *event, gpointer user_data) {

	gchar *buf;
	gchar id[10];

	if(event && !(event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS))
		return;


	gtk_clist_get_text(GTK_CLIST(clist), row, column, &buf);
	g_print("Row/Col[%d/%d]: Clicked twice. Text[%s]\n", row , column, buf);

	gtk_clist_get_text(GTK_CLIST(clist), row, 0, &buf);
	gtk_entry_set_text(GTK_ENTRY(enName), buf);
	gtk_clist_get_text(GTK_CLIST(clist), row, 1, &buf);
	gtk_entry_set_text(GTK_ENTRY(enValue), buf);

	sprintf(id, "%d", row);
	gtk_label_set_text(GTK_LABEL(hidRow), id);

	g_print("-- showing settingsedit win\n");
	gtk_widget_show(GTK_WIDGET(settingseditwin));
}


void on_btnSettingsExit_clicked(GtkButton *button, gpointer user_data) {

	gtk_widget_hide(GTK_WIDGET(settingswin));

	/* XXX - samma sak göres i delete-event handlern! */

	config_save_from_clist(clSettings);

	/* Save our new configuration */
	config_save(0);

	/* Update the run struct */
	config_use();


}



void on_btnSettingsReset_clicked(GtkButton *button, gpointer user_data) {

	config_save(1);
	config_load_to_clist(clSettings);
}


gboolean on_settingseditwin_delete_event(GtkWidget *widget, GdkEvent *event,
					 gpointer user_data) {

	gtk_widget_hide(widget);
	return TRUE;
}


void on_btnSettingsEditOK_clicked(GtkButton *button, gpointer user_data) {
	gchar *values[2];
	gchar *buf;
	int row;

	values[0] = strdup(gtk_entry_get_text(GTK_ENTRY(enName)));
	values[1] = strdup(gtk_entry_get_text(GTK_ENTRY(enValue)));
	gtk_label_get(GTK_LABEL(hidRow), &buf);
	row = atoi(buf);

	gtk_clist_insert(GTK_CLIST(clSettings), row, values);
	gtk_clist_remove(GTK_CLIST(clSettings), row+1);

	gtk_widget_hide(GTK_WIDGET(settingseditwin));
}

void
on_tbEnableDebug_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
		debug = 1;
	else
		debug = 0;
}


void on_tbVrotor_toggled(GtkToggleButton *togglebutton, gpointer user_data) {

	/* Används i on_mnRotorStarta_activate */
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
		use_vrotor = 1;
	else
		use_vrotor = 0;
}


void update_skytt_stats(void) {
	gchar *text, buf[0xff];
	int i, skytt;
	int lblstats[16];
	GtkWidget *lbls[16] = { 
		lblSkytt1, lblSkytt2, lblSkytt3, lblSkytt4,
		lblSkytt5, lblSkytt6, lblSkytt7, lblSkytt8,
		lblSkyttA, lblSkyttB, lblSkyttC, lblSkyttD,
		lblSkyttE, lblSkyttF, lblSkyttG, lblSkyttH
	};

	i = 0;
	memset(&lblstats, 0, sizeof(lblstats));
	while(gtk_clist_get_text(GTK_CLIST(clProgNew), i, 0, &text)) {
		if(*text >= '1' && *text <= '8')
			skytt = *text - '1';
		else if(*text >= 'A' && *text <= 'H')
			skytt = *text - 'A' + 8;
		else {
			/* Ex: text==Paustid || text=Lägg */
			i++;
			continue;
		}

		text = NULL;
		gtk_clist_get_text(GTK_CLIST(clProgNew), i, 2, &text);
		lblstats[skytt] += atoi(text);

		i++;
	}

	for(i = 0; i < 16; i++) {
		sprintf(buf, "%d", lblstats[i]);
		gtk_label_set_text(GTK_LABEL(lbls[i]), buf);
	}
}


void on_ctrlGui_activate(GtkMenuItem *menuitem, gpointer user_data) {

}


void on_ctrlMan_activate(GtkMenuItem *menuitem, gpointer user_data) {

}


gboolean on_dlgWarnReset_destroy_event(GtkWidget *widget, GdkEvent *event,
					gpointer user_data) {



	return FALSE;
}


void on_btnWarnReset_clicked(GtkButton *button, gpointer user_data) {

	gtk_widget_hide(dlgWarnReset);
}

