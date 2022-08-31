#include <gtk/gtk.h>

static void app_activate(GApplication *app, gpointer user_data)
{           // 未传参数则调用该函数
    g_print("You need a filename argument.\n");
}

static void app_open(GApplication *app, GFile **files, gint n_files, gchar *hint, gpointer user_data)
{           // 传递了参数的话就调用该函数
    GtkWidget *win;
    GtkWidget *scr;
    GtkWidget *tv;
    GtkTextBuffer *tb;
    char *contents;
    gsize length;
    char *filename;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    scr = gtk_scrolled_window_new();
    gtk_window_set_child(GTK_WINDOW(win), scr);

    tv = gtk_text_view_new();
    tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(tv), TRUE);      // TURE: we can edit the file
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv);    // tv --> scr

    if (g_file_load_contents(files[0], NULL, &contents, &length, NULL, NULL)) {
        // g_print("%zd\n", length);
        // g_print("%s", contents);
        gtk_text_buffer_set_text(tb, contents, length);
        g_free(contents);
        contents = NULL;
        if ((filename = g_file_get_basename(files[0])) != NULL) {
            gtk_window_set_title(GTK_WINDOW(win), filename); // 如果我们传入的文件名不为空,设置标题为filename
            g_free(filename);
            filename = NULL;
        }
        gtk_widget_show(win);
    }
    else {      // file 不存在
        char *pathname;
        if ((pathname = g_file_get_path(files[0])) != NULL) {
            g_print("No such file: %s.\n", pathname);
            g_free(pathname);
            pathname = NULL;
        }
        gtk_window_destroy(GTK_WINDOW(win));
    }
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.ToshioCP.tfv3", G_APPLICATION_HANDLES_OPEN);              //! use G_APPLICATION_HANDLES_OPEN
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    g_signal_connect(app, "open", G_CALLBACK(app_open), NULL);             
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return stat;
}