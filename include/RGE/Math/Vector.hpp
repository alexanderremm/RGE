#pragma once

#include <cmath>
#include <iostream>

namespace RGE
{
	namespace Math
	{
		template <typename T>
		struct Vector2
		{
			T x;
			T y;

			Vector2(T xVal, T yVal)
			{
				x = xVal;
				y = yVal;
			}

			double Magnitude() const
			{
				return sqrt(pow(x, 2) + pow(y, 2));
			}

			Vector2<double> Normalize() const
			{
				double magnitude = this->Magnitude();
				double nX = x / magnitude;
				double nY = y / magnitude;

				return Vector2<double>(nX, nY);
			}

			// Operator overloading
			friend std::ostream& operator<<(std::ostream& os, const Vector2& v2)
			{
				os << "<" << v2.x << ", " << v2.y << ">";
				return os;
			}
		};

	} // Math

} // RGE
