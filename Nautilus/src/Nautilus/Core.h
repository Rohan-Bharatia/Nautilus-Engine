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

#ifndef _NT_NAUTILUS_CORE_H_
    #define _NT_NAUTILUS_CORE_H_

#if defined(NT_PLATFORM_WINDOWS)
    #if defined(NT_BUILD_SHARED)
        #define NT_API __declspec(dllexport)
    #else // (NOT) defined(NT_BUILD_SHARED)
        #define NT_API __declspec(dllimport)
    #endif // defined(NT_BUILD_SHARED)
#elif defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)
    #if defined(NT_BUILD_SHARED)
        #define NT_API __attribute__((visibility("default")))
    #else // (NOT) defined(NT_BUILD_SHARED)
        #define NT_API __attribute__((visibility("hidden")))
    #endif // defined(NT_BUILD_SHARED)
#else // (NOT) defined(NT_PLATFORM_WINDOWS), defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)
    #define NT_API
#endif // defined(NT_PLATFORM_WINDOWS), defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)

#endif // _NT_NAUTILUS_CORE_H_
