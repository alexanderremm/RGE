#include "RGE/GWindow.hpp"

int main()
{
	// Create a window context
	RGE::GWindow window = RGE::GWindow("Test Window", RGE::Math::v2i(800, 600));

	// Main window loop
	while (!window.ShouldClose())
	{
		window.PollEvent();
	}

	return 0;
}