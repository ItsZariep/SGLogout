#include "mainwindow.h"

GtkWidget *window;
GtkWidget *grid;
GtkWidget *dialog;
GtkWidget *label;
GtkWidget *headerbar;
GtkWidget *button;
GtkWidget *image;
GtkWidget *wtitle;
GtkWidget *submenu;
GtkWidget *submenu_item3;
GtkWidget *poscombo;
GtkWidget *layoutcombo;
GtkWidget *icocombo;
GtkWidget *wshowico;
GtkWidget *wshowtxt;
GtkWidget *wpostxt;
GtkWidget *defbtn;
GtkWidget *applybtn;
GtkWidget *shutdown_box;
GtkWidget *reboot_box;
GtkWidget *sleep_box;
GtkWidget *hibernate_box;
GtkWidget *lock_box;
GtkWidget *logout_box;
GtkWidget *killall_box;
GtkWidget *shutdown_btn;
GtkWidget *reboot_btn;
GtkWidget *sleep_btn;
GtkWidget *hibernate_btn;
GtkWidget *lock_btn;
GtkWidget *logout_btn;
GtkWidget *killall_btn;
GtkWidget *shutdown_ico;
GtkWidget *shutdown_txt;
GtkWidget *killall_ico;
GtkWidget *killall_txt;
GtkWidget *reboot_ico;
GtkWidget *reboot_txt;
GtkWidget *sleep_ico;
GtkWidget *sleep_txt;
GtkWidget *hibernate_ico;
GtkWidget *hibernate_txt;
GtkWidget *lock_ico;
GtkWidget *lock_txt;
GtkWidget *logout_ico;
GtkWidget *logout_txt;

GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;


gboolean on_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer user_data)
{
	gtk_main_quit();
	return TRUE;
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	if (event->keyval == GDK_KEY_Escape)
	{
		gtk_main_quit();
	}
	return FALSE;
}

void run_command(GtkWidget *input)
{
	const gchar *command = g_object_get_data(G_OBJECT(input), "command");

	if (!command || *command == '\0')
	{
		g_warning("No command provided.");
		return;
	}

	gchar **argv = g_strsplit(command, " ", -1);
	GError *error = NULL;
	gint exit_status;
	gchar *stdout_output = NULL;
	gchar *stderr_output = NULL;

	gboolean success = g_spawn_sync(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, 
		&stdout_output, &stderr_output, &exit_status, &error );

	if (!success)
	{
		g_warning("Failed to run command: %s", error->message);
		g_error_free(error);
	}
	else
	{
		gtk_main_quit();
	}

	g_free(stdout_output);
	g_free(stderr_output);
	g_strfreev(argv);
}

void on_submenu_item3_selected(GtkMenuItem *menuitem, gpointer userdata) 
{
	dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "SGLogout");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright © 2025 ItsZariep");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "Simple GTK Session Manager");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://codeberg.org/itszariep/sglogout");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), "Project WebSite");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog),"system-shutdown");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


void create_window(void)
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "SGLogout");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);
	gtk_layer_init_for_window(GTK_WINDOW(window));
	gtk_window_set_accept_focus(GTK_WINDOW(window), TRUE);
	gtk_layer_set_keyboard_mode(GTK_WINDOW(window), GTK_LAYER_SHELL_KEYBOARD_MODE_ON_DEMAND);
	gtk_widget_grab_focus(window);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //is commented to prevent destroying process when destroying window

	theme = gtk_icon_theme_get_default();
	info = gtk_icon_theme_lookup_icon(theme, "system-shutdown", 48, 0);
	if (info != NULL)
	{
		GdkPixbuf *icon = gtk_icon_info_load_icon(info, NULL);
		gtk_window_set_icon(GTK_WINDOW(window), icon);
		g_object_unref(icon);
		g_object_unref(info);
	}

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	gint omode;

	if (postxt == 0)
	{
		omode = GTK_ORIENTATION_HORIZONTAL;
	}
	else if (postxt == 1)
	{
		omode = GTK_ORIENTATION_VERTICAL;
	}

		shutdown_box = gtk_box_new(omode, 5);
		reboot_box = gtk_box_new(omode, 5);
		sleep_box = gtk_box_new(omode, 5);
		hibernate_box = gtk_box_new(omode, 5);
		killall_box = gtk_box_new(omode, 5);
		lock_box = gtk_box_new(omode, 5);
		logout_box = gtk_box_new(omode, 5);

		// Shut down
		shutdown_btn = gtk_button_new();
			shutdown_ico = gtk_image_new_from_icon_name("system-shutdown", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(shutdown_ico), iconsize);
			shutdown_txt = gtk_label_new("Shut down");
			g_object_set_data(G_OBJECT(shutdown_btn), "command", shutdowncmd);

		// Reboot
		reboot_btn = gtk_button_new();
			reboot_ico = gtk_image_new_from_icon_name("system-reboot", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(reboot_ico), iconsize);
			reboot_txt = gtk_label_new("Reboot");
			g_object_set_data(G_OBJECT(reboot_btn), "command", rebootcmd);

		// Suspend
		sleep_btn = gtk_button_new();
			sleep_ico = gtk_image_new_from_icon_name("system-suspend", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(sleep_ico), iconsize);
			sleep_txt = gtk_label_new("Suspend");
			g_object_set_data(G_OBJECT(sleep_btn), "command", suspendcmd);

		// Hibernate
		hibernate_btn = gtk_button_new();
			hibernate_ico = gtk_image_new_from_icon_name("system-hibernate", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(hibernate_ico), iconsize);
			hibernate_txt = gtk_label_new("Hibernate");
			g_object_set_data(G_OBJECT(hibernate_btn), "command", hibernatecmd);

		// Kill all
		killall_btn = gtk_button_new();
			killall_ico = gtk_image_new_from_icon_name("window-close", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(killall_ico), iconsize);
			killall_txt = gtk_label_new("Close all windows");
			g_object_set_data(G_OBJECT(killall_btn), "command", closeallcmd);

		// Lock screen
		lock_btn = gtk_button_new();
			lock_ico = gtk_image_new_from_icon_name("lock", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(lock_ico), iconsize);
			lock_txt = gtk_label_new("Lock screen");
			g_object_set_data(G_OBJECT(lock_btn), "command", lockcmd);

		// Logout
		logout_btn = gtk_button_new();
			logout_ico = gtk_image_new_from_icon_name("system-log-out", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(logout_ico), iconsize);
			logout_txt = gtk_label_new("Logout");
			g_object_set_data(G_OBJECT(logout_btn), "command", logoutcmd);


		//Add icon to box
		if (showicons == 1)
		{
			gtk_container_add(GTK_CONTAINER(shutdown_box), shutdown_ico);
			gtk_container_add(GTK_CONTAINER(reboot_box), reboot_ico);
			gtk_container_add(GTK_CONTAINER(sleep_box), sleep_ico);
			gtk_container_add(GTK_CONTAINER(hibernate_box), hibernate_ico);
			gtk_container_add(GTK_CONTAINER(killall_box), killall_ico);
			gtk_container_add(GTK_CONTAINER(lock_box), lock_ico);
			gtk_container_add(GTK_CONTAINER(logout_box), logout_ico);
		}

		//add text next to icon, into the box
		if (showtext == 1)
		{
			gtk_container_add(GTK_CONTAINER(shutdown_box), shutdown_txt);
			gtk_container_add(GTK_CONTAINER(reboot_box), reboot_txt);
			gtk_container_add(GTK_CONTAINER(sleep_box), sleep_txt);
			gtk_container_add(GTK_CONTAINER(hibernate_box), hibernate_txt);
			gtk_container_add(GTK_CONTAINER(killall_box), killall_txt);
			gtk_container_add(GTK_CONTAINER(lock_box), lock_txt);
			gtk_container_add(GTK_CONTAINER(logout_box), logout_txt);
		}
		//add the full box into the button
			gtk_container_add(GTK_CONTAINER(shutdown_btn), shutdown_box);
			gtk_container_add(GTK_CONTAINER(reboot_btn), reboot_box);
			gtk_container_add(GTK_CONTAINER(sleep_btn), sleep_box);
			gtk_container_add(GTK_CONTAINER(hibernate_btn), hibernate_box);
			gtk_container_add(GTK_CONTAINER(killall_btn), killall_box);
			gtk_container_add(GTK_CONTAINER(lock_btn), lock_box);
			gtk_container_add(GTK_CONTAINER(logout_btn), logout_box);
		
	int ea;
		if (showicons == 0 && showtext == 0)
		{
			ea = 1;
		}

	if (ea == 1)
	{
		gtk_grid_attach(GTK_GRID(grid), gtk_label_new("You have hidden the icons and the text, what did you expect to happen?"), 0, 0, 6, 6); 
	}
	else
	{
		if (layout == 0)
		{
			gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
			gtk_grid_attach(GTK_GRID(grid), shutdown_btn,  0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), reboot_btn,    0, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), sleep_btn,     0, 2, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), hibernate_btn, 0, 3, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), killall_btn,   0, 4, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), lock_btn,      0, 5, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), logout_btn,    0, 6, 1, 1);
		}
		else if (layout == 1)
		{
			gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
			gtk_grid_attach(GTK_GRID(grid), shutdown_btn,  0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), reboot_btn,    1, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), sleep_btn,     2, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), hibernate_btn, 3, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), killall_btn,   4, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), lock_btn,      5, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), logout_btn,    6, 0, 1, 1);
		}
		else if (layout == 2)
		{
			gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
			gtk_grid_attach(GTK_GRID(grid), shutdown_btn,  0, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), reboot_btn,    1, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), sleep_btn,     2, 0, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), hibernate_btn, 0, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), killall_btn,   1, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), lock_btn,      2, 1, 1, 1);
			gtk_grid_attach(GTK_GRID(grid), logout_btn,    1, 2, 1, 1);
		}
	}

		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_widget_show_all(window);

		int windowWidth, windowHeight;
		gtk_window_get_size(GTK_WINDOW(window), &windowWidth, &windowHeight);

	switch (position)
	{
		case 0: // Top - Left
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
			break;
		case 1: // Top - Center
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
			// You may want to center horizontally by setting margins or alignment
			break;
		case 2: // Top - Right
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
			break;
		case 3: // Middle - Left
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, false);
			// Center vertically by margins or alignment
			break;
		case 4: // Middle - Center
			// No anchors set to edges; center window both vertically and horizontally
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, false);
			// Use gtk_layer_set_margin or set window alignment to center it
			break;
		case 5: // Middle - Right
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, false);
			// Center vertically by margins or alignment
			break;
		case 6: // Bottom - Left
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, false);
			break;
		case 7: // Bottom - Center
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, false);
			// Center horizontally by margins or alignment
			break;
		case 8: // Bottom - Right
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, true);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, false);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, false);
			break;
	}

	g_signal_connect(shutdown_btn, "clicked", G_CALLBACK(run_command), shutdown_btn);
	g_signal_connect(reboot_btn, "clicked", G_CALLBACK(run_command), reboot_btn);
	g_signal_connect(sleep_btn, "clicked", G_CALLBACK(run_command), sleep_btn);
	g_signal_connect(hibernate_btn, "clicked", G_CALLBACK(run_command), hibernate_btn);
	g_signal_connect(killall_btn, "clicked", G_CALLBACK(run_command), killall_btn);
	g_signal_connect(lock_btn, "clicked", G_CALLBACK(run_command), lock_btn);
	g_signal_connect(logout_btn, "clicked", G_CALLBACK(run_command), logout_btn);
	g_signal_connect(window, "key-release-event", G_CALLBACK(on_key_press), 0);
	g_signal_connect(window, "focus-out-event", G_CALLBACK(on_focus_out), 0);
}
