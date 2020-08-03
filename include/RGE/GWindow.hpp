/*!
	Abstract class for the creation and management of a window.
*/

#ifndef GWINDOW_HPP
#define GWINDOW_HPP

#ifdef _WIN32
#include <Windows.h>
//#pragma comment (lib, "opengl32.lib")
#endif // _WIN32

#ifdef __linux__
#include <X11/Xlib.h>
#endif // unix

#include "Math.hpp"


namespace RGE
{
	class GWindow
	{
	public:
		GWindow(const char* windowName, const Math::v2i& dims);
		~GWindow();

		// Common API
		bool Init();
		void PollEvent();
		bool ShouldClose();

	private:
		const char* m_name;
		int m_width;
		int m_height;

		bool m_closeWindow = true; // Is the window active/should it be closed

		// Windows implementation
		#ifdef _WIN32
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Member vars
		WNDCLASS m_wc = {};
		HWND m_handle;
		HINSTANCE m_instance;

		MSG m_msg = {};
		#endif // _WIN32

		// Linux implementation
		#ifdef __linux__
		Display* m_display;
		int m_screen;
		Window m_window;
		#endif // __linux__

	};

} // RGE

#endif // GWINDOW_HPP
