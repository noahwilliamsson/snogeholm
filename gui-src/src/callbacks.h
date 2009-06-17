#include <gnome.h>


void
on_mainwin_destroy                     (GtkObject       *object,
                                        gpointer         user_data);

void
on_tbRotor_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_tbProgrun_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btnProgreset_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnProgcreate_clicked               (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_progwin_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_btnProgExit_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_clNewProg_select_row                (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_progeditwin_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_btnEditExit_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnProgexit_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_clProgNew_select_row                (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_btnProgEditButtons_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnProgEditButtons_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnProgsave_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnProgsavename_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void    
on_omPrograms_activated                 (GtkMenuItem *item,
					 gpointer blah);


void
on_btnManual_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_cb_manual_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_manualwin_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_cb_manual_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_manual_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_manual_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_mnRotor_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnRotorStarta_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnRotorStoppa_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgram_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramLoad_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramRun_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramPause_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramReset_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramCreate_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnManualShow_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProperties_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnExitProgram_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_btnProgEditButtons_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnProgEditButtons_clicked          (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_settingswin_destroy_event           (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_settingswin_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_clSettings_select_row               (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_btnSettingsReset_clicked            (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_settingseditwin_delete_event        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_btnSettingsEditOK_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnSettingsEditExit_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btnSettingsExit_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_mnDebugShow_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_debugwin_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_tbEnableDebug_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_tbVrotor_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_manual_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ctrlGui_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_ctrlMan_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramCreate_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mnProgramModify_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_btnTest_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_dwMain_expose_event                 (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_pxmMain_expose_event                (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_imgMain_expose_event                (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_imgMain_expose_event                (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_dlgWarnReset_destroy_event          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_btnWarnReset_clicked                (GtkButton       *button,
                                        gpointer         user_data);
