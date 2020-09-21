#ifndef LOGGING_HPP
#define LOGGING_HPP

#include "RGE/rge_exports.h"

#include <spdlog/spdlog.h>

namespace RGE
{
    class RGE_EXPORT Logging
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreConsoleLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientConsoleLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_coreConsoleLogger;
        static std::shared_ptr<spdlog::logger> s_clientConsoleLogger;
    };

} // RGE

// Core log macros
#define RGE_CORE_TRACE(...) ::RGE::Logging::GetCoreLogger()->trace(__VA_ARGS__)
#define RGE_CORE_INFO(...)  ::RGE::Logging::GetCoreLogger()->info(__VA_ARGS__)
#define RGE_CORE_WARN(...)  ::RGE::Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define RGE_CORE_ERROR(...) ::RGE::Logging::GetCoreLogger()->error(__VA_ARGS__)
#define RGE_CORE_FATAL(...) ::RGE::Logging::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RGE_TRACE(...)      ::RGE::Logging::GetClientLogger()->trace(__VA_ARGS__)
#define RGE_INFO(...)       ::RGE::Logging::GetClientLogger()->info(__VA_ARGS__)
#define RGE_WARN(...)       ::RGE::Logging::GetClientLogger()->warn(__VA_ARGS__)
#define RGE_ERROR(...)      ::RGE::Logging::GetClientLogger()->error(__VA_ARGS__)
#define RGE_FATAL(...)      ::RGE::Logging::GetClientLogger()->critical(__VA_ARGS__)

#endif // LOGGING_HPP
