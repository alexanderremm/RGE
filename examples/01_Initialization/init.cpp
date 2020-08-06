#include "RGE/GWindow.hpp"
#include "RGE/Logger.hpp"

int main()
{
	// Create a window context
	RGE::GWindow window = RGE::GWindow("Test Window", RGE::Math::v2i(800, 600));

	RGE::Logger::LOG(RGE::LOG_INFO, "Started the Game window");
	RGE::Logger::LOG(RGE::LOG_DEBUG, "Test!");
	RGE::Logger::LOG(RGE::LOG_WARN, "Failed to recognize input mechanism!");
	RGE::Logger::LOG(RGE::LOG_ERROR, "The game has crashed!");

	float theta = 0.0f;

	// Main window loop
	while (!window.ShouldClose())
	{
		window.PollEvent();

		RGE::Logger::LOG(RGE::LOG_DEBUG, "Rotation value: ", theta);

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

	return 0;
}