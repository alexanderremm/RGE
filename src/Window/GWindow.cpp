#define RGE_EXPORTS

#include "RGE/Window/GWindow.hpp"

namespace RGE
{
	// =========================================================================
	// Constructors/Destructors
	// =========================================================================
	EventQueue GWindow::m_eventQueue;

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

	// =========================================================================
	// Public
	// =========================================================================
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

		// Set OpenGL version (3.3)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

		// Register event callbacks
		glfwSetKeyCallback(m_window, KeyCallback);
		glfwSetMouseButtonCallback(m_window, MouseCallback);

		// Set the current OpenGL context and load OpenGL extensions
		glfwMakeContextCurrent(m_window);
		// Enable/Disable vsync
		if (!m_windowProps.vsync)
		{
			glfwSwapInterval(0);
		}

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
		#ifndef NDEBUG
			Logger::LOGC(RGE::LOG_DEBUG, "Failed to load the OpenGL extensions");
		#endif // NDEBUG
			// Failed to load OpenGL extensions
			return false;
		}

		// Display the OpenGL version
	#ifndef NDEBUG
		Logger::LOGC(RGE::LOG_DEBUG, "OpenGL: ", GLVersion.major, ".", GLVersion.minor);
	#endif // NDEBUG

		// Enable certain OpenGL capabilities
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	bool GWindow::ShouldClose() const
	{
		return glfwWindowShouldClose(m_window);
	}

	void GWindow::PollEvents(Event& event)
	{
		glfwPollEvents();

		// Grab event from window EventQueue
		Event* ev = m_eventQueue.GetNextEvent();
		if (ev)
		{
			event = *ev;
		}
	}

	void GWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	void* GWindow::GetNativeWindow() const
	{
		return m_window;
	}

	// =========================================================================
	// Private
	// =========================================================================
	void GWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Keypress
		if (action == GLFW_PRESS)
		{
			// Generate a keypress event
			Event* e = new Event;
			e->type = RGE::EventType::KeyPressed;
			e->key.keycode = key;
			e->key.repeated = false;

			m_eventQueue.AddEvent(e);
		}

		// Keypress (held)
		if (action == GLFW_REPEAT)
		{
			// Generate a keyheld event
			Event* e = new Event;
			e->type = RGE::EventType::KeyPressed;
			e->key.keycode = key;
			e->key.repeated = true;

			m_eventQueue.AddEvent(e);
		}

		// Keyrelease
		if (action == GLFW_RELEASE)
		{
			// Generate keyreleased event
			Event* e = new Event;
			e->type = RGE::EventType::KeyReleased;
			e->key.keycode = key;

			m_eventQueue.AddEvent(e);
		}
	}

	void GWindow::MouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		// Get current mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Mouse button pressed
		if (action == GLFW_PRESS)
		{
			// Generate mouse button pressed event
			Event* e = new Event;
			e->type = RGE::EventType::MouseButtonPressed;
			e->mouse.button = button;
			e->mouse.pos = RGE::Math::Vector2<double>(xpos, ypos);

			m_eventQueue.AddEvent(e);
		}

		// Mouse button released
		if (action == GLFW_RELEASE)
		{
			// Generate mouse button released event
			Event* e = new Event;
			e->type = RGE::EventType::MouseButtonReleased;
			e->mouse.button = button;
			e->mouse.pos = RGE::Math::Vector2<double>(xpos, ypos);

			m_eventQueue.AddEvent(e);
		}
	}

} // RGE