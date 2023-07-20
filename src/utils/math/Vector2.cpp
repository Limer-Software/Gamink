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


namespace Gamink
{
	namespace Math
	{
		struct Vector2
		{
		public:
			double x;
			double y;

			Vector2(double x, double y);
			~Vector2();


			double GetMagnitude();

			double Distance(Vector2 vector);
			double DistanceSquared(Vector2 vector);


			Vector2 operator+(Vector2 other);
			Vector2 operator-(Vector2 other);
			Vector2 operator*(Vector2 other);

			Vector2 operator*(double other);
			Vector2 operator/(double other);

			bool operator==(Vector2 other);
			bool operator!=(Vector2 other);

			Vector2 operator+=(Vector2 other);
			Vector2 operator-=(Vector2 other);
			Vector2 operator*=(Vector2 other);

			Vector2 operator*=(double other);
			Vector2 operator/=(double other);
		};
	}
}
