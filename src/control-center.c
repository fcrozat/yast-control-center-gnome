#include "config.h"
#include <string.h>
#include <gtk/gtkicontheme.h>
#include <libgnome/gnome-desktop-item.h>
#include <libgnomeui/libgnomeui.h>
#include <libgnome/gnome-i18n.h>
#include <dirent.h>

#include "app-shell.h"
#include "app-shell-startup.h"
#include "slab-gnome-util.h"

void handle_static_action_clicked(Tile * tile, TileEvent * event, gpointer data);
static GSList * get_actions_list();

#define CONTROL_CENTER_PREFIX             "/desktop/gnome/applications/y2cc-gnome/cc_"
#define CONTROL_CENTER_ACTIONS_LIST_KEY   (CONTROL_CENTER_PREFIX "actions_list")
#define CONTROL_CENTER_ACTIONS_SEPARATOR  ";"
#define EXIT_SHELL_ON_STATIC_ACTION       "exit_shell_on_static_action"

static GSList *
get_actions_list ()
{
	GSList *l;
	GSList *key_list;
	GSList *actions_list = NULL;
	AppAction *action;

	key_list = get_slab_gconf_slist (CONTROL_CENTER_ACTIONS_LIST_KEY);
	if (!key_list)
	{
		g_warning (_("key not found [%s]\n"), CONTROL_CENTER_ACTIONS_LIST_KEY);
		return NULL;
	}

	for (l = key_list; l != NULL; l = l->next)
	{
		gchar *entry = (gchar *) l->data;
		gchar **temp;

		action = g_new (AppAction, 1);
		temp = g_strsplit (entry, CONTROL_CENTER_ACTIONS_SEPARATOR, 2);
		action->name = g_strdup (temp[0]);
		if ((action->item = load_desktop_item_from_unknown (temp[1])) == NULL)
		{
			g_warning ("get_actions_list() - PROBLEM - Can't load %s\n", temp[1]);
		}
		else
		{
			actions_list = g_slist_prepend (actions_list, action);
		}
		g_strfreev (temp);
		g_free (entry);
	}

	g_slist_free (key_list);

	return g_slist_reverse (actions_list);
}

void
handle_static_action_clicked (Tile * tile, TileEvent * event, gpointer data)
{
	if (event->type == TILE_EVENT_ACTIVATED_DOUBLE_CLICK)
		return;
	
	gchar *temp;

	AppShellData *app_data = (AppShellData *) data;
	GnomeDesktopItem *item =
		(GnomeDesktopItem *) g_object_get_data (G_OBJECT (tile), APP_ACTION_KEY);
	open_desktop_item_exec (item);

	temp = g_strdup_printf("%s%s", app_data->gconf_prefix, EXIT_SHELL_ON_STATIC_ACTION);
	if (get_slab_gconf_bool(temp))
		gtk_main_quit ();
	/* Use this block instead of above line as soon as we move to 1/2007 version of gnome-main-menu
	{
		if (app_data->exit_on_close)
			gtk_main_quit ();
		else
			hide_shell (app_data);
	}
	*/
	g_free (temp);
}

int
main (int argc, char *argv[])
{
	BonoboApplication *bonobo_app = NULL;
	gboolean hidden = FALSE;
	gchar * startup_id;
	AppShellData *app_data;
	GSList *actions;
	GnomeProgram *program;

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	if (argc > 1)
	{
		if (argc != 2 || strcmp ("-h", argv[1]))
		{
			printf ("Usage - y2controlcenter-gnome [-h]\n");
			printf ("Options: -h : hide on start\n");
			printf ("\tUseful if you want to autostart the control-center singleton so it can get all it's slow loading done\n");
			exit (1);
		}
		hidden = TRUE;
	}

	startup_id = g_strdup (g_getenv (DESKTOP_STARTUP_ID));
	program = gnome_program_init ("YaST2 GNOME Control Center", "0.1", LIBGNOMEUI_MODULE,
		argc, argv, NULL, NULL);

	if (apss_already_running (argc, argv, &bonobo_app, "YaST-gnome", startup_id))
	{
		gdk_notify_startup_complete ();
		bonobo_debug_shutdown ();
		g_free (startup_id);
		exit (1);
	}

	GtkIconTheme * theme;
	theme = gtk_icon_theme_get_default();
	gtk_icon_theme_prepend_search_path (theme, "/usr/share/YaST2/theme/NLD");

	app_data = appshelldata_new (
		"YaST-gnome.menu", NULL, CONTROL_CENTER_PREFIX, GTK_ICON_SIZE_LARGE_TOOLBAR);
	generate_categories (app_data);

	actions = get_actions_list ();
	layout_shell (app_data, _("Filter"), _("Groups"), _("Common Tasks"), actions,
		handle_static_action_clicked);

	g_signal_connect (bonobo_app, "new-instance", G_CALLBACK (apss_new_instance_cb), app_data);
	create_main_window (app_data, "MyControlCenter", _("Control Center"),
		"y2cc-gnome", 975, 600, hidden);

	if (bonobo_app)
		bonobo_object_unref (bonobo_app);
	bonobo_debug_shutdown ();
	g_free (startup_id);
	return 0;
};
