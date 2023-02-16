#include <gtk/gtk.h>

#include "my_view.h"

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget* window = gtk_application_window_new(app);

  GtkWidget* header_bar = gtk_header_bar_new();
  // gtk_widget_show(GTK_WIDGET(header_bar));
  gtk_window_set_titlebar(GTK_WINDOW(window), GTK_WIDGET(header_bar));

  gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
  gtk_widget_show(window);

  GtkWidget* view = my_view_new();
  gtk_widget_show(view);
  gtk_container_add(GTK_CONTAINER(window), view);
}

int main(int argc, char** argv) {
  g_autoptr(GtkApplication) app =
      gtk_application_new("oh.my.corners", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  return g_application_run(G_APPLICATION(app), argc, argv);
}
