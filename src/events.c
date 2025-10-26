#include "events.h"

#ifdef wayland
	#include <gtk-layer-shell/gtk-layer-shell.h>
#elif defined(X11)
	#include "sgxpos/sgxpos.h"
#endif

guint verbose = 0;
static guint selflock = 0;

void custom_log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
	(void)log_level;
	(void)user_data;
	(void)log_domain;

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



gboolean on_focus_out(GtkWidget *widget, gpointer user_data)
{
	(void)widget;

	int value = GPOINTER_TO_INT(user_data);
	if (value == 1)
	{
		selflock = 0;
		g_custom_message("Events [Window]", "Exit on focus re-enabled");
	}
	else
	{
		if (selflock == 0)
		{
			gtk_main_quit();
			return TRUE;
		}
	}
	return FALSE;
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	(void)widget; (void)data;

	if (event->keyval == GDK_KEY_Escape)
	{
		gtk_main_quit();
	}
	return FALSE;
}


typedef struct
{
	gchar *command;
	GtkWindow *main_window;
} CommandData;

typedef struct
{
	gchar *error_message;
	GtkWindow *main_window;
} ErrorDialogData;


static gboolean show_error_dialog(gpointer user_data)
{
	ErrorDialogData *err_data = (ErrorDialogData *)user_data;

	GtkWidget *dialog = gtk_message_dialog_new(
		err_data->main_window,
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_CLOSE,
		"%s", err_data->error_message
	);

	gtk_window_set_title(GTK_WINDOW(dialog), "Error");
	gtk_window_set_transient_for(GTK_WINDOW(dialog), err_data->main_window);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	gtk_window_set_keep_above(GTK_WINDOW(dialog), TRUE);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	g_free(err_data->error_message);
	g_free(err_data);

	selflock = 0;
	g_custom_message("Events [Window]", "Exit on focus re-enabled");
	return FALSE; // remove from idle
}

static void execute_command(const gchar *command, GtkWindow *main_window)
{
	gchar **argv = g_strsplit(command, " ", -1);
	GError *error = NULL;
	gtk_widget_hide(GTK_WIDGET(main_window));

	if (!g_spawn_async(NULL, argv, NULL, G_SPAWN_SEARCH_PATH | G_SPAWN_DO_NOT_REAP_CHILD,
		NULL, NULL, NULL, &error))
	{
		ErrorDialogData *err_data = g_new0(ErrorDialogData, 1);
		err_data->error_message = g_strdup(error->message);
		err_data->main_window = main_window;
		g_idle_add(show_error_dialog, err_data);
		gtk_widget_show(GTK_WIDGET(main_window));
		g_error_free(error);
	}
	else
	{
		gtk_widget_destroy(GTK_WIDGET(main_window));
	}
	g_strfreev(argv);
}

static void on_confirm_no(GtkWidget *button, gpointer data)
{
	(void)button;
	GtkWidget *popover = GTK_WIDGET(data);
	gtk_popover_popdown(GTK_POPOVER(popover));
}

static void on_confirm_yes(GtkWidget *button, gpointer data)
{
	(void)data;

	const gchar *command = g_object_get_data(G_OBJECT(button), "command");
	GtkWindow *main_window = g_object_get_data(G_OBJECT(button), "main_window");
	GtkWidget *popover = g_object_get_data(G_OBJECT(button), "popover");

	gtk_popover_popdown(GTK_POPOVER(popover));
	execute_command(command, main_window);
}

static void on_popover_closed(GtkPopover *popover, gpointer data)
{
	(void)popover;(void)data;
	selflock = 0;
	g_custom_message("Events [Window]", "Exit on focus re-enabled");
}

void run_command(GtkWidget *input, GtkWindow *main_window)
{
	if (selflock == 1)
	{
		return;
	}

	selflock = 1;
	g_custom_message("Events [Window]", "Exit on focus disabled");
	const gchar *command = g_object_get_data(G_OBJECT(input), "command");
	const gchar *label = g_object_get_data(G_OBJECT(input), "label");
	const gchar *iconname = g_object_get_data(G_OBJECT(input), "icon");

	if (!command || *command == '\0')
	{
		g_warning("No command provided.");
		return;
	}

	if (showconfirm == 1)
	{
		GtkWidget *popover = gtk_popover_new(input);
		gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);

		GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
		gtk_container_set_border_width(GTK_CONTAINER(box), 12);

		GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);

		GtkWidget *icon;
		if (iconname && *iconname != '\0')
		{
			icon = gtk_image_new_from_icon_name(iconname, GTK_ICON_SIZE_DIALOG);
		}
		else
		{
			icon = gtk_image_new_from_icon_name("dialog-warning", GTK_ICON_SIZE_DIALOG);
		}
		gtk_widget_set_valign(icon, GTK_ALIGN_START);
		gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);

		gchar *message = g_strconcat("Are you sure you want to ", label, "?", NULL);
		GtkWidget *label_widget = gtk_label_new(message);
		gtk_label_set_line_wrap(GTK_LABEL(label_widget), TRUE);
		gtk_label_set_max_width_chars(GTK_LABEL(label_widget), 40);
		gtk_widget_set_halign(label_widget, GTK_ALIGN_START);
		gtk_box_pack_start(GTK_BOX(hbox), label_widget, TRUE, TRUE, 0);
		g_free(message);

		gtk_box_pack_start(GTK_BOX(box), hbox, FALSE, FALSE, 0);

		GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
		gtk_widget_set_halign(button_box, GTK_ALIGN_END);

		GtkWidget *btn_no = gtk_button_new_with_label("No");
		GtkWidget *btn_yes = gtk_button_new_with_label("Yes");

		GtkStyleContext *context = gtk_widget_get_style_context(btn_yes);
		gtk_style_context_add_class(context, "destructive-action");

		gtk_box_pack_start(GTK_BOX(button_box), btn_no, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(button_box), btn_yes, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(box), button_box, FALSE, FALSE, 0);

		gtk_container_add(GTK_CONTAINER(popover), box);
		gtk_widget_show_all(box);

		g_object_set_data(G_OBJECT(btn_yes), "command", (gpointer)command);
		g_object_set_data(G_OBJECT(btn_yes), "main_window", main_window);
		g_object_set_data(G_OBJECT(btn_yes), "popover", popover);

		g_signal_connect(btn_no, "clicked", G_CALLBACK(on_confirm_no), popover);
		g_signal_connect(btn_yes, "clicked", G_CALLBACK(on_confirm_yes), NULL);
		g_signal_connect(popover, "closed", G_CALLBACK(on_popover_closed), main_window);

		gtk_popover_popup(GTK_POPOVER(popover));
		return;
	}

	execute_command(command, main_window);
}