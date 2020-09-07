#pragma once

#include "RGE/rge_exports.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace RGE
{
	class RGE_EXPORT Timer
	{
	public:
		Timer() {};
		virtual ~Timer() = default;

		double static GetTime(void);
		void static SetTime(double time);
	};

} // RGE