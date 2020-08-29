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

	// Main window loop
	while (!window.ShouldClose())
	{
		window.PollEvents();

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

		theta += 0.1f;
	}

	logger.LOG(RGE::LOG_INFO, "Closing the game window");

	return 0;
}
