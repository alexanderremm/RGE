/*!
	Class for the creation and management of a window.
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#ifdef unix

#endif // unix

#include <string>

#include "Math.hpp"

namespace RGE
{
	class Window
	{
	public:
		Window(std::string window_name, Math::v2i dims);
		~Window();
	private:
#ifdef _WIN32
		bool WindowsInitialize();

		WNDCLASS wc = {};
#endif // _WIN32

#ifdef unix
		bool LinuxInitialize();
#endif // unix


		std::string name;
		int width;
		int height;
	};
} // RGE

#endif // WINDOW_HPP