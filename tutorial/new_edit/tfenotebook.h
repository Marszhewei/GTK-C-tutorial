#ifndef _TFE_NOTE_BOOK_H_
#define _TFE_NOTE_BOOK_H_

extern  void notebook_page_save(GtkNotebook *nb);

extern void notebook_page_close (GtkNotebook *nb);

extern void notebook_page_open (GtkNotebook *nb);

extern void notebook_page_new_with_file (GtkNotebook *nb, GFile *file);

extern void notebook_page_new (GtkNotebook *nb);

#endif