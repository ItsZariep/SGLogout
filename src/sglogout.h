#ifndef SGLOGOUT_H
#define SGLOGOUT_H

#include <gtk/gtk.h>

#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#define ML 512

gint sgcfg, omode;

gchar *pm, *home_dir, *sessiondo;
const gchar *clayout, *cposition, *ciconsize;

#include "settings.h"
#include "cfgmgr.h"
#include "mainwindow.h"
#include "events.h"

#endif
