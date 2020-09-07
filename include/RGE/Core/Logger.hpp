#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "RGE/rge_exports.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include "Util.hpp"

namespace RGE
{
	typedef uint8_t LOG_LEVEL;

	// Define different log levels
	enum RGE_EXPORT : LOG_LEVEL
	{
		LOG_INFO,
		LOG_DEBUG,
		LOG_WARN,
		LOG_ERROR
	};

	// Define some conosle colors
#ifdef _WIN32
// See https://ss64.com/nt/color.html for color codes
	constexpr auto RED = 12;
	constexpr auto BLUE = 9;
	constexpr auto YELLOW = 14;
	constexpr auto DEFAULT_COLOR = 7;
#endif // _WIN32

#ifdef __linux__
	constexpr auto RED = "[1;31m";
	constexpr auto BLUE = "[1;34m";
	constexpr auto YELLOW = "[1;33m";
	constexpr auto DEFAULT_COLOR = "[0m";
#endif // __linux__

	class RGE_EXPORT Logger
	{
	public:
		Logger(const char* fileName = "")
		{
			// Check if the log file already exists
			if (FileExists(fileName))
			{
				LOG(LOG_WARN, "Log file: ", fileName, " already exists!");
			}

			m_logFile.open(fileName, std::fstream::out);

			// Make sure the log file was created
			if (!m_logFile)
			{
				LOG(LOG_ERROR, "Failed to create the log file: ", fileName);
				LOG(LOG_INFO, "Check permissions or ensure that the file does not exists already");
			}

			m_logFileCreated = true;
		}

		~Logger()
		{
			m_logFile.close();
		}

		template<typename First, typename... Args>
		void LOG(LOG_LEVEL logLevel, First msg, Args... msgs)
		{
			LOGC(logLevel, msg, msgs...);
			LOGF(logLevel, msg, msgs...);
		}

		// Logs information to a file, requires an instance of the Logger
		template<typename First, typename... Args>
		void LOGF(LOG_LEVEL logLevel, First msg, Args... msgs)
		{
			// Make sure the log file exists before we write to it
			if (m_logFileCreated)
			{
				// Create the log message (no coloring information)
				// Get the current time
				time_t rawTime;
				struct tm timeInfo;
				char dateTimeString[25];

				time(&rawTime);
#ifdef _WIN32
				localtime_s(&timeInfo, &rawTime); // Thread-safe windows implementation
#elif defined(__linux__)
				localtime_r(&rawTime, &timeInfo); // Thread-safe linux implementation
#endif // _WIN32
				strftime(dateTimeString, sizeof(dateTimeString), "%F | %X | ", &timeInfo);

				const char* level = "";

				// TODO: Use a switch statement
				if (logLevel == LOG_INFO)
				{
					level = "[INFO]: ";
				}

				else if (logLevel == LOG_DEBUG)
				{
					level = "[DEBUG]: ";
				}

				else if (logLevel == LOG_WARN)
				{
					level = "[WARN]: ";
				}

				else if (logLevel == LOG_ERROR)
				{
					level = "[ERROR]: ";
				}

				// Build the log message
				// Format: Date | Time | [Log Level]: Message
				std::stringstream logMessage;

				// Unpack parameter values and add to the log message
				LOG(logMessage, msg, msgs...);

				// Write the output to the log file
				m_logFile << dateTimeString << level << logMessage.str() << std::endl;

			}
		}

		// Logs information to the console
		template<typename First, typename... Args>
		static void LOGC(LOG_LEVEL logLevel, First msg, Args... msgs)
		{
#ifdef _WIN32
			HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif // _WIN32

			// Get the current time
			time_t rawTime;
			struct tm timeInfo;
			char dateTimeString[25];

			time(&rawTime);
#ifdef _WIN32
			localtime_s(&timeInfo, &rawTime); // Thread-safe windows implementation
#elif defined(__linux__)
			localtime_r(&rawTime, &timeInfo); // Thread-safe linux implementation
#endif // _WIN32
			strftime(dateTimeString, sizeof(dateTimeString), "%F | %X | ", &timeInfo);

#ifdef _WIN32
			int label_color;
			int msg_color;
			const char* level = "";
#endif // _WIN32

#ifdef __linux__
			const char* label_color = "";
			const char* msg_color = "";
			const char* level = "";
#endif // __linux__

			// TODO: Use a switch statement
			if (logLevel == LOG_INFO)
			{
				label_color = DEFAULT_COLOR;
				msg_color = DEFAULT_COLOR;
				level = "[INFO]: ";
			}

			else if (logLevel == LOG_DEBUG)
			{
				label_color = BLUE;
				msg_color = DEFAULT_COLOR;
				level = "[DEBUG]: ";
			}

			else if (logLevel == LOG_WARN)
			{
				label_color = YELLOW;
				msg_color = YELLOW;
				level = "[WARN]: ";
			}

			else if (logLevel == LOG_ERROR)
			{
				label_color = RED;
				msg_color = RED;
				level = "[ERROR]: ";
			}

			// Build the log message
			// Format: Date | Time | [Log Level]: Message
			std::stringstream logMessage;

			// Unpack parameter values and add to the log message
			LOG(logMessage, msg, msgs...);
			logMessage << std::endl;

			// Print the actual log message
#ifdef _WIN32
			std::cout << dateTimeString;
			SetConsoleColor(label_color);
			std::cout << level;
			SetConsoleColor(msg_color);
			std::cout << logMessage.str();
			SetConsoleColor(DEFAULT_COLOR);
#endif // _WIN32

#ifdef __linux__
			// See: https://stackoverflow.com/questions/2353430/how-can-i-print-to-the-console-in-color-in-a-cross-platform-manner for more information about coloring the console
			printf("%s%c%s%s%c%s%s%c%s", dateTimeString, 27, label_color, level, 27, msg_color, logMessage.str().c_str(), 27, DEFAULT_COLOR);
#endif // __linux__

		}

	private:
		// Recursive variadic parameter unpacking functions
		// See: https://raymii.org/s/snippets/Cpp_variadic_template_recursive_example.html
		template<typename T>
		static void LOG(std::stringstream& ss, T arg)
		{
			ss << arg;
		}

		template<typename First, typename ...Args>
		static void LOG(std::stringstream& ss, First first, Args ...args)
		{
			LOG(ss, first);
			LOG(ss, args...);
		}

#ifdef _WIN32
		static void SetConsoleColor(int colorCode)
		{
			HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(cHandle, colorCode);
		}
#endif // _WIN32

		bool m_logFileCreated = false;
		std::fstream m_logFile;

	};

} // RGE

#endif // LOGGER_HPP
