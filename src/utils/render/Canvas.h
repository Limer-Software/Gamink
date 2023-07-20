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


#include "Canvas.cpp"


namespace Gamink::Render
{
	#pragma region Constructor and Destructor
	Canvas::Canvas(int width, int height)
	{
		this->width = width;
		this->height = height;

		this->canvas = gtk_frame_new(NULL);

		this->drawingArea = (GtkWidget *)g_object_new(
			GTK_TYPE_DRAWING_AREA,
			"accessible-role",
			GTK_ACCESSIBLE_ROLE_IMG,
			NULL
		);

		gtk_frame_set_child(GTK_FRAME(this->canvas), this->drawingArea);


		gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(this->drawingArea), this->width);
		gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(this->drawingArea), this->height);
		gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(this->drawingArea), Canvas::RenderSurface, this, NULL);

		this->dragGesture = gtk_gesture_drag_new();
		gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(this->dragGesture), 0);
		gtk_widget_add_controller(this->drawingArea, GTK_EVENT_CONTROLLER(this->dragGesture));

		g_signal_connect(this->drawingArea, "resize", G_CALLBACK(Canvas::CanvasResize), this);

		g_signal_connect(this->dragGesture, "drag-begin", G_CALLBACK(Canvas::DragBegin), this);
		g_signal_connect(this->dragGesture, "drag-update", G_CALLBACK(Canvas::DragUpdate), this);
		g_signal_connect(this->dragGesture, "drag-end", G_CALLBACK(Canvas::DragEnd), this);
	}

	Canvas::~Canvas()
	{
		cairo_surface_destroy(this->surface);
	}
	#pragma endregion


	#pragma region Static Methods
	void Canvas::RenderSurface(GtkDrawingArea *da, cairo_t *cr, int width, int height, gpointer data)
	{
		Canvas *canvas = (Canvas *)data;

		cairo_set_source_surface(cr, canvas->surface, 0, 0);
		cairo_paint(cr);
	}

	void Canvas::CanvasResize(GtkWidget *drawingArea, int width, int height, gpointer data)
	{
		Canvas *canvas = (Canvas *)data;

		canvas->CreateSurface();
	}

	void Canvas::DragBegin(GtkGestureDrag *gesture, double x, double y, gpointer data)
	{
		Canvas *canvas = (Canvas *)data;

		canvas->startPoint = new Vector2(x, y);
		canvas->lastPoint = new Vector2(x, y);

		canvas->DrawBrush(canvas->startPoint);

		canvas->UpdateSurface();
	}

	void Canvas::DragUpdate(GtkGestureDrag *gesture, double x, double y, gpointer data)
	{
		Canvas *canvas = (Canvas *)data;

		Vector2 *point = new Vector2(x, y);

		if (canvas->lastPoint != point) {
			Vector2 *actualPoint = new Vector2(
				canvas->startPoint->x + point->x,
				canvas->startPoint->y + point->y
			);

			canvas->DrawBrushLine(
				canvas->lastPoint,
				actualPoint
			);

			canvas->lastPoint = actualPoint;

			canvas->UpdateSurface();
		}

		delete(point);
		point = NULL;
	}

	void Canvas::DragEnd(GtkGestureDrag *gesture, double x, double y, gpointer data)
	{
		Canvas::DragUpdate(gesture, x, y, data);
	}
	#pragma endregion


	#pragma region Methods
	void Canvas::CreateSurface()
	{
		if (this->surface) {
			cairo_surface_destroy(this->surface);
		}

		this->surface = cairo_image_surface_create(
			CAIRO_FORMAT_ARGB32,
			gtk_widget_get_width(this->drawingArea),
			gtk_widget_get_height(this->drawingArea)
		);

		cairo_t *cr = cairo_create(this->surface);
		cairo_set_source_rgb(cr, 1, 1, 1);
		cairo_paint(cr);

		cairo_destroy(cr);
	}

	GtkWidget *Canvas::GetCanvas()
	{
		return this->canvas;
	}

	GtkWidget *Canvas::GetDrawingArea()
	{
		return this->drawingArea;
	}

	void Canvas::UpdateSurface()
	{
		gtk_widget_queue_draw(this->drawingArea);
	}

	void Canvas::DrawBrush(Vector2 *point)
	{
		if (
			this->surface == NULL ||
			cairo_image_surface_get_width(this->surface) != gtk_widget_get_width(this->drawingArea) ||
			cairo_image_surface_get_height(this->surface) != gtk_widget_get_height(this->drawingArea)
		) {
			this->CreateSurface();
		}

		cairo_t *cr = cairo_create(this->surface);

		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_arc(cr, point->x, point->y, 5, 0, 2 * M_PI);
		cairo_fill(cr);

		cairo_destroy(cr);
	}

	void Canvas::DrawBrushLine(Vector2 *point1, Vector2 *point2)
	{
		double distance = sqrt(pow(point2->x - point1->x, 2) + pow(point2->y - point1->y, 2));

		for (double i = 0; i < distance; i++) {
			double x = point1->x + (point2->x - point1->x) * (i / distance);
			double y = point1->y + (point2->y - point1->y) * (i / distance);

			this->DrawBrush(new Vector2(x, y));
		}
	}
	#pragma endregion
}
