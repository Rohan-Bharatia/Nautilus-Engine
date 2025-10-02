#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#pragma once

#ifndef _CORE_LOG_H_
    #define _CORE_LOG_H_

#include "String.h"

namespace Nt
{
    enum class LogLevel
    {
        None = 0,
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    class NT_API Log
    {
    public:
        NT_CLASS_DEFAULTS(Log)

        static void Initialize(String path);

        static void Message(LogLevel level, String tag, String message, ...);

    private:
        static String s_path;
    };
} // namespace Nt

#define NT_CORE_TRACE(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Trace, "NAUTILUS", msg, ##__VA_ARGS__)
#define NT_CORE_DEBUG(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Debug, "NAUTILUS", msg, ##__VA_ARGS__)
#define NT_CORE_INFO(msg, ...)  ::Nt::Log::Message(::Nt::LogLevel::Info, "NAUTILUS", msg, ##__VA_ARGS__)
#define NT_CORE_WARN(msg, ...)  ::Nt::Log::Message(::Nt::LogLevel::Warning, "NAUTILUS", msg, ##__VA_ARGS__)
#define NT_CORE_ERROR(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Error, "NAUTILUS", msg, ##__VA_ARGS__)
#define NT_CORE_FATAL(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Fatal, "NAUTILUS", msg, ##__VA_ARGS__)

#define NT_CLIENT_TRACE(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Trace, "APPLICATION", msg, ##__VA_ARGS__)
#define NT_CLIENT_DEBUG(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Debug, "APPLICATION", msg, ##__VA_ARGS__)
#define NT_CLIENT_INFO(msg, ...)  ::Nt::Log::Message(::Nt::LogLevel::Info, "APPLICATION", msg, ##__VA_ARGS__)
#define NT_CLIENT_WARN(msg, ...)  ::Nt::Log::Message(::Nt::LogLevel::Warning, "APPLICATION", msg, ##__VA_ARGS__)
#define NT_CLIENT_ERROR(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Error, "APPLICATION", msg, ##__VA_ARGS__)
#define NT_CLIENT_FATAL(msg, ...) ::Nt::Log::Message(::Nt::LogLevel::Fatal, "APPLICATION", msg, ##__VA_ARGS__)

#endif // _CORE_LOG_H_
