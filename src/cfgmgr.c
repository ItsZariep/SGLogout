#include "cfgmgr.h"

GtkWidget *gcloseallcmd;
GtkWidget *ghibernatecmd;
GtkWidget *glockscreencmd;
GtkWidget *glogoutcmd;
GtkWidget *gpwroffcmd;
GtkWidget *grebootcmd;
GtkWidget *gcloseallcmd;
GtkWidget *gsuspendcmd;
GtkWidget *glayout;
GtkWidget *gposition;
GtkWidget *giconsize;
GtkWidget *gshowconfirm;
GtkWidget *gpostxt;
GtkWidget *gshowtxt;
GtkWidget *gshowico;
GtkWidget *gcustomcss;
GtkWidget *ggridlayout_cols_label;
GtkWidget *ggridlayout_cols;
GtkWidget *gautogridadjustment;

#define XA 0.0f
#define XM 4

static void on_glayout_changed(GtkComboBox *combo, gpointer user_data)
{

	if (gtk_combo_box_get_active(combo) == 2)
	{
		gtk_widget_show(ggridlayout_cols_label);
		gtk_widget_show(ggridlayout_cols);
		gtk_widget_show(gautogridadjustment);
	}
	else
	{
		gtk_widget_hide(ggridlayout_cols_label);
		gtk_widget_hide(ggridlayout_cols);
		gtk_widget_hide(gautogridadjustment);
	}
}

void on_save_button_clicked(GtkWidget *dummy, gpointer data)
{
	layout = gtk_combo_box_get_active(GTK_COMBO_BOX(glayout));
	autogridadjustment = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gautogridadjustment));

	const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(ggridlayout_cols));
		gchar *endptr;
		guint64 result = g_ascii_strtoull(entry_text, &endptr, 10);
		gridlayout_cols = (guint) result;

	position = gtk_combo_box_get_active(GTK_COMBO_BOX(gposition));
	iconsize = gtk_spin_button_get_value(GTK_SPIN_BUTTON(giconsize));
	showicons = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowico));
	showconfirm = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowconfirm));
	showtext = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gshowtxt));
	postxt = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gpostxt));
	customcss = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gcustomcss));

	closeallcmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(gcloseallcmd))); 
	hibernatecmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(ghibernatecmd))); 
	lockcmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(glockscreencmd))); 
	logoutcmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(glogoutcmd))); 
	shutdowncmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(gpwroffcmd))); 
	rebootcmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(grebootcmd))); 
	suspendcmd = g_strdup(gtk_entry_get_text(GTK_ENTRY(gsuspendcmd))); 

	saveconf();
	gint input = GPOINTER_TO_INT(data);
	if (input == 1) {gtk_main_quit();}
}

GtkIconTheme *theme;
GtkIconInfo *info;
GdkPixbuf *icon;

void showcfg(void)
{
	GtkWidget *cfgdialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(cfgdialog), "Settings - SGLogout");
	gtk_container_set_border_width(GTK_CONTAINER(cfgdialog), 10);

	theme = gtk_icon_theme_get_default();
	info = gtk_icon_theme_lookup_icon(theme, "system-shutdown", 48, 0);
	if (info != NULL)
	{
		GdkPixbuf *icon = gtk_icon_info_load_icon(info, NULL);
		gtk_window_set_icon(GTK_WINDOW(cfgdialog), icon);
		g_object_unref(icon);
		g_object_unref(info);
	}

	g_signal_connect(cfgdialog, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(cfgdialog), vbox);
	GtkWidget *notebook = gtk_notebook_new();
	gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

	GtkWidget *settings_tab = gtk_grid_new();
		gtk_grid_set_column_homogeneous(GTK_GRID(settings_tab), TRUE);

		GtkWidget *glayout_label = gtk_label_new("Item layout:");
			gtk_label_set_xalign(GTK_LABEL(glayout_label), XA);
			gtk_widget_set_margin_start(glayout_label, XM);
		glayout = gtk_combo_box_text_new();
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(glayout), "Vertical");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(glayout), "Horizontal");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(glayout), "Grid");

		ggridlayout_cols_label = gtk_label_new("Grid columns:");
			gtk_label_set_xalign(GTK_LABEL(ggridlayout_cols_label), XA);
			gtk_widget_set_margin_start(ggridlayout_cols_label, XM);
		GtkAdjustment *cols_adjustment = gtk_adjustment_new(1, 1, 7, 1, 1, 0);
			ggridlayout_cols = gtk_spin_button_new(cols_adjustment, 1, 0);
		gautogridadjustment =  gtk_check_button_new_with_label("Auto-adjust grid items");
			gtk_widget_set_direction(gautogridadjustment, GTK_TEXT_DIR_RTL);

		GtkWidget *gposition_label = gtk_label_new("Window Position:");
			gtk_label_set_xalign(GTK_LABEL(gposition_label), XA);
			gtk_widget_set_margin_start(gposition_label, XM);
		gposition = gtk_combo_box_text_new();
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Top - Left");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Top - Center");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Top - Right");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Middle - Left");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Middle - Center");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Middle - Right");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Bottom - Left");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Bottom - Center");
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(gposition), "Bottom - Right");

		GtkWidget *giconsize_label = gtk_label_new("Icon Size:");
			gtk_label_set_xalign(GTK_LABEL(giconsize_label), XA);
			gtk_widget_set_margin_start(giconsize_label, XM);
		GtkAdjustment *icon_adjustment = gtk_adjustment_new(1, 0, 1024, 1, 1, 0);
			giconsize = gtk_spin_button_new(icon_adjustment, 1, 0);

		gshowconfirm = gtk_check_button_new_with_label("Show Confirmation");
			gtk_widget_set_direction(gshowconfirm, GTK_TEXT_DIR_RTL);
		gshowico = gtk_check_button_new_with_label("Show icons");
			gtk_widget_set_direction(gshowico, GTK_TEXT_DIR_RTL);
		gshowtxt = gtk_check_button_new_with_label("Show text");
			gtk_widget_set_direction(gshowtxt, GTK_TEXT_DIR_RTL);
		gpostxt  = gtk_check_button_new_with_label("Text under icon");
			gtk_widget_set_direction(gpostxt, GTK_TEXT_DIR_RTL);
		gcustomcss  = gtk_check_button_new_with_label("Use custom CSS");
			gtk_widget_set_direction(gcustomcss, GTK_TEXT_DIR_RTL);

	GtkWidget *command_tab = gtk_grid_new();
		gtk_grid_set_column_homogeneous(GTK_GRID(command_tab), TRUE);

		GtkWidget *gcloseall_label = gtk_label_new("Close All Command:");
			gtk_label_set_xalign(GTK_LABEL(gcloseall_label), XA);
			gtk_widget_set_margin_start(gcloseall_label, XM);
		gcloseallcmd = gtk_entry_new();

		GtkWidget *ghibernate_label = gtk_label_new("Hibernate Command:");
			gtk_label_set_xalign(GTK_LABEL(ghibernate_label), XA);
			gtk_widget_set_margin_start(ghibernate_label, XM);
		ghibernatecmd = gtk_entry_new();

		GtkWidget *glockscreen_label = gtk_label_new("Lock Screen Command:");
			gtk_label_set_xalign(GTK_LABEL(glockscreen_label), XA);
			gtk_widget_set_margin_start(glockscreen_label, XM);
		glockscreencmd = gtk_entry_new();

		GtkWidget *glogout_label = gtk_label_new("Logout Command:");
			gtk_label_set_xalign(GTK_LABEL(glogout_label), XA);
			gtk_widget_set_margin_start(glogout_label, XM);
		glogoutcmd = gtk_entry_new();

		GtkWidget *gpwroff_label = gtk_label_new("Power Off Command:");
			gtk_label_set_xalign(GTK_LABEL(gpwroff_label), XA);
			gtk_widget_set_margin_start(gpwroff_label, XM);
		gpwroffcmd = gtk_entry_new();

		GtkWidget *greboot_label = gtk_label_new("Reboot Command:");
			gtk_label_set_xalign(GTK_LABEL(greboot_label), XA);
			gtk_widget_set_margin_start(greboot_label, XM);
		grebootcmd = gtk_entry_new();

		GtkWidget *gsuspend_label = gtk_label_new("Suspend Command:");
			gtk_label_set_xalign(GTK_LABEL(gsuspend_label), XA);
			gtk_widget_set_margin_start(gsuspend_label, XM);
		gsuspendcmd = gtk_entry_new();

	GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		gtk_box_set_homogeneous(GTK_BOX(button_box), FALSE);
		GtkWidget *about_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
		GtkWidget *image = gtk_image_new_from_icon_name("system-shutdown", GTK_ICON_SIZE_DIALOG);
			gtk_box_pack_start(GTK_BOX(about_page), image, FALSE, FALSE, 0);
		GtkWidget *label_program_name = gtk_label_new("SGLogout");
			gtk_box_pack_start(GTK_BOX(about_page), label_program_name, FALSE, FALSE, 0);
		GtkWidget *label_program_version = gtk_label_new(pver);
			gtk_box_pack_start(GTK_BOX(about_page), label_program_version, FALSE, FALSE, 0);
		GtkWidget *label_copyright = gtk_label_new("Copyright © 2025 ItsZariep");
			gtk_box_pack_start(GTK_BOX(about_page), label_copyright, FALSE, FALSE, 0);
		GtkWidget *label_comments = gtk_label_new("Simple GTK Session Manager");
			gtk_box_pack_start(GTK_BOX(about_page), label_comments, FALSE, FALSE, 0);
		GtkWidget *link = gtk_link_button_new_with_label("https://codeberg.org/itszariep/sglogout", "Project WebSite");
			gtk_box_pack_start(GTK_BOX(about_page), link, FALSE, FALSE, 0);


		GtkWidget *ok_button = gtk_button_new_with_label("OK");
		GtkWidget *apply_button = gtk_button_new_with_label("Apply");
		GtkWidget *cancel_button = gtk_button_new_with_label("Cancel");

#ifndef nolibs
	gtk_grid_attach(GTK_GRID(settings_tab), gposition_label, 0, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(settings_tab), gposition, 1, 1, 1, 1);
#endif
	gtk_grid_attach(GTK_GRID(settings_tab), glayout_label, 0, 2, 1, 1);
		gtk_grid_attach(GTK_GRID(settings_tab), glayout, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), ggridlayout_cols_label, 0, 3, 1, 1);
		gtk_grid_attach(GTK_GRID(settings_tab), ggridlayout_cols, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), gautogridadjustment, 0, 4, 2, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), giconsize_label, 0, 5, 1, 1);
		gtk_grid_attach(GTK_GRID(settings_tab), giconsize, 1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), gshowconfirm, 0, 6, 2, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), gshowico, 0, 7, 2, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), gshowtxt, 0, 8, 2, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), gpostxt, 0, 9, 2, 1);
	gtk_grid_attach(GTK_GRID(settings_tab), gcustomcss, 0, 10, 2, 1);

	gtk_grid_attach(GTK_GRID(command_tab), gcloseall_label, 0, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), gcloseallcmd, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(command_tab), ghibernate_label, 0, 1, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), ghibernatecmd, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(command_tab), glockscreen_label, 0, 2, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), glockscreencmd, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(command_tab), glogout_label, 0, 3, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), glogoutcmd, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(command_tab), gpwroff_label, 0, 4, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), gpwroffcmd, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(command_tab), greboot_label, 0, 5, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), grebootcmd, 1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(command_tab), gsuspend_label, 0, 6, 1, 1);
		gtk_grid_attach(GTK_GRID(command_tab), gsuspendcmd, 1, 6, 1, 1);



	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), settings_tab, gtk_label_new("Layout Settings"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), command_tab, gtk_label_new("Commands"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), about_page, gtk_label_new("About"));

	gtk_box_pack_end(GTK_BOX(button_box), apply_button, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(button_box), cancel_button, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(button_box), ok_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);


	g_signal_connect(glayout, "changed", G_CALLBACK(on_glayout_changed),NULL);

	g_signal_connect(ok_button, "clicked", G_CALLBACK(on_save_button_clicked), GINT_TO_POINTER(1));
	g_signal_connect(cancel_button, "clicked", G_CALLBACK(gtk_main_quit), cfgdialog);
	g_signal_connect(apply_button, "clicked", G_CALLBACK(on_save_button_clicked), GINT_TO_POINTER(0));

	gtk_combo_box_set_active(GTK_COMBO_BOX(gposition), position);
	gtk_combo_box_set_active(GTK_COMBO_BOX(glayout), layout);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(ggridlayout_cols), gridlayout_cols);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(giconsize), iconsize);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gautogridadjustment), autogridadjustment);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowconfirm), showconfirm);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowico), showicons);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gshowtxt), showtext);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gpostxt), postxt);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gcustomcss), customcss);

	gtk_entry_set_text(GTK_ENTRY(gcloseallcmd), closeallcmd); 
	gtk_entry_set_text(GTK_ENTRY(ghibernatecmd), hibernatecmd); 
	gtk_entry_set_text(GTK_ENTRY(glockscreencmd), lockcmd); 
	gtk_entry_set_text(GTK_ENTRY(glogoutcmd), logoutcmd); 
	gtk_entry_set_text(GTK_ENTRY(gpwroffcmd), shutdowncmd); 
	gtk_entry_set_text(GTK_ENTRY(grebootcmd), rebootcmd); 
	gtk_entry_set_text(GTK_ENTRY(gsuspendcmd), suspendcmd); 

	gtk_window_set_position(GTK_WINDOW(cfgdialog), GTK_WIN_POS_CENTER);
	gtk_widget_show_all(cfgdialog);
	on_glayout_changed(GTK_COMBO_BOX(glayout), NULL);	
	gtk_main();
}
