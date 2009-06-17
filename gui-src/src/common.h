/*
 * common.h, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */

#include "program.h"


#define INPUT_ELEV		0x01
#define INPUT_ROTOR		0x02
#define INPUT_REMOTE		0x04

#define OUTPUT_ELEV_UP		0x02
#define OUTPUT_ELEV_DN		0x01
#define OUTPUT_SHOOT		0x04
#define OUTPUT_ROTOR		0x08
#define OUTPUT_SPANNARE		0x10



/* Pending instruction */
#define I_PENDING	0x01
/* Instruction executed */
#define I_EXECUTED	0x02
/* Executing pause instruction */
#define I_PAUSE		0x04
/* Locked */
#define I_LOCKED	0x08
#define	I_NOOP		0x10


/* Elev dn */
#define ELEV_DN		0x04
/* Elev middle */
#define ELEV_MD		0x02
/* Elev up */
#define ELEV_UP		0x01


#define ADLINK_SET		0x01
#define ADLINK_ADD		0x02
#define ADLINK_CLEAR		0x04
#define ADLINK_VADD		0x20
#define ADLINK_VCLEAR		0x40


typedef struct {
	int id;
	int elev;
	int value;
} PROGRAM;

typedef struct {
	/* Rotor running */
	int rotor_on;

	/* Count of initial rotor rounds */
	int init_round;

	/* Statusbar context id */
	int rotor_cid;

	/* Rotor timing statistics */
	struct timeval tstat[5];


	/* Misc flags..? */
	volatile int flags;


	/* We're processing instructions.. */
	int running;

	/* Num pending instructions */
	int pend_instructions;

	/* Total number of instructions (1..n) */
	int tot_instructions;

	/* Subinstructions left to execute */
	int value;

	/* Current instruction */
	int instruction;

	/* Current set of instructions */
	PROGRAM *program;


	/* Elevator state */
	int elev_state;



	/* GUI configurable variables */

	/* Configurable value */
	int init_rounds;

	/* Time needed by the reloader to 
	   get ready to fire again */
	int reload_time;

	/* Set to TRUE when we'd like to try to
	   execute two instructions per round */
	int dual_execute;

	/* For debugging purposes */
	int round;

} RUN_INFO;




struct _CONFIG {
	char *name;
	char *val;
	struct _CONFIG *next;
};
typedef struct _CONFIG CONFIG;





/* Global vars */
extern RUN_INFO *run;
extern CONFIG *config;



extern GtkWidget *mainwin;
extern GtkWidget *sbStatus;
extern GtkWidget *omPrograms;
extern GtkWidget *clInfo;
extern GtkWidget *mnProgramRun;
extern GtkWidget *mnProgramPause;
extern GtkWidget *mnProgramReset;
extern GtkWidget *mnRotorStarta;
extern GtkWidget *mnRotorStoppa;
extern GtkWidget *imgMain;

extern GtkWidget *progwin;
extern GtkWidget *clProgNew;
extern GtkWidget *btnProgsave;
extern GtkWidget *btnProgexit;
extern GtkWidget *sbProgedit;
extern GtkWidget *omProgedit;
extern GtkWidget *lblProgeditName;
extern GtkWidget *lblSkytt1;
extern GtkWidget *lblSkytt2;
extern GtkWidget *lblSkytt3;
extern GtkWidget *lblSkytt4;
extern GtkWidget *lblSkytt5;
extern GtkWidget *lblSkytt6;
extern GtkWidget *lblSkytt7;
extern GtkWidget *lblSkytt8;
extern GtkWidget *lblSkyttA;
extern GtkWidget *lblSkyttB;
extern GtkWidget *lblSkyttC;
extern GtkWidget *lblSkyttD;
extern GtkWidget *lblSkyttE;
extern GtkWidget *lblSkyttF;
extern GtkWidget *lblSkyttG;
extern GtkWidget *lblSkyttH;


extern GtkWidget *progeditwin;
extern GtkWidget *btnProgEditOk;
extern GtkWidget *btnProgEditCancel;
extern GtkWidget *lbl_ID;
extern GtkWidget *omSkytt;
extern GtkWidget *omElev;
extern GtkWidget *sbDuvor;

extern GtkWidget *progsavewin;
extern GtkWidget *btnProgsavename;
extern GtkWidget *enProgname;

extern GtkWidget *debugwin;
extern GtkWidget *lblTiming;
extern GtkWidget *lblInput;
extern GtkWidget *lblOutput;
extern GtkWidget *tbVrotor;
extern GtkWidget *tbEnableDebug;
extern GtkWidget *cb1;
extern GtkWidget *cb2;
extern GtkWidget *cb3;
extern GtkWidget *cb4;
extern GtkWidget *cb5;
extern GtkWidget *cb6;
extern GtkWidget *cb7;
extern GtkWidget *cb8;

extern GtkWidget *settingswin;
extern GtkWidget *clSettings;

extern GtkWidget *settingseditwin;
extern GtkWidget *enName;
extern GtkWidget *enValue;
extern GtkWidget *hidRow;

extern GtkWidget *dlgWarnReset;

extern int adlink_fd;
extern int debug;
extern volatile int use_vrotor;

#include "proto.h"
