// #include <gtk-3.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include <stdio.h>

static void quit_cb(GtkButton *button, gpointer user_data) { 
    GtkWindow *window = GTK_WINDOW(user_data);
    gtk_window_destroy(window);
    sleep(0.3);
    puts("You press the quit button.\nQuit sucessfully.");
}


static void click_cb(GtkButton *button, gpointer user_data) {
    const char *s;

    s = gtk_button_get_label (button);
    if (strcmp(s, "Click") == 0) {
        puts("You press the click button.");
        gtk_button_set_label (button, "Clicked");
    }
    else {
        puts("Click to cancel.");
        gtk_button_set_label (button, "Click");
    }
}



static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;                  // GtkWindow and GtkApplicationWindow can have only one child
    // GtkWidget* label;
    GtkWidget *box;
    GtkWidget *quit_btn;
    GtkWidget *click_btn;


    // window = gtk_application_window_new(app);                       // return GtkWidget*, 创建一个新的窗口
    window = gtk_window_new();
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "ToDo");                   // arg :    GtkWindow* string       GTK_WINDOW是一个宏,来实现类型转换      设置标题
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);          // 设置窗口大小



    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    gtk_window_set_child(GTK_WINDOW(window), box);



    /* label = gtk_label_new("text");
    gtk_window_set_child(GTK_WINDOW(window), label);  */               // text label       


    quit_btn = gtk_button_new_with_label("Quit");
    // gtk_window_set_child(GTK_WINDOW(window), quit_btn);
    g_signal_connect(quit_btn, "clicked", G_CALLBACK(quit_cb), window);


    click_btn = gtk_button_new_with_label("Click");    
    g_signal_connect(click_btn, "clicked", G_CALLBACK(click_cb), window);


    gtk_box_append(GTK_BOX(box), quit_btn);
    gtk_box_append(GTK_BOX(box), click_btn);



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
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);     // 对GtkApplication进行初始化,参数为标志符和flag(有特殊有求的时候传)
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);              // 连接到activate函数
    status = g_application_run(G_APPLICATION(app), argc, argv);                 // 启动activate函数
    g_object_unref(app);            // 释放GtkApplication对象

    return status;
}
