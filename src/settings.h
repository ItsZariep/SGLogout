#ifndef SETTINGS_H
#define SETTINGS_H

#include <glib.h>
#include "events.h"

extern guint layout;
extern guint gridlayout_cols;
extern guint autogridadjustment;
extern guint position;
extern guint iconsize;
extern guint showicons;
extern guint showconfirm;
extern guint showtext;
extern guint postxt;
extern guint customcss;

extern gchar *shutdowncmd;
extern gchar *rebootcmd;
extern gchar *hibernatecmd;
extern gchar *suspendcmd;
extern gchar *closeallcmd;
extern gchar *lockcmd;
extern gchar *logoutcmd;

void readconf(void);
void saveconf(void);

#endif
