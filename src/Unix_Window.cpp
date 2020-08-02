#include "RGE/Unix_Window.hpp"

namespace RGE
{
    GWindow::GWindow(const char* windowName, const Math::v2i &dims)
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
        XCloseDisplay(m_display);
    }

    bool GWindow::Init()
    {
        m_display = XOpenDisplay(NULL);
        if (m_display == NULL)
        {
            // Failed to initialize the display
            return false;
        }

        m_screen = DefaultScreen(m_display);

        m_window = XCreateSimpleWindow(m_display,
            RootWindow(m_display, m_screen), 10, 10,
            m_width, m_height, 1, BlackPixel(m_display, m_screen),
            WhitePixel(m_display, m_screen));

        XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
        XMapWindow(m_display, m_window);

        // Prevent the window from closing
        m_closeWindow = false;

        return true;
    }

    void GWindow::PollEvent()
    {
        XEvent e;
        XNextEvent(m_display, &e);
        
        if (e.type == KeyPress)
        {
            m_closeWindow = true;
        }
    }

    bool GWindow::ShouldClose()
    {
        return m_closeWindow;
    }
} // RGE
