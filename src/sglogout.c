#include "sglogout.h"


GOptionEntry entries[] =
{
	{ "cfg", 0, 0, G_OPTION_ARG_NONE, &sgcfg, "Open SGLogout settings", NULL },
	{"verbose", 0, 0, G_OPTION_ARG_NONE, &verbose, "Show verbose program messages", NULL},
	{ NULL }
};


int main(int argc, char *argv[]) 
{
	GOptionContext *context = g_option_context_new("");
	g_option_context_add_main_entries(context, entries, NULL);
	g_option_context_parse(context, &argc, &argv, NULL);

	readconf();

	gtk_init(&argc, &argv);

	if (sgcfg)
	{
		showcfg();
		return 0;
	}
	create_window();

	gtk_main();
	return 0;
}

