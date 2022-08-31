#include <gtk/gtk.h>

static void print_button_delete(GtkWidget *widget, gpointer data)
{
    g_print("Delete\n");
}

static void print_button_add(GtkWidget *widget, gpointer data)
{
    g_print("Add\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;

    /* 创建一个新窗口，并设置其标题 */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "ToDo");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    /* 在这里，我们构造了将要打包按钮的容器 */
    GtkWidget *grid = gtk_grid_new();
    /* 在窗口中打包容器 */
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button = gtk_button_new_with_label("Add");
    g_signal_connect(button, "clicked", G_CALLBACK(print_button_add), NULL);
    /* 将第一个按钮放在网格单元格 (0, 0) 中，并使其填充 * 水平和垂直仅 1 个单元格（即没有跨越）*/
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    button = gtk_button_new_with_label("Delete");
    g_signal_connect(button, "clicked", G_CALLBACK(print_button_delete), NULL);
    /* 将第二个按钮放在网格单元格 (1, 0) 中，并使其在水平和垂直方向仅填充 * 1 个单元格（即没有跨越）*/
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);
    /* 将退出按钮放在网格单元格 (0, 1) 中，并使其 * 跨越 2 列。*/
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 2, 1);

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