#ifndef __TFE_TEXT_VIEW_H__
#define __TFE_TEXT_VIEW_H__

#include <gtk/gtk.h>

#define TFE_TYPE_TEXT_VIEW tfe_text_view_get_type ()
G_DECLARE_FINAL_TYPE (TfeTextView, tfe_text_view, TFE, TEXT_VIEW, GtkTextView)

/* "open-response" signal response */
enum TfeTextViewOpenResponseType {
  TFE_OPEN_RESPONSE_SUCCESS,
  TFE_OPEN_RESPONSE_CANCEL,
  TFE_OPEN_RESPONSE_ERROR
};


extern GFile *tfe_text_view_get_file (TfeTextView *tv);

extern void tfe_text_view_open (TfeTextView *tv, GtkWindow *win);

extern void tfe_text_view_save (TfeTextView *tv);

extern void tfe_text_view_saveas (TfeTextView *tv);

extern GtkWidget *tfe_text_view_new_with_file (GFile *file);

extern GtkWidget *tfe_text_view_new (void);

#endif /* __TFE_TEXT_VIEW_H__ */

