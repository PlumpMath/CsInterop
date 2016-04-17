#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gi18n.h>

#include <gtksourceview/gtksource.h>

#include <file.h>

#include "about.h"

GtkBuilder* builder;

GtkWidget* tFilename;

GtkWidget* view;
GtkWidget* scroll;
GtkSourceBuffer *buf;
GtkSourceLanguage* lang;
GtkSourceLanguageManager* lm;


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
	gtk_entry_set_text(GTK_ENTRY(tFilename), filename);

	if(buf != NULL)
	{
		GtkTextIter start;
		GtkTextIter end;
		
		gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buf), &start);
		gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buf), &end);

		gtk_text_buffer_delete(GTK_TEXT_BUFFER(buf), &start, &end);
	}
	else
	{
		buf = gtk_source_buffer_new(NULL);
	}

	char* c_type;
	gboolean unknown;

	c_type = g_content_type_guess(filename, NULL, 0, &unknown);
	if(unknown)
	{
		g_free(c_type);
		c_type = NULL;
	}

	gchar* content;
	g_file_get_contents(filename, &content, NULL, NULL);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buf), content, -1);

	lm = gtk_source_language_manager_new();
	lang = gtk_source_language_manager_guess_language(lm, filename, c_type);
	gtk_source_buffer_set_language(buf, lang);

	view = gtk_source_view_new_with_buffer(buf);
	gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(view), true);
	gtk_source_view_set_auto_indent(GTK_SOURCE_VIEW(view), true);

	gtk_container_add(GTK_CONTAINER(scroll), GTK_WIDGET(view));
	gtk_widget_show_all(GTK_WIDGET(view));
}

static void
save_file(GtkWidget* parent, gpointer data)
{
	File file;
	const char* filename = gtk_entry_get_text(GTK_ENTRY(tFilename));
	gchar* content = get_content(view);
	
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
		_("_Cancel"),
		GTK_RESPONSE_CANCEL,
		_("_Open"),
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
	GObject* mAbout;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_resource(builder, "/com/kalebklein/gtk/ui/window.ui", NULL);
	
	window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	tFilename = GTK_WIDGET(gtk_builder_get_object(builder, "tFilename"));
	scroll = GTK_WIDGET(gtk_builder_get_object(builder, "scrollView"));
	
	mQuit = gtk_builder_get_object(builder, "menuQuit");
	g_signal_connect(mQuit, "activate", G_CALLBACK(gtk_main_quit), NULL);
	
	mOpen = gtk_builder_get_object(builder, "menuOpen");
	g_signal_connect(mOpen, "activate", G_CALLBACK(open_file), NULL);
	
	mSave = gtk_builder_get_object(builder, "menuSave");
	g_signal_connect(mSave, "activate", G_CALLBACK(save_file), NULL);

	mAbout = gtk_builder_get_object(builder, "menuAbout");
	g_signal_connect(mAbout, "activate", G_CALLBACK(open_about_dialog), NULL);
	
	gtk_main();
	
	return 0;
}
