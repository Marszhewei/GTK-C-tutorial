#include <gtk/gtk.h>

static void click_cb(GtkButton *btn, gpointer user_data)
{
    GtkWindow *win = GTK_WINDOW(user_data);
    // gtk_window_destroy(win);
    gtk_window_close(win);
}

static void app_activate(GApplication *app, gpointer user_data)
{
    GtkWidget *win;
    GtkWidget *btn;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "lb3");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    btn = gtk_button_new_with_label("Quit");
    gtk_window_set_child(GTK_WINDOW(win), btn);
    g_signal_connect(btn, "clicked", G_CALLBACK(click_cb), win);  // 将 btn win 传递给了 click_cb

    gtk_widget_show(win);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}