#include "about.h"

void open_about_dialog(GtkWidget* parent, gpointer data)
{
	static const gchar* const authors[] = {
		"Kaleb Klein <klein.jae@gmail.com>",
		NULL
	};

	static const gchar copyright[] = "Copyright \xc2\xa9 2016 Kaleb Klein";

	static const gchar comments[] = \
		N_("My Gtk App is a simple text editor built in GTK+ 3");

	GdkPixbuf* logo;

	logo = gdk_pixbuf_new_from_resource("/com/kalebklein/gtk/pixmaps/gedit.png", NULL);

	gtk_show_about_dialog(NULL,
		"program-name", "My Gtk App",
		"authors", authors,
		"comments", _(comments),
		"copyright", copyright,
		"license-type", GTK_LICENSE_GPL_2_0,
		"logo", logo,
		"version", "1.0",
		"website", "http://kalebklein.com",
		"website-label", "kalebklein.com",
		NULL);

	g_clear_object(&logo);
}