/*
	Gamink, a drawing program for videogames.
	Copyright (C) 2022 Edgar Lima <contact@robotoskunk.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <gtk-4.0/gtk/gtk.h>
#include "utils/render/Canvas.h"

#define IDENTIFIER "com.limer.gamink"
#define DEFAULT_WIDTH 1270
#define DEFAULT_HEIGHT 720


using namespace Gamink::Render;

void activate(GtkApplication *app, gpointer data) {
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Gamink");
	gtk_window_set_default_size(GTK_WINDOW(window), DEFAULT_WIDTH, DEFAULT_HEIGHT);


	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	gtk_window_set_child(GTK_WINDOW(window), box);


	gtk_box_append(GTK_BOX(box), gtk_label_new("First"));
	Canvas *canvas = new Canvas(DEFAULT_WIDTH, DEFAULT_HEIGHT / 2);
	gtk_box_append(GTK_BOX(box), canvas->GetCanvas());

	gtk_box_append(GTK_BOX(box), gtk_label_new("Second"));
	Canvas *canvas2 = new Canvas(DEFAULT_WIDTH, DEFAULT_HEIGHT / 2);
	gtk_box_append(GTK_BOX(box), canvas2->GetCanvas());

	gtk_widget_show(window);
}

int main(int argc, char **argv) {
	GtkApplication *app = gtk_application_new(IDENTIFIER, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	int status = g_application_run(G_APPLICATION(app), argc, argv);

	g_object_unref(app);

	return status;
}
