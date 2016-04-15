#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>

#include <file.h>

#include "res.h"

GtkBuilder* builder;

GtkWidget* tFilename;
GtkWidget* tContent;

GObject* bSave;

gchar* get_content(GtkWidget* widget)
{
	GtkTextBuffer* b = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	GtkTextIter start;
	GtkTextIter end;
	
	gtk_text_buffer_get_start_iter(b, &start);
	gtk_text_buffer_get_end_iter(b, &end);
	
	return gtk_text_buffer_get_text(b, &start, &end, true);
}

void set_boxes(const char* filename)
{
	gchar* content;
	gtk_entry_set_text(GTK_ENTRY(tFilename), filename);
	
	g_file_get_contents(filename, &content, NULL, NULL);
	
	GtkTextBuffer* b = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(b, content, -1);
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(tContent), b);
}

static void
save_file(GtkWidget* parent, gpointer data)
{
	File file;
	const char* filename = gtk_entry_get_text(GTK_ENTRY(tFilename));
	gchar* content = get_content(tContent);
	
	file.writeToFile(filename, content);
}

static void
open_file(GtkWidget* parent, gpointer data)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	
	dialog = gtk_file_chooser_dialog_new("Open File",
											NULL,
											action,
											"Cancel",
											GTK_RESPONSE_CANCEL,
											"Open",
											GTK_RESPONSE_ACCEPT,
											NULL);
	
	gint res = gtk_dialog_run(GTK_DIALOG(dialog));
	if(res == GTK_RESPONSE_ACCEPT)
	{
		char* filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		set_boxes(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	GObject* window;
	
	GObject* mOpen;
	GObject* mQuit;
	GObject* mSave;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_resource(builder, "/com/kalebklein/gtk/window.glade", NULL);
	
	window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	tFilename = GTK_WIDGET(gtk_builder_get_object(builder, "tFilename"));
	tContent = GTK_WIDGET(gtk_builder_get_object(builder, "tContent"));
	
	bSave = gtk_builder_get_object(builder, "bSave");
	g_signal_connect(bSave, "clicked", G_CALLBACK(save_file), NULL);
	
	mQuit = gtk_builder_get_object(builder, "menuQuit");
	g_signal_connect(mQuit, "activate", G_CALLBACK(gtk_main_quit), NULL);
	
	mOpen = gtk_builder_get_object(builder, "menuOpen");
	g_signal_connect(mOpen, "activate", G_CALLBACK(open_file), NULL);
	
	mSave = gtk_builder_get_object(builder, "menuSave");
	g_signal_connect(mSave, "activate", G_CALLBACK(save_file), NULL);
	
	gtk_main();
	
	return 0;
}
