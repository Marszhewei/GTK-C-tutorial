#include <gtk/gtk.h>


#define TFE_TYPE_TEXT_VIEW tfe_text_view_get_type()
G_DECLARE_FINAL_TYPE(TfeTextView, tfe_text_view, TFE, TEXT_VIEW, GtkTextView)


struct _TfeTextView {
  GtkTextView parent;
  GFile *file;
};


G_DEFINE_TYPE(TfeTextView, tfe_text_view, GTK_TYPE_TEXT_VIEW);


static void tfe_text_view_init(TfeTextView *tv)
{
}


static void tfe_text_view_class_init(TfeTextViewClass *class)
{
}


void tfe_text_view_set_file(TfeTextView *tv, GFile *f)
{
    tv->file = f;
}


GFile *tfe_text_view_get_file(TfeTextView *tv)
{
    return tv->file;
}


GtkWidget *tfe_text_view_new(void)
{
    return GTK_WIDGET(g_object_new(TFE_TYPE_TEXT_VIEW, NULL));
}


/* ---------- end of the definition of TfeTextView ---------- */
static gboolean before_close(GtkWindow *win, gpointer user_data)
{
    GtkWidget *nb = GTK_WIDGET(user_data);
    GtkWidget *scr;
    GtkWidget *tv;
    GFile *file;
    char *pathname;
    GtkTextBuffer *tb;
    GtkTextIter start_iter;
    GtkTextIter end_iter;
    char *contents;
    unsigned int n;
    unsigned int i;

    n = gtk_notebook_get_n_pages(GTK_NOTEBOOK(nb));
    for (i = 0; i < n; ++i) {
        scr = gtk_notebook_get_nth_page(GTK_NOTEBOOK(nb), i);
        tv = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scr));
        file = tfe_text_view_get_file(TFE_TEXT_VIEW(tv));
        tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
        gtk_text_buffer_get_bounds(tb, &start_iter, &end_iter);
        contents = gtk_text_buffer_get_text(tb, &start_iter, &end_iter, FALSE);

        if (!g_file_replace_contents(file, contents, strlen(contents), NULL,TRUE,
                                     G_FILE_CREATE_NONE, NULL, NULL, NULL)) {
            pathname = g_file_get_path(file);
            g_print("ERROR : Can't save %s.", pathname);
            g_free(pathname);
        }
        g_free(contents);
    }
    return FALSE;
}


static void app_activate(GApplication *app, gpointer user_data)
{ // 命令行调用时没有传入文件会调用这个函数
  g_print("You need to give filenames as arguments.\n");
}


// static void
// app_open (GApplication *app, GFile ** files, gint n_files, gchar *hint, gpointer user_data) {
//   GtkWidget *win;
//   GtkWidget *nb;
//   GtkWidget *lab;
//   GtkNotebookPage *nbp;
//   GtkWidget *scr;
//   GtkWidget *tv;
//   GtkTextBuffer *tb;
//   char *contents;
//   gsize length;
//   char *filename;
//   int i;

//   GtkWidget *boxv;
//   GtkWidget *boxh;
//   GtkWidget *dmy1;
//   GtkWidget *dmy2;
//   GtkWidget *dmy3;
//   GtkWidget *btnn; /* button for new */
//   GtkWidget *btno; /* button for open */
//   GtkWidget *btns; /* button for save */
//   GtkWidget *btnc; /* button for close */

//   win = gtk_application_window_new (GTK_APPLICATION (app));
//   gtk_window_set_title (GTK_WINDOW (win), "file editor");
//   gtk_window_set_default_size (GTK_WINDOW (win), 600, 400);

//   boxv = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
//   gtk_window_set_child (GTK_WINDOW (win), boxv);

//   boxh = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
//   gtk_box_append (GTK_BOX (boxv), boxh);

//   dmy1 = gtk_label_new(NULL); /* dummy label for left space */
//   gtk_label_set_width_chars (GTK_LABEL (dmy1), 10);
//   dmy2 = gtk_label_new(NULL); /* dummy label for center space */
//   gtk_widget_set_hexpand (dmy2, TRUE);
//   dmy3 = gtk_label_new(NULL); /* dummy label for right space */
//   gtk_label_set_width_chars (GTK_LABEL (dmy3), 10);
//   btnn = gtk_button_new_with_label ("New");
//   btno = gtk_button_new_with_label ("Open");
//   btns = gtk_button_new_with_label ("Save");
//   btnc = gtk_button_new_with_label ("Close");

//   gtk_box_append (GTK_BOX (boxh), dmy1);
//   gtk_box_append (GTK_BOX (boxh), btnn);
//   gtk_box_append (GTK_BOX (boxh), btno);
//   gtk_box_append (GTK_BOX (boxh), dmy2);
//   gtk_box_append (GTK_BOX (boxh), btns);
//   gtk_box_append (GTK_BOX (boxh), btnc);
//   gtk_box_append (GTK_BOX (boxh), dmy3);

//   nb = gtk_notebook_new ();
//   gtk_widget_set_hexpand (nb, TRUE);
//   gtk_widget_set_vexpand (nb, TRUE);
//   gtk_box_append (GTK_BOX (boxv), nb);

//   for (i = 0; i < n_files; i++) {
//     if (g_file_load_contents (files[i], NULL, &contents, &length, NULL, NULL)) {
//       scr = gtk_scrolled_window_new ();
//       tv = tfe_text_view_new ();
//       tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
//       gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (tv), GTK_WRAP_WORD_CHAR);
//       gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scr), tv);

//       tfe_text_view_set_file (TFE_TEXT_VIEW (tv),  g_file_dup (files[i]));
//       gtk_text_buffer_set_text (tb, contents, length);
//       g_free (contents);
//       filename = g_file_get_basename (files[i]);
//       lab = gtk_label_new (filename);
//       gtk_notebook_append_page (GTK_NOTEBOOK (nb), scr, lab);
//       nbp = gtk_notebook_get_page (GTK_NOTEBOOK (nb), scr);
//       g_object_set (nbp, "tab-expand", TRUE, NULL);
//       g_free (filename);
//     } else if ((filename = g_file_get_path (files[i])) != NULL) {
//         g_print ("No such file: %s.\n", filename);
//         g_free (filename);
//     } else
//         g_print ("No valid file is given\n");
//   }
//   if (gtk_notebook_get_n_pages (GTK_NOTEBOOK (nb)) > 0) {
//     gtk_widget_show (win);
//   } else
//     gtk_window_destroy (GTK_WINDOW (win));
// }


static void app_open(GApplication *app, GFile **files, 
                     gint n_files, gchar *hint, gpointer user_data)
{
    GtkWidget *win;       // window
    GtkWidget *nb;        // note book
    GtkWidget *lab;       // label text
    GtkNotebookPage *nbp; // note book page
    GtkWidget *scr;       // scroll
    GtkWidget *tv;        // text view
    GtkTextBuffer *tb;    // text buffer
    char *contents;       // text string
    gsize length;         // text string length
    char *filename;       // text file name
    GtkBuilder *build;    // for build ui

    // 实现一些功能键
    build = gtk_builder_new_from_file("button.xml");
    win = GTK_WIDGET(gtk_builder_get_object(build, "win"));
    gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));
    nb = GTK_WIDGET(gtk_builder_get_object(build, "nb")); // ui是渲染在note book上
    g_object_unref(build);                                // 销毁build

    for (int i = 0; i < n_files; i++) {
        if (g_file_load_contents(files[i], NULL, &contents, &length, NULL, NULL)) {
            scr = gtk_scrolled_window_new();
            tv = tfe_text_view_new(); // text view是使用我们自己实现的子对象(gtk_text_view)
            tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv); // 滚动栏

            tfe_text_view_set_file(TFE_TEXT_VIEW(tv), g_file_dup(files[i]));
            gtk_text_buffer_set_text(tb, contents, length); // 把文本载入到text buffer中
            g_free(contents);
            filename = g_file_get_basename(files[i]);             // get filename
            lab = gtk_label_new(filename);                        // 创建一个label,名为filename
            gtk_notebook_append_page(GTK_NOTEBOOK(nb), scr, lab); // 把 scroll 和 label 加载到 note book 上
            nbp = gtk_notebook_get_page(GTK_NOTEBOOK(nb), scr);
            g_object_set(nbp, "tab-expand", TRUE, NULL); // 把 note book 组织到 note book page 上
            g_free(filename);
        }
        else if ((filename = g_file_get_path(files[i])) != NULL) {
            g_print("No such file: %s.\n", filename);
            g_free(filename);
        }
        else
            g_print("No valid file is given\n");
    }
    if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(nb)) > 0)
        gtk_widget_show(win);
    else
        gtk_window_destroy(GTK_WINDOW(win));
}


int main(int argc, char **argv)
{
    GtkApplication *app;
    int stat;

    app = gtk_application_new("mars.demo", G_APPLICATION_HANDLES_OPEN);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    g_signal_connect(app, "open", G_CALLBACK(app_open), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return stat;
}