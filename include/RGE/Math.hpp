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

			v2i(int x1, int y1) { x = x1, y = y1; }
		};
		// 2d float vector
		struct v2f
		{
			float x = 0.0f;
			float y = 0.0f;

			v2f(float x1, float y1) { x = x1, y = y1; }
		};
	};
} // RGE

#endif // MATH_HPP