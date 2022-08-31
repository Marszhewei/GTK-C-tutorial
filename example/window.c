#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data)       /* gpoint is void* */
{
    GtkWidget* window;
    

    // window = gtk_application_window_new(app);                       /* return GtkWidget*, 创建一个新的窗口 */
    window = gtk_window_new();
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "ToDo");               // arg :    GtkWindow* string       GTK_WINDOW是一个宏,来实现类型转换      设置标题
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);      // 设置窗口大小
    gtk_widget_show(window);                        // 显示窗口


    /* GtkWidget* window1;             // 可以创建多个窗口程序

    window1 = gtk_application_window_new(app);                 
    gtk_window_set_title(GTK_WINDOW(window1), "1");              
    gtk_window_set_default_size(GTK_WINDOW(window1), 200, 200);      
    gtk_widget_show(window1);    */    
    
}

int main(int argc, char** argv)
{
    GtkApplication* app;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);         // 对GtkApplication进行初始化,参数为标志符和flag(有特殊有求的时候传)
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);                  // 连接到activate函数
    int status = g_application_run(G_APPLICATION(app), argc, argv);                 // 启动activate函数
    g_object_unref(app);            // 释放GtkApplication对象

    return status;
}
