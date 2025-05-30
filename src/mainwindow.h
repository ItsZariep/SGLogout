#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef wayland
	#include <gtk-layer-shell/gtk-layer-shell.h>
#elif defined(X11)
	#include "sgxpos/sgxpos.h"
#endif

#include "settings.h"
#include "cfgmgr.h"

gboolean on_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void on_submenu_item3_selected(GtkMenuItem *menuitem, gpointer userdata);
void on_apply_button_clicked(GtkButton *button, gpointer user_data);
void run_command(GtkWidget *widget);
void create_window(void);

#endif
