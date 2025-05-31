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

GtkCssProvider *global_provider = NULL;
void loadcss(int load)
{
	if (load == 1)
	{
		if (global_provider != NULL)
		{
			g_warning("CSS is already loaded.");
			return;
		}

		gchar *data_dir = g_build_filename(g_get_user_data_dir(), "sglogout", NULL);
		gchar *css_path = g_build_filename(data_dir, "style.css", NULL);

		global_provider = gtk_css_provider_new();
		GdkDisplay *display = gdk_display_get_default();
		GdkScreen *screen = gdk_display_get_default_screen(display);

		gtk_style_context_add_provider_for_screen(
			screen,
			GTK_STYLE_PROVIDER(global_provider),
			GTK_STYLE_PROVIDER_PRIORITY_USER
		);

		GError *error = NULL;

		gtk_css_provider_load_from_path(global_provider, css_path, &error);

		if (error != NULL)
		{
			g_warning("Could not load CSS from %s: %s", css_path, error->message);
			g_error_free(error);
		}

		g_free(data_dir);
		g_free(css_path);
	}
	else if (load == 0)
	{
		if (global_provider == NULL)
		{
			return;
		}

		GdkDisplay *display = gdk_display_get_default();
		GdkScreen *screen = gdk_display_get_default_screen(display);

		gtk_style_context_remove_provider_for_screen(screen,GTK_STYLE_PROVIDER(global_provider));

		g_object_unref(global_provider);
		global_provider = NULL;
	}
	else
	{
		return;
	}
}

void add_button_if_cmd_valid(GPtrArray *arr, const char *cmd, GtkWidget *btn)
{
	if (cmd != NULL && cmd[0] != '\0')
	{
		g_ptr_array_add(arr, btn);
	}
}

void create_window(void)
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "SGLogout");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_layer_init_for_window(GTK_WINDOW(window));
	gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_OVERLAY);
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

	gint omode = 0;

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
			g_object_set_data(G_OBJECT(shutdown_btn), "label", "Shut down");

		// Reboot
		reboot_btn = gtk_button_new();
			reboot_ico = gtk_image_new_from_icon_name("system-reboot", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(reboot_ico), iconsize);
			reboot_txt = gtk_label_new("Reboot");
			g_object_set_data(G_OBJECT(reboot_btn), "command", rebootcmd);
			g_object_set_data(G_OBJECT(reboot_btn), "label", "Reboot");

		// Suspend
		sleep_btn = gtk_button_new();
			sleep_ico = gtk_image_new_from_icon_name("system-suspend", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(sleep_ico), iconsize);
			sleep_txt = gtk_label_new("Suspend");
			g_object_set_data(G_OBJECT(sleep_btn), "command", suspendcmd);
			g_object_set_data(G_OBJECT(sleep_btn), "label", "Suspend");

		// Hibernate
		hibernate_btn = gtk_button_new();
			hibernate_ico = gtk_image_new_from_icon_name("system-hibernate", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(hibernate_ico), iconsize);
			hibernate_txt = gtk_label_new("Hibernate");
			g_object_set_data(G_OBJECT(hibernate_btn), "command", hibernatecmd);
			g_object_set_data(G_OBJECT(hibernate_btn), "label", "Hibernate");

		// Kill all
		killall_btn = gtk_button_new();
			killall_ico = gtk_image_new_from_icon_name("window-close", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(killall_ico), iconsize);
			killall_txt = gtk_label_new("Close all windows");
			g_object_set_data(G_OBJECT(killall_btn), "command", closeallcmd);
			g_object_set_data(G_OBJECT(killall_btn), "label", "Close all windows");

		// Lock screen
		lock_btn = gtk_button_new();
			lock_ico = gtk_image_new_from_icon_name("lock", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(lock_ico), iconsize);
			lock_txt = gtk_label_new("Lock screen");
			g_object_set_data(G_OBJECT(lock_btn), "command", lockcmd);
			g_object_set_data(G_OBJECT(lock_btn), "label", "Lock screen");

		// Logout
		logout_btn = gtk_button_new();
			logout_ico = gtk_image_new_from_icon_name("system-log-out", GTK_ICON_SIZE_INVALID);
			gtk_image_set_pixel_size(GTK_IMAGE(logout_ico), iconsize);
			logout_txt = gtk_label_new("Logout");
			g_object_set_data(G_OBJECT(logout_btn), "command", logoutcmd);
			g_object_set_data(G_OBJECT(logout_btn), "label", "Logout");


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
		
	int ea = 0;
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
		GPtrArray *buttons = g_ptr_array_new_with_free_func(NULL);

		if (*shutdowncmd != '\0') {g_ptr_array_add(buttons, shutdown_btn);}
		if (*rebootcmd != '\0') {g_ptr_array_add(buttons, reboot_btn);}
		if (*suspendcmd != '\0') {g_ptr_array_add(buttons, sleep_btn);}
		if (*hibernatecmd != '\0') {g_ptr_array_add(buttons, hibernate_btn);}
		if (*closeallcmd != '\0') {g_ptr_array_add(buttons, killall_btn);}
		if (*lockcmd != '\0') {g_ptr_array_add(buttons, lock_btn);}
		if (*logoutcmd != '\0') g_ptr_array_add(buttons, logout_btn);

		int columns = 1;
		if (layout == 0)
		{
			columns = 1;
		}
		else if (layout == 1)
		{
			columns = 9;
		}
		else if (layout == 2)
		{
			columns = (gridlayout_cols > 0) ? gridlayout_cols : 1;
		}

		guint num_buttons = buttons->len;
		guint last_row_items = num_buttons % columns;
		if (last_row_items == 0)
		{
			last_row_items = columns;
		}

		gboolean columns_odd = (columns % 2 == 1);
		gboolean last_row_odd = (last_row_items % 2 == 1);

		gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

		guint total_rows = (num_buttons + columns - 1) / columns;

		for (guint i = 0; i < num_buttons; i++)
		{
			guint row = i / columns;
			guint col = i % columns;

			if (autogridadjustment == 1)
			{
				if (position == 1 || position == 2 || position  ==  4 || position  == 5)
				{
					// Adjust last row (normal, no inversion)
					if (row == total_rows - 1)
					{
						guint item_in_last_row = i % columns;

						if (!columns_odd && !last_row_odd)
						{
							guint offset = (columns - last_row_items) / 2;
							col = item_in_last_row + offset;
						}
						else if (columns_odd && last_row_odd)
						{
							guint offset = (columns - last_row_items) / 2;
							col = item_in_last_row + offset;
						}
						else if (columns_odd && !last_row_odd)
						{
							if (item_in_last_row < last_row_items / 2)
							{
								col = item_in_last_row;
							}
							else
							{
								col = columns - (last_row_items - item_in_last_row);
							}
						}
						else if (!columns_odd && last_row_odd)
						{
							col = item_in_last_row;
						}
					}
				}
				else if (position == 6 || position == 7 || position == 8)
				{
					// Invert rows vertically:
					row = total_rows - 1 - row;

					// Recalculate last_row_items for inverted layout (still same count)
					// Apply adjustment to first row after inversion (which was previously last row)
					if (row == 0)  // after inversion, bottom row is now row 0
					{
						guint item_in_first_row = i % columns;
						guint first_row_items = last_row_items;
						gboolean first_row_odd = (first_row_items % 2 == 1);

						if (!columns_odd && !first_row_odd)
						{
							guint offset = (columns - first_row_items) / 2;
							col = item_in_first_row + offset;
						}
						else if (columns_odd && first_row_odd)
						{
							guint offset = (columns - first_row_items) / 2;
							col = item_in_first_row + offset;
						}
						else if (columns_odd && !first_row_odd)
						{
							if (item_in_first_row < first_row_items / 2)
							{
								col = item_in_first_row;
							}
							else
							{
								col = columns - (first_row_items - item_in_first_row);
							}
						}
						else if (!columns_odd && first_row_odd)
						{
							col = item_in_first_row;
						}
					}
				}
			}

			GtkWidget *button = g_ptr_array_index(buttons, i);
			gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
		}
		g_ptr_array_free(buttons, TRUE);
	}

		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_widget_show_all(window);

		int windowWidth, windowHeight;
		gtk_window_get_size(GTK_WINDOW(window), &windowWidth, &windowHeight);

	switch (position)
	{
		case 0: // Top - Left
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
			break;
		case 1: // Top - Center
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
			// You may want to center horizontally by setting margins or alignment
			break;
		case 2: // Top - Right
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
			break;
		case 3: // Middle - Left
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
			// Center vertically by margins or alignment
			break;
		case 4: // Middle - Center
			// No anchors set to edges; center window both vertically and horizontally
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
			// Use gtk_layer_set_margin or set window alignment to center it
			break;
		case 5: // Middle - Right
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
			// Center vertically by margins or alignment
			break;
		case 6: // Bottom - Left
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
			break;
		case 7: // Bottom - Center
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
			// Center horizontally by margins or alignment
			break;
		case 8: // Bottom - Right
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 1);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
			gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
			break;
	}

	loadcss(customcss);
	g_signal_connect(shutdown_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(reboot_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(sleep_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(hibernate_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(killall_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(lock_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(logout_btn, "clicked", G_CALLBACK(run_command), window);
	g_signal_connect(window, "key-release-event", G_CALLBACK(on_key_press), 0);
	//g_signal_connect(window, "focus-out-event", G_CALLBACK(on_focus_out), 0);
}
