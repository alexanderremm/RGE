#include "RGE/Window/GWindow.hpp"

namespace RGE
{
	GWindow::GWindow(GWindowProperties windowProperties)
	{
		m_windowProps = windowProperties;
	}

	GWindow::GWindow(unsigned width, unsigned height, const char* title, bool resizeable)
	{
		m_windowProps.width = width;
		m_windowProps.height = height;
		m_windowProps.title = title;
		m_windowProps.resizeable = resizeable;
	}

	GWindow::~GWindow()
	{
		// Destroy window context
		if (m_window)
		{
			glfwDestroyWindow(m_window);
		}

		// Terminate GLFW
		glfwTerminate();
	}

	bool GWindow::Init()
	{
		// Initialize GLFW
		if (!glfwInit())
		{
		#ifdef _DEBUG
			Logger::LOGC(RGE::LOG_DEBUG, "Failed to initialize GLFW");
		#endif // _DEBUG
			// Initialization failed
			return false;
		}

		// Determine whether the window should be resizable or not
		if (m_windowProps.resizeable)
		{
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		}
		else
		{
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		// Create the window
		m_window = glfwCreateWindow(m_windowProps.width, m_windowProps.height, m_windowProps.title, NULL, NULL);

		if (!m_window)
		{
		#ifdef _DEBUG
			Logger::LOGC(RGE::LOG_DEBUG, "Failed to create the GLFW window");
		#endif // _DEBUG
			// Window or OpenGL context creation failed
			return false;
		}

		// Set the current OpenGL context and load OpenGL extensions
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGL())
		{
		#ifdef _DEBUG
			Logger::LOGC(RGE::LOG_DEBUG, "Failed to load the OpenGL extensions");
		#endif // _DEBUG
			// Failed to load OpenGL extensions
			return false;
		}

		// Display the OpenGL version
	#ifdef _DEBUG
		Logger::LOGC(RGE::LOG_DEBUG, "OpenGL: ", GLVersion.major, ".", GLVersion.minor);
	#endif // _DEBUG

		return true;
	}

	bool GWindow::ShouldClose() const
	{
		return glfwWindowShouldClose(m_window);
	}

	void GWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void GWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

} // RGE