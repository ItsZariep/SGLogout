#ifndef CFGMGR_H
#define CFGMGR_H

#include <gtk/gtk.h>
#include "settings.h"

extern GtkWidget *gsettingscmd;
extern GtkWidget *ghibernatecmd;
extern GtkWidget *glockscreencmd;
extern GtkWidget *glogoutcmd;
extern GtkWidget *gpwroffcmd;
extern GtkWidget *grebootcmd;
extern GtkWidget *gsettingscmd;
extern GtkWidget *gsuspendcmd;
extern GtkWidget *glayout;
extern GtkWidget *gposition;
extern GtkWidget *giconsize;
extern GtkWidget *gpostxt;
extern GtkWidget *gshowtxt;
extern GtkWidget *gshowico;

#define XA 0.0f
#define XM 4

void on_save_button_clicked(GtkWidget *dummy, gpointer data);
void showcfg(void);

#endif
