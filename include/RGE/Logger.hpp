#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

namespace RGE
{
	typedef uint8_t LOG_LEVEL;

	// Define different log levels
	enum : LOG_LEVEL
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

	class Logger
	{
	public:
		Logger(const char* fileName = nullptr)
		{
			
		}

		~Logger()
		{

		}

		template<typename T>
		static void LOG(LOG_LEVEL logLevel, T msg)
		{
		#ifdef _WIN32
			HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
		#endif // _WIN32

			// Get the current time
			time_t rawTime;
			struct tm* timeInfo;
			char dateTimeString[25];

			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(dateTimeString, sizeof(dateTimeString), "%F | %X | ", timeInfo);

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
			logMessage << msg << std::endl;

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
	#ifdef _WIN32
	
		static void SetConsoleColor(int colorCode)
		{
			HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(cHandle, colorCode);
		}
		
	#endif // _WIN32

	};

} // RGE

#endif // LOGGER_HPP