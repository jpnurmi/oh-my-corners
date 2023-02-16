#include "my_view.h"

struct _MyView {
  GtkWidget parent_instance;
};

G_DEFINE_TYPE(MyView, my_view, GTK_TYPE_WIDGET)

static void my_view_constructed(GObject* object) {}

static void my_view_dispose(GObject* object) {
  G_OBJECT_CLASS(my_view_parent_class)->dispose(object);
}

static void my_view_realize(GtkWidget* widget) {
  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);

  gtk_widget_set_realized(widget, TRUE);

  GdkWindowAttr attributes;
  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.x = allocation.x;
  attributes.y = allocation.y;
  attributes.width = allocation.width;
  attributes.height = allocation.height;
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.visual = gtk_widget_get_visual(widget);
  attributes.event_mask = gtk_widget_get_events(widget);
  gint attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL;
  GdkWindow* window = gdk_window_new(gtk_widget_get_parent_window(widget),
                                     &attributes, attributes_mask);
  gtk_widget_set_window(widget, window);
  gtk_widget_register_window(widget, window);

  g_autoptr(GError) error = NULL;
  GdkGLContext* main_context = gdk_window_create_gl_context(window, &error);
  if (error || !gdk_gl_context_realize(main_context, &error)) {
    g_critical("GL context: %s", error->message);
  }
}

static void my_view_class_init(MyViewClass* klass) {
  GObjectClass* object_class = G_OBJECT_CLASS(klass);
  object_class->constructed = my_view_constructed;
  object_class->dispose = my_view_dispose;

  GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);
  widget_class->realize = my_view_realize;
}

static gboolean tick_cb(GtkWidget* widget, GdkFrameClock* frame_clock,
                        gpointer user_data) {
  static gint i = 0;
  fprintf(stderr, "tick %d\n", ++i);
  gtk_widget_queue_draw(widget);
  return G_SOURCE_CONTINUE;
}

static void my_view_init(MyView* self) {
  gtk_widget_add_tick_callback(GTK_WIDGET(self), tick_cb, NULL, NULL);
}

GtkWidget* my_view_new() {
  return GTK_WIDGET(g_object_new(my_view_get_type(), NULL));
}
