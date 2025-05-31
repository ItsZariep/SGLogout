#include "settings.h"

guint layout = 1;
guint gridlayout_cols = 1;
guint autogridadjustment = 1;
guint position = 4;
guint iconsize = 32;
guint showconfirm = 1;
guint showicons = 1;
guint showtext = 1;
guint postxt = 1;
guint customcss = 0;

gchar *shutdowncmd = NULL;
gchar *rebootcmd = NULL;
gchar *hibernatecmd = NULL;
gchar *suspendcmd = NULL;
gchar *closeallcmd = NULL;
gchar *lockcmd = NULL;
gchar *logoutcmd = NULL;


void readconf(void)
{
	GKeyFile *key_file;
	GError *error = NULL;
	gchar *config_file_path;

	const gchar *conf_dir = g_get_user_config_dir();
	config_file_path = g_build_filename(conf_dir, "sglogout.conf", NULL);

	key_file = g_key_file_new();

	if (!g_key_file_load_from_file(key_file, config_file_path, G_KEY_FILE_NONE, &error))
	{
		g_warning("Failed to load config file: %s", config_file_path);

		hibernatecmd = g_strdup("(command -v systemctl >/dev/null && systemctl hibernate) || (command -v loginctl >/dev/null && loginctl hibernate)");
		suspendcmd   = g_strdup("(command -v systemctl >/dev/null && systemctl suspend) || (command -v loginctl >/dev/null && loginctl suspend)");
		shutdowncmd  = g_strdup("(command -v systemctl >/dev/null && systemctl poweroff) || (command -v loginctl >/dev/null && loginctl poweroff)");
		rebootcmd    = g_strdup("(command -v systemctl >/dev/null && systemctl reboot) || (command -v loginctl >/dev/null && loginctl reboot)");
		lockcmd      = g_strdup("xdg-screensaver lock");
		logoutcmd    = g_strdup("pkill -KILL -u $USER");
		closeallcmd  = g_strdup("xdotool getactivewindow windowkill");
		return;
	}

	g_custom_message("Settings [READ]", "Reading file: %s", config_file_path);
	layout = g_key_file_get_integer(key_file, "Settings", "layout", NULL);
		g_custom_message("Settings [LOAD]", "layout: %d", layout);
	gridlayout_cols = g_key_file_get_integer(key_file, "Settings", "gridlayout_cols", NULL);
		g_custom_message("Settings [LOAD]", "gridlayout_cols: %d", gridlayout_cols);
	autogridadjustment = g_key_file_get_integer(key_file, "Settings", "autogridadjustment", NULL);
		g_custom_message("Settings [LOAD]", "autogridadjustment: %d", autogridadjustment);
	position = g_key_file_get_integer(key_file, "Settings", "position", NULL);
		g_custom_message("Settings [LOAD]", "position: %d", position);
	iconsize = g_key_file_get_integer(key_file, "Settings", "iconsize", NULL);
		g_custom_message("Settings [LOAD]", "iconsize: %d", iconsize);
	showicons = g_key_file_get_integer(key_file, "Settings", "showicons", NULL);
		g_custom_message("Settings [LOAD]", "showicons: %d", showicons);
	showconfirm = g_key_file_get_integer(key_file, "Settings", "showconfirm", NULL);
		g_custom_message("Settings [LOAD]", "showconfirm: %d", showconfirm);
	showtext = g_key_file_get_integer(key_file, "Settings", "showtext", NULL);
		g_custom_message("Settings [LOAD]", "showtext: %d", showtext);
	postxt = g_key_file_get_integer(key_file, "Settings", "postxt", NULL);
		g_custom_message("Settings [LOAD]", "postxt: %d", postxt);
	customcss = g_key_file_get_integer(key_file, "Settings", "customcss", NULL);
		g_custom_message("Settings [LOAD]", "customcss: %d", customcss);

	shutdowncmd = g_key_file_get_string(key_file, "Settings", "shutdowncmd", NULL);
		g_custom_message("Settings [LOAD]", "shutdowncmd: %s", shutdowncmd);
	rebootcmd = g_key_file_get_string(key_file, "Settings", "rebootcmd", NULL);
		g_custom_message("Settings [LOAD]", "rebootcmd: %s", rebootcmd);
	suspendcmd = g_key_file_get_string(key_file, "Settings", "suspendcmd", NULL);
		g_custom_message("Settings [LOAD]", "suspendcmd: %s", suspendcmd);
	hibernatecmd = g_key_file_get_string(key_file, "Settings", "hibernatecmd", NULL);
		g_custom_message("Settings [LOAD]", "hibernatecmd: %s", hibernatecmd);
	closeallcmd = g_key_file_get_string(key_file, "Settings", "closeallcmd", NULL);
		g_custom_message("Settings [LOAD]", "closeallcmd: %s", closeallcmd);
	lockcmd = g_key_file_get_string(key_file, "Settings", "lockcmd", NULL);
		g_custom_message("Settings [LOAD]", "lockcmd: %s", lockcmd);
	logoutcmd = g_key_file_get_string(key_file, "Settings", "logoutcmd", NULL);
		g_custom_message("Settings [LOAD]", "logoutcmd: %s", logoutcmd);


	g_key_file_free(key_file);
	g_free(config_file_path);
}

void saveconf(void)
{
	GKeyFile *key_file;
	GError *error = NULL;
	gchar *config_file_path;
	gchar *data;

	const gchar *conf_dir = g_get_user_config_dir();
	config_file_path = g_build_filename(conf_dir, "sglogout.conf", NULL);

	key_file = g_key_file_new();

	// Set integer values
	g_key_file_set_integer(key_file, "Settings", "layout", layout);
		g_custom_message("Settings [SAVE]", "layout: %d", layout);
	g_key_file_set_integer(key_file, "Settings", "gridlayout_cols", gridlayout_cols);
		g_custom_message("Settings [SAVE]", "gridlayout_cols: %d", gridlayout_cols);
	g_key_file_set_integer(key_file, "Settings", "autogridadjustment", autogridadjustment);
		g_custom_message("Settings [SAVE]", "autogridadjustment: %d", autogridadjustment);
	g_key_file_set_integer(key_file, "Settings", "position", position);
		g_custom_message("Settings [SAVE]", "position: %d", position);
	g_key_file_set_integer(key_file, "Settings", "iconsize", iconsize);
		g_custom_message("Settings [SAVE]", "iconsize: %d", iconsize);
	g_key_file_set_integer(key_file, "Settings", "showicons", showicons);
		g_custom_message("Settings [SAVE]", "showicons: %d", showicons);
	g_key_file_set_integer(key_file, "Settings", "showconfirm", showconfirm);
		g_custom_message("Settings [SAVE]", "showconfirm: %d", showconfirm);
	g_key_file_set_integer(key_file, "Settings", "showtext", showtext);
		g_custom_message("Settings [SAVE]", "showtext: %d", showtext);
	g_key_file_set_integer(key_file, "Settings", "postxt", postxt);
		g_custom_message("Settings [SAVE]", "postxt: %d", postxt);
	g_key_file_set_integer(key_file, "Settings", "customcss", customcss);
		g_custom_message("Settings [SAVE]", "customcss: %d", customcss);

	// Set string values
	if (shutdowncmd) g_key_file_set_string(key_file, "Settings", "shutdowncmd", shutdowncmd);
		g_custom_message("Settings [SAVE]", "shutdowncmd: %s", shutdowncmd);
	if (rebootcmd) g_key_file_set_string(key_file, "Settings", "rebootcmd", rebootcmd);
		g_custom_message("Settings [SAVE]", "rebootcmd: %s", rebootcmd);
	if (suspendcmd) g_key_file_set_string(key_file, "Settings", "suspendcmd", suspendcmd);
		g_custom_message("Settings [SAVE]", "suspendcmd: %s", suspendcmd);
	if (hibernatecmd) g_key_file_set_string(key_file, "Settings", "hibernatecmd", hibernatecmd);
		g_custom_message("Settings [SAVE]", "hibernatecmd: %s", hibernatecmd);
	if (closeallcmd) g_key_file_set_string(key_file, "Settings", "closeallcmd", closeallcmd);
		g_custom_message("Settings [SAVE]", "closeallcmd: %s", closeallcmd);
	if (lockcmd) g_key_file_set_string(key_file, "Settings", "lockcmd", lockcmd);
		g_custom_message("Settings [SAVE]", "lockcmd: %s", lockcmd);
	if (logoutcmd) g_key_file_set_string(key_file, "Settings", "logoutcmd", logoutcmd);
		g_custom_message("Settings [SAVE]", "logoutcmd: %s", logoutcmd);

	data = g_key_file_to_data(key_file, NULL, NULL);

	if (!g_file_set_contents(config_file_path, data, -1, &error))
	{
		g_printerr("Error saving config file: %s\n", error->message);
		g_error_free(error);
	}

	g_free(data);
	g_free(config_file_path);
	g_key_file_free(key_file);
}
