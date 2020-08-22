#include <RGE.hpp>

int main(int argc, char** argv)
{
	// Create a window context
	RGE::GWindow window = RGE::GWindow("Test Window", RGE::Math::v2i(800, 600));

	// Create a logger
	RGE::Logger logger("DEBUG.log");
	logger.LOG(RGE::LOG_INFO, "Started the Game window");

	float theta = 0.0f;

	// Main window loop
	bool done = false;
	while (!done)
	{
		// Event handling
		RGE::Event e;
		window.PollEvent(e);

		switch (e.type)
		{
		case RGE::EventType::WindowClose:
		{
			done = true;
			break;
		}

		case RGE::EventType::KeyPressed:
		{
			logger.LOG(RGE::LOG_INFO, "Key was pressed: ", e.key.keycode, " (repeated: ", e.key.repeated, ")");
			break;
		}
		case RGE::EventType::KeyReleased:
		{
			logger.LOG(RGE::LOG_INFO, "Key was released: ", e.key.keycode);
			break;
		}
		case RGE::EventType::MouseButtonPressed:
		{
			logger.LOG(RGE::LOG_INFO, "Mouse button was pressed: ", e.mouse.button, " (position: ", e.mouse.pos, ")");
			break;
		}
		case RGE::EventType::MouseButtonReleased:
		{
			logger.LOG(RGE::LOG_INFO, "Mouse button was released: ", e.mouse.button, " (position: ", e.mouse.pos, ")");
			break;
		}
		default:
			break;
		}

		//logger.LOG(RGE::LOG_DEBUG, "Rotation value: ", theta);

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
		window.FlipDisplay();

		theta += 0.1f;
	}

	logger.LOG(RGE::LOG_INFO, "Closing the game window");

	return 0;
}