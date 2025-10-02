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
        std::string data;
        std::getline(std::cin, data);
        return String(data);
    }

    String ReadFile(const char* path)
    {
        std::ifstream file = std::ifstream(path);
        std::string data((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();
        return String(data);
    }

    void WriteConsole(const std::string& data, bool newline)
    {
        std::cout << data;
        if (newline)
            std::cout << std::endl;
        std::cout.flush();
    }

    void WriteFile(const char* path, const std::string& data)
    {
        std::ofstream file = std::ofstream(path);
        file << data;
        file.flush();
        file.close();
    }
} // namespace Nt

#endif // _CORE_IO_CPP_
