#include "events.h"

guint verbose = 0;

void custom_log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
	gint64 now_us = g_get_real_time();

	time_t seconds = (time_t)(now_us / G_USEC_PER_SEC);
	gint milliseconds = (gint)((now_us % G_USEC_PER_SEC) / 1000);

	struct tm *tm_info = localtime(&seconds);

	gchar time_buffer[32];

	if (tm_info != NULL)
	{
		strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info);

		size_t len = strlen(time_buffer);
		snprintf(time_buffer + len, sizeof(time_buffer) - len, ".%03d", milliseconds);
	}
	else
	{
		strncpy(time_buffer, "??:??:??.???", sizeof(time_buffer));
		time_buffer[sizeof(time_buffer) - 1] = '\0';
	}

	const gchar *prefix = (const gchar *)user_data;

	g_print("** \033[0;32m%s\033[0m: \033[0;34m%s\033[0m: %s\n", prefix, time_buffer, message);
}

void g_custom_message(const gchar *prefix, const gchar *format, ...)
{
	if (verbose == 1)
	{
		va_list args;
		va_start(args, format);

		gchar *formatted_message = g_strdup_vprintf(format, args);
		va_end(args);

		g_log_set_handler(NULL, G_LOG_LEVEL_MESSAGE, (GLogFunc) custom_log_handler, (gpointer) prefix);
		g_message("%s", formatted_message);
		g_free(formatted_message);
	}
}
