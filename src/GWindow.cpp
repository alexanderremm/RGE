#include "RGE/GWindow.hpp"

namespace RGE
{
	GWindow::GWindow(const char* windowName, const Math::v2i& dims)
	{
		m_name = windowName;
		m_width = dims.x;
		m_height = dims.y;

		bool ready = Init();
		if (!ready)
		{
			RGE::Logger::LOGC(RGE::LOG_ERROR, "Failed to initialize the window!");
		}
	}

	GWindow::~GWindow()
	{
	#ifdef _WIN32
		ReleaseDC(m_handle, m_deviceContext);
		wglDeleteContext(m_glRenderingContext); // Delete the OpenGL rendering context
		PostQuitMessage(0);

		m_handle = nullptr;
	#endif // _WIN32

	#ifdef __linux__
		glXMakeCurrent(m_display, None, NULL);
		glXDestroyContext(m_display, m_glRenderingContext);

		m_display = nullptr;
		m_vi = nullptr;
	#endif // __linux__
	}

	// ---- Windows Specific Methods ---- //
	#ifdef _WIN32
	LRESULT CALLBACK GWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		GWindow* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
				PFD_TYPE_RGBA,												// The kind of framebuffer, RGBA or palette
				24,															// Colordepth of the framebuffer
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				32,															// Number of bits for the depth buffer
				0,															// Number of bits for the stencil buffer
				0,															// Number of Aux buffers in the framebuffer
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (GWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
			
			// Set window properties
			pThis->m_handle = hwnd;

			// OpenGL context creation
			pThis->m_deviceContext = GetDC(hwnd);
			int wcpf; // Windows chosen pixel format
			wcpf = ChoosePixelFormat(pThis->m_deviceContext, &pfd);
			SetPixelFormat(pThis->m_deviceContext, wcpf, &pfd);

			pThis->m_glRenderingContext = wglCreateContext(pThis->m_deviceContext);
			wglMakeCurrent(pThis->m_deviceContext, pThis->m_glRenderingContext);

			glViewport(0, 0, pThis->m_width, pThis->m_height);
		}
		else
		{
			pThis = (GWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	LRESULT GWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
		{
			// Generate an event and push it to the event queue
			Event* e = new Event;
			e->type = EventType::WindowClose;

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_KEYDOWN:
		{
			// Generate an event and push it to the event queue
			Event* e = new Event;
			e->type = EventType::KeyPressed;
			e->key.keycode = wParam;
			e->key.repeated = (lParam >> 30) & 1;

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_KEYUP:
		{
			// Generate an event and push it to the event queue
			Event* e = new Event;
			e->type = EventType::KeyReleased;
			e->key.keycode = wParam;
			e->key.repeated = (lParam >> 30) & 1;

			m_eventQueue.AddEvent(e);
			return 0;
		}

		// MouseButtonDown events
		case WM_LBUTTONDOWN:
		{
			Event* e = new Event;
			e->type = EventType::MouseButtonPressed;
			e->mouse.button = 1;
			e->mouse.pos = RGE::Math::v2i(LOWORD(lParam), HIWORD(lParam));

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_MBUTTONDOWN:
		{
			Event* e = new Event;
			e->type = EventType::MouseButtonPressed;
			e->mouse.button = 2;
			e->mouse.pos = RGE::Math::v2i(LOWORD(lParam), HIWORD(lParam));

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_RBUTTONDOWN:
		{
			Event* e = new Event;
			e->type = EventType::MouseButtonPressed;
			e->mouse.button = 3;
			e->mouse.pos = RGE::Math::v2i(LOWORD(lParam), HIWORD(lParam));

			m_eventQueue.AddEvent(e);
			return 0;
		}

		// MouseButtonUp events
		case WM_LBUTTONUP:
		{
			Event* e = new Event;
			e->type = EventType::MouseButtonReleased;
			e->mouse.button = 1;
			e->mouse.pos = RGE::Math::v2i(LOWORD(lParam), HIWORD(lParam));

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_MBUTTONUP:
		{
			Event* e = new Event;
			e->type = EventType::MouseButtonReleased;
			e->mouse.button = 2;
			e->mouse.pos = RGE::Math::v2i(LOWORD(lParam), HIWORD(lParam));

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_RBUTTONUP:
		{
			Event* e = new Event;
			e->type = EventType::MouseButtonReleased;
			e->mouse.button = 3;
			e->mouse.pos = RGE::Math::v2i(LOWORD(lParam), HIWORD(lParam));

			m_eventQueue.AddEvent(e);
			return 0;
		}

		case WM_PAINT:
		{
			return 0;
		}

		default:
			return DefWindowProc(m_handle, uMsg, wParam, lParam);
		}
		return TRUE;
	}
	#endif // _WIN32

	bool GWindow::Init()
	{
	#ifdef _WIN32
		// Register the window class
		m_wc.lpfnWndProc = GWindow::WindowProc;
		m_wc.hInstance = GetModuleHandle(0);
		m_wc.lpszClassName = m_name;

		RegisterClass(&m_wc);

		// Create the window
		m_handle = CreateWindowEx(
			CS_OWNDC,													// Optional window styles
			m_name,														// Window class
			m_name,														// Window text
			(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),	// Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,

			NULL,					 // Parent window    
			NULL,					 // Menu
			GetModuleHandle(0),		 // Instance handle
			this					 // Additional application data
		);

		if (m_handle == NULL)
		{
			return false;
		}

		ShowWindow(m_handle, SW_SHOWDEFAULT);

		return true;
	#endif // _WIN32

	#ifdef __linux__
		m_display = XOpenDisplay(NULL);
		
		if (m_display == NULL)
		{
			// Failed to initialize the display
			return false;
		}

		m_screen = DefaultScreen(m_display);

		GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		m_vi = glXChooseVisual(m_display, 0, att);

		if (m_vi == NULL)
		{
			// Log: no appropriate visual found
			return false;
		}

		m_cmap = XCreateColormap(m_display, DefaultRootWindow(m_display), m_vi->visual, AllocNone);

		m_swa.colormap = m_cmap;
		m_swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask;

		m_window = XCreateWindow(m_display, DefaultRootWindow(m_display), 
			0, 0, 
			m_width, m_height, 0, 
			m_vi->depth, InputOutput, m_vi->visual, 
			CWColormap | CWEventMask, &m_swa);

		// Set the name of the window
		XStoreName(m_display, m_window, m_name);

		// Set the recommended window size (Note: some windowing managers will ignore this)
		XSizeHints sh;
		sh.min_width = m_width; sh.min_height = m_height;
		sh.max_width = m_width; sh.max_height = m_height;
		XSetWMNormalHints(m_display, m_window, &sh);
		
		// Register interest in the delete window message
		m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(m_display, m_window, &m_wmDeleteMessage, 1);
		
		XMapWindow(m_display, m_window);

		// Create OpenGL context
		m_glRenderingContext = glXCreateContext(m_display, m_vi, NULL, GL_TRUE);
		glXMakeCurrent(m_display, m_window, m_glRenderingContext);
		glViewport(0, 0, m_width, m_height);

		return true;
	#endif // __linux__
	}

	// Poll for any window events
	void GWindow::PollEvent(Event& event)
	{
	#ifdef _WIN32
		if (GetMessage(&m_msg, NULL, 0, 0))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
	#endif // _WIN32

	#ifdef __linux__
		XEvent e;
		while(XPending(m_display))
		XNextEvent(m_display, &e);

		// Window close event
		if (e.type == ClientMessage && e.xclient.data.l[0] == m_wmDeleteMessage) 
		{
			Event* event = new Event;
			event->type = EventType::WindowClose;

			m_eventQueue.AddEvent(event);
		}

		// KeyPressed/KeyReleased events
		if (e.type == KeyPress)
		{
			Event* event = new Event;
			event->type = EventType::KeyPressed;
			event->key.keycode = e.xkey.keycode;
			// TODO: Find a way to handle held keys
			// Set to 0 on linux for now
			event->key.repeated = 0;

			m_eventQueue.AddEvent(event);
		}

		if (e.type == KeyRelease)
		{
			Event* event = new Event;
			event->type = EventType::KeyReleased;
			event->key.keycode = e.xkey.keycode;

			m_eventQueue.AddEvent(event);
		}

		// MouseButtonPressed/MouseButtonReleased events
		if (e.type == ButtonPress)
		{
			Event* event = new Event;
			event->type = EventType::MouseButtonPressed;
			event->mouse.button = e.xbutton.button;
			event->mouse.pos = RGE::Math::v2i(e.xbutton.x, e.xbutton.y);

			m_eventQueue.AddEvent(event);
		}

		if (e.type == ButtonRelease)
		{
			Event* event = new Event;
			event->type = EventType::MouseButtonReleased;
			event->mouse.button = e.xbutton.button;
			event->mouse.pos = RGE::Math::v2i(e.xbutton.x, e.xbutton.y);

			m_eventQueue.AddEvent(event);
		}
	#endif // __linux__

		// Grab event messages and cast to the correct type
		Event* ev = m_eventQueue.GetNextEvent();
		if (ev) // Will be a nullptr if there are no events on the queue
		{
			event = *ev;
		}
	}

	void GWindow::FlipDisplay()
	{
	#ifdef _WIN32
		SwapBuffers(m_deviceContext);
	#endif // _WIN32

	#ifdef __linux__
		glXSwapBuffers(m_display, m_window);
	#endif // __linux__
	}

} // RGE
