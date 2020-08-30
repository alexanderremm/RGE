#include <RGE.hpp>

int main(int argc, char** argv)
{
	// Create a logger
	RGE::Logger logger("DEBUG.log");
	logger.LOG(RGE::LOG_INFO, "Started the Game window");

	// Create a window context
	RGE::Math::Vector2 dims(800, 600);

	// Test some vector operations
	logger.LOGC(RGE::LOG_DEBUG, "Magnitude: ", dims.Magnitude());
	logger.LOGC(RGE::LOG_DEBUG, "Normal: ", dims.Normalize());

	RGE::GWindowProperties gwProps;
	gwProps.width = dims.x;
	gwProps.height = dims.y;
	gwProps.title = "EXAMPLE_01_Initialization";
	RGE::GWindow window(gwProps);

	// Initialize the window
	if (!window.Init())
	{
		logger.LOG(RGE::LOG_ERROR, "Unable to create the window!");
	}

	float theta = 0.0f;
	bool forward = true;
	float speed = 0.1f;

	// Main window loop
	while (!window.ShouldClose())
	{
		// Check for events
		RGE::Event e;
		window.PollEvents(e);

		switch (e.type)
		{
		case RGE::EventType::KeyPressed:
		{
			logger.LOG(RGE::LOG_INFO, "KeyPressed: ", e.key.keycode, " (repeated: ", e.key.repeated, ")");
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
			logger.LOG(RGE::LOG_INFO, "MouseButtonPressed: ", e.mouse.button, " (position: ", e.mouse.pos, ")");
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

		glPushMatrix();
		glRotatef(theta, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);
		glEnd();
		glPopMatrix();

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

	logger.LOG(RGE::LOG_INFO, "Closing the game window");

	return 0;
}
