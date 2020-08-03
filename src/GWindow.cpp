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
		XCloseDisplay(m_display);
	#endif // __linux__
	}

	// ---- Windows Specific Methods ---- //
	#ifdef _WIN32
	LRESULT CALLBACK GWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		GWindow* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (GWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_handle = hwnd;
			pThis->m_closeWindow = false;
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
			PostQuitMessage(0);
			m_closeWindow = true;
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_handle, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(m_handle, &ps);
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
			CS_OWNDC,													// Optional window styles.
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
		XNextEvent(m_display, &e);

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

} // RGE
