#define RGE_EXPORTS

#include "RGE/Core/Timer.hpp"

namespace RGE
{
	double Timer::GetTime(void)
	{
		return glfwGetTime();
	}

	void Timer::SetTime(double time)
	{
		glfwSetTime(time);
	}

} // RGE