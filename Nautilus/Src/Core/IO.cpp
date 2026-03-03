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

#ifndef _CORE_IO_CPP_
    #define _CORE_IO_CPP_

#include "IO.h"

namespace Nt
{
    String ReadConsole(void)
    {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    String ReadFile(const String& path)
    {
        std::ifstream file((const char*)path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void WriteConsole(const String& data, bool newline)
    {
        std::cout << (const char*)data;
        if (newline)
            std::cout << std::endl;
    }

    void WriteFile(const String& path, const String& data, bool overwrite)
    {
        std::ofstream file((const char*)path, overwrite ? std::ios::trunc : std::ios::app);
        NT_ASSERT(file.is_open(), "Failed to open file: %s", path);
        file << (const char*)data;
        file.close();
    }
} // namespace Nt

#endif // _CORE_IO_CPP_
