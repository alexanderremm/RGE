#include "RGE/GWindow.hpp"
#include "RGE/Logger.hpp"

int main()
{
	// Create a window context
	RGE::GWindow window = RGE::GWindow("Test Window", RGE::Math::v2i(800, 600));

	// Create a logger
	RGE::Logger logger("DEBUG.log");
	logger.LOG(RGE::LOG_INFO, "Started the Game window");

	float theta = 0.0f;

	// Main window loop
	while (!window.ShouldClose())
	{
		window.PollEvent();

		logger.LOG(RGE::LOG_DEBUG, "Rotation value: ", theta);

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