#ifndef EVENTS_H
#define EVENTS_H

#include <glib.h>
#include <stdio.h>

extern guint verbose;

void custom_log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);
void g_custom_message(const gchar *prefix, const gchar *format, ...);


#endif
