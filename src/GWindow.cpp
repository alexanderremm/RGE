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
			// TODO: Log error
		}
	}

	GWindow::~GWindow()
	{
	#ifdef _WIN32
		m_handle = nullptr;
	#endif // _WIN32

	#ifdef __linux__
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
			pThis->m_closeWindow = false;

			// OpenGL context creation
			pThis->m_deviceContext = GetDC(hwnd);
			int wcpf; // Windows chosen pixel format
			wcpf = ChoosePixelFormat(pThis->m_deviceContext, &pfd);
			SetPixelFormat(pThis->m_deviceContext, wcpf, &pfd);

			pThis->m_glRenderingContext = wglCreateContext(pThis->m_deviceContext);
			wglMakeCurrent(pThis->m_deviceContext, pThis->m_glRenderingContext);

			glViewport(0, 0, pThis->m_width, pThis->m_height);

			MessageBoxA(0, (char*)glGetString(GL_VERSION), "OpenGL Version", 0); // Test display box
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
			ReleaseDC(m_handle, m_deviceContext);
			wglDeleteContext(m_glRenderingContext); // Delete the OpenGL rendering context
			PostQuitMessage(0);
			m_closeWindow = true;
			return 0;

		case WM_PAINT:
		{
			
		}
		return 0;

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
		m_swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask;

		m_window = XCreateWindow(m_display, DefaultRootWindow(m_display), 
			0, 0, 
			m_width, m_height, 0, 
			m_vi->depth, InputOutput, m_vi->visual, 
			CWColormap | CWEventMask, &m_swa);

		// Set the name of the window
		XStoreName(m_display, m_window, m_name);
		
		// Register interest in the delete window message
		m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(m_display, m_window, &m_wmDeleteMessage, 1);
		
		XMapWindow(m_display, m_window);

		// Create OpenGL context
		m_glRenderingContext = glXCreateContext(m_display, m_vi, NULL, GL_TRUE);
		glXMakeCurrent(m_display, m_window, m_glRenderingContext);
		glViewport(0, 0, m_width, m_height);

		// Prevent the window from closing
		m_closeWindow = false;

		return true;
	#endif // __linux__
	}

	// Poll for any window events
	void GWindow::PollEvent()
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

		if (e.type == ClientMessage && e.xclient.data.l[0] == m_wmDeleteMessage) 
		{
			glXMakeCurrent(m_display, None, NULL);
			glXDestroyContext(m_display, m_glRenderingContext);
			m_closeWindow = true;
		}

		if (e.type == KeyPress)
		{
			m_closeWindow = true;
		}
	#endif // __linux__
	}

	// Determine if the window should close or not
	bool GWindow::ShouldClose()
	{
		return m_closeWindow;
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
