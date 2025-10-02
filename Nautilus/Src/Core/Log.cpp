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

#ifndef _CORE_LOG_CPP_
    #define _CORE_LOG_CPP_

#include "Log.h"

#include "IO.h"
#include "Timer.h"

namespace Nt
{
    String Log::s_path;

    void Log::Initialize(String path)
    {
        s_path = path;
        WriteFile(s_path, "", true);
    }

    void Log::Message(LogLevel level, String tag, String message, ...)
    {
        String color, levelStr;

        switch (level)
        {
            case LogLevel::Trace:
                color    = "\e[36m"; // Cyan
                levelStr = "TRACE";
                break;
            case LogLevel::Debug:
                color    = "\e[34m"; // Blue
                levelStr = "DEBUG";
                break;
            case LogLevel::Info:
                color    = "\e[32m"; // Green
                levelStr = "INFO";
                break;
            case LogLevel::Warning:
                color    = "\e[33m"; // Yellow
                levelStr = "WARNING";
                break;
            case LogLevel::Error:
                color    = "\e[31m"; // Red
                levelStr = "ERROR";
                break;
            case LogLevel::Fatal:
                color    = "\e[35m"; // Magenta
                levelStr = "FATAL";
                break;
        }

        String time = DateTime::Now("%Y-%m-%d %H:%M:%S %Z %z");

        va_list args;
        va_start(args, message);
        char* buffer = new char[1024];
        std::vsnprintf(buffer, 1024, message, args);
        va_end(args);
        message      = String(buffer);
        delete[] buffer;

        String consoleOutput = color + "[" + time + "]" + "[" + tag + "][" + levelStr + "]:\e[0m " + message;
        String fileOutput    = String("[") + time + "]" + "[" + tag + "][" + levelStr + "]: " + message + "\n";

        WriteConsole(consoleOutput);
        WriteFile(s_path, fileOutput);
    }
} // namespace Nt

#endif // _CORE_LOG_CPP_
