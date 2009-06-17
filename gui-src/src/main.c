/*
 * main.c, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include "interface.h"
#include "support.h"

#include "common.h"


GtkWidget *mainwin;
GtkWidget *sbStatus;
GtkWidget *omPrograms;
GtkWidget *clInfo;
GtkWidget *mnProgramRun;
GtkWidget *mnProgramPause;
GtkWidget *mnProgramReset;
GtkWidget *mnRotorStarta;
GtkWidget *mnRotorStoppa;
GtkWidget *imgMain;

GtkWidget *progwin;
GtkWidget *clProgNew;
GtkWidget *btnProgsave;
GtkWidget *btnProgexit;
GtkWidget *sbProgedit;
GtkWidget *omProgedit;
GtkWidget *lblSkytt1;
GtkWidget *lblSkytt2;
GtkWidget *lblSkytt3;
GtkWidget *lblSkytt4;
GtkWidget *lblSkytt5;
GtkWidget *lblSkytt6;
GtkWidget *lblSkytt7;
GtkWidget *lblSkytt8;
GtkWidget *lblSkyttA;
GtkWidget *lblSkyttB;
GtkWidget *lblSkyttC;
GtkWidget *lblSkyttD;
GtkWidget *lblSkyttE;
GtkWidget *lblSkyttF;
GtkWidget *lblSkyttG;
GtkWidget *lblSkyttH;
GtkWidget *lblProgeditName;

GtkWidget *progeditwin;
GtkWidget *btnProgEditOk;
GtkWidget *btnProgEditCancel;
GtkWidget *lbl_ID;
GtkWidget *omSkytt;
GtkWidget *omElev; 
GtkWidget *sbDuvor;

GtkWidget *progsavewin;
GtkWidget *btnProgsavename;
GtkWidget *enProgname;

GtkWidget *debugwin;
GtkWidget *lblTiming;
GtkWidget *lblOutput;
GtkWidget *lblInput;
GtkWidget *tbVrotor;
GtkWidget *tbEnableDebug;
GtkWidget *cb1;
GtkWidget *cb2;
GtkWidget *cb3;
GtkWidget *cb4;
GtkWidget *cb5;
GtkWidget *cb6;
GtkWidget *cb7;
GtkWidget *cb8;

GtkWidget *settingswin;
GtkWidget *clSettings;

GtkWidget *settingseditwin;
GtkWidget *enName;
GtkWidget *enValue;
GtkWidget *hidRow;

GtkWidget *dlgWarnReset;

int adlink_fd;
int debug = 0;
volatile int use_vrotor = 0;

RUN_INFO *run;
CONFIG *config;

int
main (int argc, char *argv[])
{

	gnome_init ("slim", VERSION, argc, argv);

	program_init();

	mainwin = create_mainwin();
  	gtk_widget_show(mainwin);

	/*
	 * Keep these in global vars for faster access
	 * since lookup_widget() is slow..
	 *
	 */

	sbStatus = lookup_widget(mainwin, "sbStatus");
	omPrograms = lookup_widget(mainwin, "omPrograms");
	clInfo = lookup_widget(mainwin, "clInfo");
	gtk_clist_column_titles_passive(GTK_CLIST(clInfo));
	mnRotorStarta = lookup_widget(mainwin, "mnRotorStarta");
	mnRotorStoppa = lookup_widget(mainwin, "mnRotorStoppa");
	mnProgramRun = lookup_widget(mainwin, "mnProgramRun");
	mnProgramPause = lookup_widget(mainwin, "mnProgramPause");
	mnProgramReset = lookup_widget(mainwin, "mnProgramReset");
	imgMain = lookup_widget(mainwin, "imgMain");


	progwin = create_progwin();
	btnProgsave = lookup_widget(progwin, "btnProgsave");
	btnProgexit = lookup_widget(progwin, "btnProgexit");
	clProgNew = lookup_widget(progwin, "clProgNew");
	sbProgedit = lookup_widget(progwin, "sbProgedit");
	omProgedit = lookup_widget(progwin, "omProgedit");
	gtk_clist_column_titles_passive(GTK_CLIST(clProgNew));
	lblProgeditName = lookup_widget(progwin, "lblProgeditName");
	lblSkytt1 = lookup_widget(progwin, "lblSkytt1");
	lblSkytt2 = lookup_widget(progwin, "lblSkytt2");
	lblSkytt3 = lookup_widget(progwin, "lblSkytt3");
	lblSkytt4 = lookup_widget(progwin, "lblSkytt4");
	lblSkytt5 = lookup_widget(progwin, "lblSkytt5");
	lblSkytt6 = lookup_widget(progwin, "lblSkytt6");
	lblSkytt7 = lookup_widget(progwin, "lblSkytt7");
	lblSkytt8 = lookup_widget(progwin, "lblSkytt8");
	lblSkyttA = lookup_widget(progwin, "lblSkyttA");
	lblSkyttB = lookup_widget(progwin, "lblSkyttB");
	lblSkyttC = lookup_widget(progwin, "lblSkyttC");
	lblSkyttD = lookup_widget(progwin, "lblSkyttD");
	lblSkyttE = lookup_widget(progwin, "lblSkyttE");
	lblSkyttF = lookup_widget(progwin, "lblSkyttF");
	lblSkyttG = lookup_widget(progwin, "lblSkyttG");
	lblSkyttH = lookup_widget(progwin, "lblSkyttH");


	progeditwin = create_progeditwin();
	btnProgEditOk = lookup_widget(progeditwin, "btnProgEditOk");
	btnProgEditCancel = lookup_widget(progeditwin, "btnProgEditCancel");
	lbl_ID = lookup_widget(progeditwin, "lbl_ID");
	omSkytt = lookup_widget(progeditwin, "omSkytt");
	omElev = lookup_widget(progeditwin, "omElev");
	sbDuvor = lookup_widget(progeditwin, "sbDuvor");

	progsavewin = create_progsavewin();
	btnProgsavename = lookup_widget(progsavewin, "btnProgsavename");
	enProgname = lookup_widget(progsavewin, "enProgname");


	debugwin = create_debugwin();
	lblTiming = lookup_widget(debugwin, "lblTiming");
	lblOutput = lookup_widget(debugwin, "lblOutput");
	lblInput = lookup_widget(debugwin, "lblInput");
	tbEnableDebug = lookup_widget(debugwin, "tbEnableDebug");
	tbVrotor = lookup_widget(debugwin, "tbVrotor");
	cb1 = lookup_widget(debugwin, "cb1");
	cb2 = lookup_widget(debugwin, "cb2");
	cb3 = lookup_widget(debugwin, "cb3");
	cb4 = lookup_widget(debugwin, "cb4");
	cb5 = lookup_widget(debugwin, "cb5");
	cb6 = lookup_widget(debugwin, "cb6");
	cb7 = lookup_widget(debugwin, "cb7");
	cb8 = lookup_widget(debugwin, "cb8");


	settingswin = create_settingswin();
	clSettings = lookup_widget(settingswin, "clSettings");

	settingseditwin = create_settingseditwin();
	enName = lookup_widget(settingseditwin, "enName");
	enValue = lookup_widget(settingseditwin, "enValue");
	hidRow = lookup_widget(settingseditwin, "hidRow");


	dlgWarnReset = create_dlgWarnReset();



	program_rescan(omPrograms);


	/* Open the I/O card */
	/* XXX - Check for errors! */
	adlink_open();


	/* Reset all outputs */
	/* XXX - poppa upp en varning om att 
	  allting inte står rätt till */
	adlink_output(0x00, ADLINK_SET);

	run = (RUN_INFO *)calloc(1, sizeof(RUN_INFO));


	config_read();

	/* Update the run struct with the config values */
	config_use();


	/* Check for inputstate changes each 50ms */
	gtk_timeout_add(50, adlink_monitor, NULL);


	/* Initialize visualization stuff */
	vis_init();

	/* XXX - fixa till! */
//	gtk_widget_show(dlgWarnReset);

	gtk_main ();

	return 0;
}
