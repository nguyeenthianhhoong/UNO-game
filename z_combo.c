#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkListStore *liststore;
    GtkWidget *combo;
    GtkCellRenderer *column;

    gtk_init(&argc, &argv);

    liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
    gtk_list_store_insert_with_values(liststore, NULL, -1,
                                      0, "red",
                                      1, "Don't install.",
                                      -1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,
                                      0, "green",
                                      1, "This user only.",
                                      -1);
    gtk_list_store_insert_with_values(liststore, NULL, -1,
                                      0, "yellow",
                                      1, "All users.",
                                      -1);

    combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(liststore));

    /* liststore is now owned by combo, so the initial reference can
     * be dropped */
    g_object_unref(liststore);

    column = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), column, TRUE);

    /* column does not need to be g_object_unref()ed because it
     * is GInitiallyUnowned and the floating reference has been
     * passed to combo by the gtk_cell_layout_pack_start() call. */

    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), column,
                                   "cell-background", 0,
                                   "text", 1,
                                   NULL);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 1);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(window), combo);

    /* Also combo is GInitiallyUnowned and it is now owned
       by window after the gtk_container_add() call. */

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
//text-x-generic