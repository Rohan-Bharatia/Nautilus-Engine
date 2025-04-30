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

#ifndef _NT_NAUTILUS_LOG_CPP_
    #define _NT_NAUTILUS_LOG_CPP_

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Nt
{
    std::shared_ptr<spdlog::logger> Log::m_coreLogger;
    std::shared_ptr<spdlog::logger> Log::m_clientLogger;

    bool Log::Initialize()
    {
        spdlog::set_pattern("%^[%T][%n]: %v%$");

        m_coreLogger = spdlog::stdout_color_mt("NAUTILUS");
        m_coreLogger->set_level(spdlog::level::trace);

        if (!m_coreLogger)
            return false;

        m_clientLogger = spdlog::stdout_color_mt("SANDBOX");
        m_clientLogger->set_level(spdlog::level::trace);

        if (!m_clientLogger)
            return false;

        return true;
    }

    std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
    {
        return m_coreLogger;
    }

    std::shared_ptr<spdlog::logger>& Log::GetClientLogger()
    {
        return m_clientLogger;
    }
}

#endif // _NT_NAUTILUS_LOG_CPP_
