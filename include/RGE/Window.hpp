/*!
	Abstract class for the creation and management of a window.
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#ifdef _WIN32
#include "WIN32_Window.hpp"
#endif // _WIN32

#ifdef __linux__
#include "Unix_Window.hpp"
#endif // unix

#endif // WINDOW_HPP
