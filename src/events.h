#ifndef EVENTS_H
#define EVENTS_H

#include <gtk/gtk.h>
#include "settings.h"

extern guint verbose;

void custom_log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);
void g_custom_message(const gchar *prefix, const gchar *format, ...);
gboolean on_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void run_command(GtkWidget *input, GtkWindow *main_window);

#endif
