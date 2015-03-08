/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * GtkBrightnessControl doesn't include any license, you can do everything you want with this project.
 */

#include <config.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n.h>
#define MONITOR_SIZE 10

typedef int bool;
bool widget_mode;
char monitor[MONITOR_SIZE];

typedef struct _Private Private;
struct _Private
{
	/* ANJUTA: Widgets declaration for gtkbrightnesscontrol.ui - DO NOT REMOVE */
};

static Private* priv = NULL;

/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */

/* Called when the window is closed */
void
destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

static GtkWidget*
create_window (void)
{
	GtkWidget *window;
	GtkBuilder *builder;
	GError* error = NULL;

	/* For testing purpose, define TEST to use the local (not installed) ui file */
	//#define TEST
	#ifdef TEST
	#define UI_FILE "../src/gtkbrightnesscontrol.ui"
	char* ui_path = UI_FILE;
	#else
	char* ui_path = getenv("UI_PATH");
	#endif
	#define TOP_WINDOW "window"

	if (ui_path == NULL){
		printf("Critical Error: environment variable UI_PATH not defined\n");
		exit(1);
	}
	
	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, ui_path, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				ui_path);
        }

	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for gtkbrightnesscontrol.ui - DO NOT REMOVE */

	g_object_unref (builder);

	
	return window;
}

void getMonitor(char *monitor){
	FILE *fp = popen("xrandr | grep ' connected' | sed 's/ connected.*$//g'", "r");
	if (fp == NULL) {
		printf("Failed to run command to get monitor\n");
		exit(1);
	}
	fgets(monitor, MONITOR_SIZE-1, fp);
	pclose(fp);
	monitor[strlen(monitor)-1]='\0';
}


int
main (int argc, char *argv[])
{
	GtkWidget *window;
	const char widget[] = "--widget-mode";
	const char b_color[] = "--background-color";
	getMonitor(monitor);
	
#ifdef ENABLE_NLS

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	
	gtk_init (&argc, &argv);

	window = create_window ();

	gtk_widget_show (window);

	if ((argc > 1) && (strcmp(argv[1],widget)==0)){
		widget_mode=TRUE;
		gtk_window_set_decorated((GtkWindow*)window,FALSE);
		gtk_window_set_skip_taskbar_hint((GtkWindow*)window,TRUE);
		gtk_window_set_default_size ((GtkWindow*)window,30,157);
		if (argc == 4){
			GdkRGBA color;
			gdk_rgba_parse (&color, argv[3]); 
			gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &color);
		}
	}else{
		printf("Options:\n\t%s to set widget mode\n\t%s to set background color (e.g. \"#FFFFFF\" or \"red\" or \"rgba(255,0,200,0.8)\")\n", widget, b_color);
		widget_mode=FALSE;
	}

	gtk_main ();


	g_free (priv);


	return 0;
}



void setBrightness(int val){
	char cmd[100];
	sprintf(cmd,"xrandr --output %s --brightness %.2f\n",monitor,val/100.);
	int len = strlen(cmd);
	cmd[len-4]='.';
	system(cmd);
}

gboolean on_scale1_button_release_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	GtkAdjustment *adjustment = (GtkAdjustment *) G_OBJECT (user_data);
	int val = (int)gtk_adjustment_get_value(adjustment);
	setBrightness(val);
	return FALSE;
}


void
on_adjustment1_value_changed (GtkAdjustment *adjustment, gpointer user_data)
{
	int val = (int)gtk_adjustment_get_value(adjustment);
	if (val%10 == 0)
		setBrightness(val);

}

gboolean on_window_focus_out_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	if (widget_mode)
		gtk_widget_destroy(widget);
	return TRUE;
}
