/*
 * proto.h, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */

/* adlink.c */
gint adlink_open(void);
gint adlink_output(u_char, gint);
gint adlink_monitor(gpointer);
gint spannare(gpointer);
gint virt_rotor_trigger(gpointer);
gint virt_rotor_trigger_off(gpointer);

gint update_angle(gpointer);


/* callbacks.c */
#include "callbacks.h"


/* config.c */
void config_read(void);
int config_save(int);
void config_free(void);
char *config_get(char *);
void config_load_to_clist(GtkWidget *);
void config_save_from_clist(GtkWidget *);
void config_use(void);


/* elev.v */
gint elev_change(int);
gint elev_done(gpointer);


/* program.c */
void program_init(void);
int program_save(GtkWidget *, gchar *);
void program_load(gchar *, GtkWidget *);
void program_rescan(GtkWidget *);
void schedule_instruction(void);
gint try_optimize(gint);
gint exec_instruction(gpointer);
gint exec_done(gpointer);
struct timeval time_diff(struct timeval, struct timeval);


/* vis.c */
void vis_init(void);
void vis_update(void);
