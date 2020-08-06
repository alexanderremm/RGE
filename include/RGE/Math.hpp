#ifndef MATH_HPP
#define MATH_HPP

#include <vector>
#include <iostream>

namespace RGE
{
	class Math
	{
	public:
		// 2d integer vector
		struct v2i
		{
			int x = 0;
			int y = 0;

			// Constructors
			v2i() {};
			v2i(int x1, int y1) { x = x1, y = y1; }

			// Operators
			friend std::ostream& operator<< (std::ostream& out, v2i const& v)
			{
				out << "<" << v.x << ", " << v.y << ">";
				return out;
			}
		};

		// 2d float vector
		struct v2f
		{
			float x = 0.0f;
			float y = 0.0f;

			// Constructors
			v2f() {};
			v2f(float x1, float y1) { x = x1, y = y1; }

			// Operators
			friend std::ostream& operator<< (std::ostream& out, v2f const& v)
			{
				out << "<" << v.x << ", " << v.y << ">";
				return out;
			}
		};
	};
} // RGE

#endif // MATH_HPP