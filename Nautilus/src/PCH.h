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

#ifndef _NT_PCH_H_
    #define _NT_PCH_H_

// C++ stdlib methods
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// C++ stdlib types
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

// Nautilus files
#include "Nautilus/Core.h"
#include "Nautilus/Log.h"

// External dependencies
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

// Platform dependencies
#if defined(NT_PLATFORM_WINDOWS)
    #include <Windows.h>
    #include <Winapifamily.h>
    #include <Windef.h>
    #include <Winbase.h>
#elif defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <signal.h>
    #include <sys/socket.h>
    #include <sys/stat.h>
    #include <time.h>
    #include <pthread.h>
    #include <dlfcn.h>
    #include <stdlib.h>
#endif // defined(NT_PLATFORM_WINDOWS), defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)

#endif // _NT_PCH_H_
