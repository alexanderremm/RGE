#ifndef WIN32_WINDOW_HPP
#define WIN32_WINDOW_HPP

#include <Windows.h>
//#pragma comment (lib, "opengl32.lib")

#include "Math.hpp"

namespace RGE
{
	class GWindow
	{
	public:
		GWindow(const char* windowName, const Math::v2i& dims);
		~GWindow();

		bool Init();
		void PollEvent();
		bool ShouldClose();

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Member vars
		WNDCLASS m_wc = {};
		HWND m_handle;
		HINSTANCE m_instance;

		MSG m_msg = {};

		const char* m_name;
		int m_width;
		int m_height;

		bool m_closeWindow = true; // Is the window not active/should it be closed
	};
} // RGE

#endif // !WIN32_WINDOW_HPP
