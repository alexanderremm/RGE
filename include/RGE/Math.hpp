#ifndef MATH_HPP
#define MATH_HPP

#include <vector>

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

			v2i(int x, int y) { x = x, y = y; }
		};
		// 2d float vector
		struct v2f
		{
			float x = 0.0f;
			float y = 0.0f;

			v2f(float x, float y) { x = x, y = y; }
		};
	};
} // RGE

#endif // MATH_HPP