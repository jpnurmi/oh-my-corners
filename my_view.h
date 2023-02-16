#ifndef MY_VIEW_H
#define MY_VIEW_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE(MyView, my_view, MY, VIEW, GtkWidget)

GtkWidget* my_view_new();

G_END_DECLS

#endif  // MY_VIEW_H
