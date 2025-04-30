#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                                 ...
//
//                  Copyright (c) Rohan Bharatia 2025

#pragma endregion LICENSE

#pragma once

#ifndef _NT_NAUTILUS_LOG_H_
    #define _NT_NAUTILUS_LOG_H_

#include "PCH.h"

#include <spdlog/spdlog.h>

namespace Nt
{
    class NT_API Log
    {
    public:
        static bool Initialize();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger();
        static std::shared_ptr<spdlog::logger>& GetClientLogger();

    private:
        static std::shared_ptr<spdlog::logger> m_coreLogger;
        static std::shared_ptr<spdlog::logger> m_clientLogger;
    };
}

// Core logger macros
#define NT_CORE_LOG_TRACE(...)    Nt::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NT_CORE_LOG_DEBUG(...)    Nt::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define NT_CORE_LOG_INFO(...)     Nt::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NT_CORE_LOG_WARN(...)     Nt::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NT_CORE_LOG_ERROR(...)    Nt::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NT_CORE_LOG_CRITICAL(...) Nt::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client logger macros
#define NT_CLIENT_LOG_TRACE(...)    Nt::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NT_CLIENT_LOG_DEBUG(...)    Nt::Log::GetClientLogger()->debug(__VA_ARGS__)
#define NT_CLIENT_LOG_INFO(...)     Nt::Log::GetClientLogger()->info(__VA_ARGS__)
#define NT_CLIENT_LOG_WARN(...)     Nt::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NT_CLIENT_LOG_ERROR(...)    Nt::Log::GetClientLogger()->error(__VA_ARGS__)
#define NT_CLIENT_LOG_CRITICAL(...) Nt::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif // _NT_NAUTILUS_LOG_H_
