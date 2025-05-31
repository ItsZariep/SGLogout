#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef wayland
	#include <gtk-layer-shell/gtk-layer-shell.h>
#elif defined(X11)
	#include "sgxpos/sgxpos.h"
#endif

#include "events.h"
#include "settings.h"
#include "cfgmgr.h"

void on_apply_button_clicked(GtkButton *button, gpointer user_data);
void create_window(void);

#endif
