#include <RGE/RGE.hpp>
#include <glad/glad.h>

#include <sstream>

#include "Render/Fonts/Cousine.ttf.hpp"

int main(int argc, char** argv)
{
	// Initialize logging
	RGE::Logging::Init();
	RGE_INFO("Started the Game window");

	// Create a window context
	RGE::Math::Vector2 dims(800, 600);

	// Test some vector operations
	//RGE_TRACE("Magnitude: {}", dims.Magnitude());
	//RGE_TRACE("Normal: {}", dims.Normalize());

	RGE::GWindowProperties gwProps;
	gwProps.width = dims.x;
	gwProps.height = dims.y;
	gwProps.title = "RGEDriver";
	RGE::GWindow window(gwProps);

	// Initialize the window
	if (!window.Init())
	{
		RGE_ERROR("Unable to create the window!");
	}

	RGE::Render::TextRenderer tr(800, 600);
	tr.LoadFromMemory(Cousine_Regular_ttf, Cousine_Regular_ttf_len, 12);

	// Initialize OpenGL extensions
	if (!gladLoadGL())
	{
		RGE_WARN("Unable to load OpenGL extensions!");
	}

	float theta = 0.0f;
	bool forward = true;
	float speed = 0.1f;

	double pt = RGE::Timer::GetTime();
	int nbFrames = 0;
	double frameTime = 0;
	double FPS = 0;

	// Main window loop
	while (!window.ShouldClose())
	{
		// FPS Counter
		double ct = RGE::Timer::GetTime();
		nbFrames++;
		if (ct - pt >= 1.0f)
		{
			frameTime = (1000 / double(nbFrames));
			FPS = 1000 / frameTime;
			nbFrames = 0;
			pt += 1.0f;
		}

		// Check for events
		RGE::Event e;
		window.PollEvents(e);

		switch (e.type)
		{
		case RGE::EventType::KeyPressed:
		{
			RGE_TRACE("KeyPressed: {} (repeated: {})", e.key.keycode, e.key.repeated);
			if (e.key.keycode == RGE_KEY_LEFT)
			{
				forward = false;
			}

			else if (e.key.keycode == RGE_KEY_RIGHT)
			{
				forward = true;
			}

			else if (e.key.keycode == RGE_KEY_UP)
			{
				speed += 0.1f;
			}

			else if (e.key.keycode == RGE_KEY_DOWN)
			{
				speed -= 0.1f;
			}
			break;
		}

		case RGE::EventType::MouseButtonPressed:
		{
			RGE_TRACE("MouseButtonPressed: {} (position: {})", e.mouse.button, e.mouse.pos);
			if (e.mouse.button == RGE_MOUSE_BUTTON_1) // Left mouse button
			{
				forward = false;
			}

			else if (e.mouse.button == RGE_MOUSE_BUTTON_2) // Right mouse button
			{
				forward = true;
			}

			break;
		}

		default:
			break;
		}

		// Cap the speed at 0.1f
		if (speed <= 0.1f)
		{
			speed = 0.1f;
		}

		// OpenGL drawing
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		std::stringstream frameTimeString;
		std::stringstream fpsString;
		frameTimeString << "Frametime: " << frameTime << " ms/frame";
		fpsString << "FPS: " << FPS;

		tr.RenderText(frameTimeString.str(), 2, 10, 1);
		tr.RenderText(fpsString.str(), 2, 22, 1);

		// Update the display
		window.SwapBuffers();

		if (forward)
		{
			theta -= speed;
		}
		else
		{
			theta += speed;
		}
	}

	RGE_INFO("Closing the game window");

	return 0;
}
