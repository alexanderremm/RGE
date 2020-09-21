#define RGE_EXPORTS

#include "RGE/Core/Logging.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace RGE
{
    std::shared_ptr<spdlog::logger> Logging::s_coreConsoleLogger;
    std::shared_ptr<spdlog::logger> Logging::s_clientConsoleLogger;
    
    void Logging::Init()
    {
        s_coreConsoleLogger = spdlog::stdout_color_mt("RGE");
        s_coreConsoleLogger->set_level(spdlog::level::trace);

        s_clientConsoleLogger = spdlog::stdout_color_mt("APP");
        s_clientConsoleLogger->set_level(spdlog::level::trace);
    }

} // RGE
