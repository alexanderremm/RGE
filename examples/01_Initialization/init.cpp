#include "RGE/Window.hpp"

int main()
{
	// Create a window context
	RGE::Window window = RGE::Window("Test Window", RGE::Math::v2i(800, 600));

	// Main window loop
	while (!window.ShouldClose())
	{
		window.PollEvent();
	}

	return 0;
}