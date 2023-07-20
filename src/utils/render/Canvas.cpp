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
#include "../math/Vector2.h"


namespace Gamink
{
	namespace Render
	{
		using namespace Math;

		class Canvas
		{
		private:
			cairo_surface_t *surface = NULL;
			GtkWidget *canvas;
			GtkWidget *drawingArea;
			GtkGesture *dragGesture;

			Vector2 *startPoint;
			Vector2 *lastPoint;

			int width;
			int height;


			static void RenderSurface(GtkDrawingArea *da, cairo_t *cr, int width, int height, gpointer data);
			static void CanvasResize(GtkWidget *drawingArea, int width, int height, gpointer data);

			static void DragBegin(GtkGestureDrag *gesture, double x, double y, gpointer data);
			static void DragUpdate(GtkGestureDrag *gesture, double x, double y, gpointer data);
			static void DragEnd(GtkGestureDrag *gesture, double x, double y, gpointer data);

			void CreateSurface();
			void DrawBrush(Vector2 *point);
			void DrawBrushLine(Vector2 *point1, Vector2 *point2);
			void UpdateSurface();

		public:
			Canvas(int width, int height);
			~Canvas();

			GtkWidget *GetCanvas();
			GtkWidget *GetDrawingArea();
		};
	}
}
