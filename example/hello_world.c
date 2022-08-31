#include <gtk/gtk.h>


/* static void print_hello(GtkWidget* widget, gpointer data)
{
    g_print("Hello GTK.\n");
} */


static void print_hello(GtkWidget *widget, gpointer user_data)
{
    // GtkWidget *button = widget;
    // GtkWidget *window = user_data;
    g_print("Hello GTK.\n");
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);
}


static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window; /* window */
    GtkWidget *button; /* button */
    GtkWidget *box;    /* box */
    /* window <- box <- button */

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "ToDo");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // 创建一个box 垂直的 横
    // box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);  // 创建一个box 水平的 竖
    gtk_window_set_child(GTK_WINDOW(window), box); // 将box添加到window上

    button = gtk_button_new_with_label("Hello World");                    // 创建一个button
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL); // 连接print_hello函数上
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);
    gtk_box_append(GTK_BOX(box), button); // 把button添加到box上

    gtk_widget_show(window);
}


int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}