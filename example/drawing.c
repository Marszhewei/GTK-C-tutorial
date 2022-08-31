#include <gtk/gtk.h>

/* 存储当前涂鸦的表面 */
static cairo_surface_t* surface = NULL;

static void clear_surface(void) {
    cairo_t* cr;

    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

/* 创建一个合适大小的新表面来存储我们的涂鸦 */
static void resize_cb(GtkWidget* widget, int width, 
                        int height, gpointer data) {
    if (surface) {
        cairo_surface_destroy(surface);
        surface = NULL;
    }

    if (gtk_native_get_surface(gtk_widget_get_native(widget))) {
        surface = gdk_surface_create_similar_surface(gtk_native_get_surface(gtk_widget_get_native(widget)),
            CAIRO_CONTENT_COLOR,
            gtk_widget_get_width(widget),
            gtk_widget_get_height(widget));

        /* 将表面初始化为白色 */
        clear_surface();
    }
}

/* 从表面重绘屏幕。请注意，draw * 回调接收一个准备好使用的 cairo_t，该 cairo_t 已经 * 剪裁为仅绘制小部件的暴露区域 */
static void draw_cb(GtkDrawingArea* drawing_area, cairo_t* cr, 
                        int width, int height, gpointer data) {
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);
}

/* 在表面上给定位置绘制一个矩形 */
static void draw_brush(GtkWidget* widget, double x, double y) {
    cairo_t* cr;

    /* 绘制到表面，我们存储我们的状态 */
    cr = cairo_create(surface);

    cairo_rectangle(cr, x - 3, y - 3, 6, 6);
    cairo_fill(cr);

    cairo_destroy(cr);

    /* 现在使绘图区域无效。*/
    gtk_widget_queue_draw(widget);
}

static double start_x;
static double start_y;

static void drag_begin(GtkGestureDrag* gesture, double x, double y, GtkWidget* area) {
    start_x = x;
    start_y = y;

    draw_brush(area, x, y);
}

static void drag_update(GtkGestureDrag* gesture, double x, double y, GtkWidget* area) {
    draw_brush(area, start_x + x, start_y + y);
}

static void drag_end(GtkGestureDrag* gesture, double x, 
                            double y, GtkWidget* area) {
    draw_brush(area, start_x + x, start_y + y);
}

static void pressed(GtkGestureClick* gesture, int _press, 
                        double x, double y, GtkWidget* area) {
    clear_surface();
    gtk_widget_queue_draw(area);
}

static void close_window(void) {
    if (surface) {
        cairo_surface_destroy(surface);
    }
}


static void print_button_delete(GtkWidget *widget, gpointer data)
{
    g_print("Delete\n");
}

static void print_button_add(GtkWidget *widget, gpointer data)
{
    g_print("Add\n");
}


static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window;
    GtkWidget* frame;           /* 帧 */
    GtkWidget* drawing_area;    // 绘画区域
    GtkGesture* drag;           // 拖动?   
    GtkGesture* press;          // 按压?
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Drawing");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 400);

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

    // g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

    frame = gtk_frame_new(NULL);
    gtk_window_set_child(GTK_WINDOW(window), frame);

    drawing_area = gtk_drawing_area_new();
    /* 设置最小尺寸 */
    gtk_widget_set_size_request(drawing_area, 600, 400);

    gtk_frame_set_child(GTK_FRAME(frame), drawing_area);

    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_cb, NULL, NULL);

    g_signal_connect_after(drawing_area, "resize", G_CALLBACK(resize_cb), NULL);

    drag = gtk_gesture_drag_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(drag), GDK_BUTTON_PRIMARY);
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(drag));
    g_signal_connect(drag, "drag-begin", G_CALLBACK(drag_begin), drawing_area);
    g_signal_connect(drag, "drag-update", G_CALLBACK(drag_update), drawing_area);
    g_signal_connect(drag, "drag-end", G_CALLBACK(drag_end), drawing_area);

    press = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(press), GDK_BUTTON_SECONDARY);
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(press));

    g_signal_connect(press, "pressed", G_CALLBACK(pressed), drawing_area);

    gtk_widget_show(window);
}


int main(int argc, char** argv) {
    GtkApplication* app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}