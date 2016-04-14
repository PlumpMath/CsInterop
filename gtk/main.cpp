#include <gtk/gtk.h>
#include <stdio.h>

#include <file.h>

#include "res.h"

GtkWidget* tFilename;
GtkWidget* tContent;
GObject* bSave;

static void
get_shit(GtkWidget* parent, gpointer data)
{
	File file;
	const char* filename = gtk_entry_get_text(GTK_ENTRY(tFilename));
	const char* content = gtk_entry_get_text(GTK_ENTRY(tContent));
	
	file.writeToFile(filename, content);
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	
	GtkBuilder* builder;
	GObject* window;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_resource(builder, "/com/kalebklein/window.glade", NULL);
	
	window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	tFilename = GTK_WIDGET(gtk_builder_get_object(builder, "tFilename"));
	tContent = GTK_WIDGET(gtk_builder_get_object(builder, "tContent"));
	
	bSave = gtk_builder_get_object(builder, "bSave");
	g_signal_connect(bSave, "clicked", G_CALLBACK(get_shit), NULL);
	
	gtk_main();
	
	return 0;
}
