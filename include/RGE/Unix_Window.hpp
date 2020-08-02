#ifndef UNIX_WINDOW_HPP
#define UNIX_WINDOW_HPP

#include <X11/Xlib.h>

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
        Display *m_display;
        int m_screen;
        Window m_window;

        const char* m_name;
		int m_width;
		int m_height;

        bool m_closeWindow = true; // Is the window not active/should it be closed
    };

} // RGE

#endif // UNIX__WINDOW_HPP