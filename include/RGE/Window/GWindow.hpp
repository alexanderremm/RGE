#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RGE/Logger.hpp"

namespace RGE
{
	/**
	* A structure to hold properties of a window definition
	*/
	struct GWindowProperties
	{
		unsigned width;				// Width of the window
		unsigned height;			// Height of the window
		const char* title;			// Title of the window
		bool resizeable = false;	// Flag for whether the window should be resizeable or not
	};
	/**
	* \class GWindow
	* 
	* \brief The main windowing class used to handle window operations:
	* open/close/draw/etc.
	*/
	class GWindow
	{
	public:
		/**
		* \brief Window constructor
		* 
		* \param[in] windowProperties Initial window properties
		*/
		GWindow(GWindowProperties windowProperties);

		/**
		* \brief Window constructor
		*
		* \param[in] width Initial window width
		* \param[in] height Initial window height
		* \param[in] title Window title
		* \param[in] resizeable Flag for whether the window should be resizeable or not
		*/
		GWindow(unsigned width, unsigned height, const char* title, bool resizeable = false);

		/**
		* \brief Window destructor
		*/
		~GWindow();

		/**
		* \brief Initializes the window and creates the window context
		* 
		* \returns True if the window creation was successful, false if there was an error
		*/
		bool Init();

		/**
		* \brief Function to determine if the window should close or not
		* 
		* \returns True if the window should close, false if it should stay open
		*/
		bool ShouldClose() const;

		/**
		* \brief Poll for any window events
		*/
		void PollEvents();

		/**
		* \brief Swap display buffers and update screen
		*/
		void SwapBuffers();

	private:
		GWindowProperties m_windowProps;
		GLFWwindow* m_window = nullptr;
	};

} // RGE
