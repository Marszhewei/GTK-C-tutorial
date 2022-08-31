#ifndef _TFE_TEXT_VIEW_H_
#define _TFE_TEXT_VIEW_H_

#include <gtk/gtk.h>
#include <stdio.h>

#define TFE_TYPE_TEXT_VIEW tfe_text_view_get_type()
G_DECLARE_FINAL_TYPE(TfeTextView, tfe_text_view, TFE, TEXT_VIEW, GtkTextView)

extern void tfe_text_view_set_file(TfeTextView *tv, GFile *f);

extern GFile *tfe_text_view_get_file(TfeTextView *tv);

extern GtkWidget *tfe_text_view_new(void);

#endif
