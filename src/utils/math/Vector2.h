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


#include <math.h>
#include "Vector2.cpp"

namespace Gamink
{
	namespace Math
	{
		Vector2::Vector2(double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2::~Vector2() { }

		double Vector2::GetMagnitude()
		{
			return sqrt(pow(this->x, 2) + pow(this->y, 2));
		}

		double Vector2::Distance(Vector2 vector)
		{
			return sqrt(pow(vector.x - this->x, 2) + pow(vector.y - this->y, 2));
		}

		double Vector2::DistanceSquared(Vector2 vector)
		{
			return pow(vector.x - this->x, 2) + pow(vector.y - this->y, 2);
		}


		Vector2 Vector2::operator+(Vector2 other)
		{
			return Vector2(this->x + other.x, this->y + other.y);
		}

		Vector2 Vector2::operator-(Vector2 other)
		{
			return Vector2(this->x - other.x, this->y - other.y);
		}

		Vector2 Vector2::operator*(Vector2 other)
		{
			return Vector2(this->x * other.x, this->y * other.y);
		}


		Vector2 Vector2::operator*(double other)
		{
			return Vector2(this->x * other, this->y * other);
		}

		Vector2 Vector2::operator/(double other)
		{
			return Vector2(this->x / other, this->y / other);
		}


		bool Vector2::operator==(Vector2 other)
		{
			double magnitude = this->GetMagnitude();
			double otherMagnitude = other.GetMagnitude();

			return (magnitude == otherMagnitude);
		}

		bool Vector2::operator!=(Vector2 other)
		{
			return !(*this == other);
		}

		Vector2 Vector2::operator+=(Vector2 other)
		{
			this->x += other.x;
			this->y += other.y;

			return *this;
		}

		Vector2 Vector2::operator-=(Vector2 other)
		{
			this->x -= other.x;
			this->y -= other.y;

			return *this;
		}

		Vector2 Vector2::operator*=(Vector2 other)
		{
			this->x *= other.x;
			this->y *= other.y;

			return *this;
		}

		Vector2 Vector2::operator*=(double other)
		{
			this->x *= other;
			this->y *= other;

			return *this;
		}

		Vector2 Vector2::operator/=(double other)
		{
			this->x /= other;
			this->y /= other;

			return *this;
		}
	}
}
