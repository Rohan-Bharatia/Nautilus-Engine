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

#ifndef _ENTRY_POINT_H_
    #define _ENTRY_POINT_H_

#include "Nautilus.h"

#ifdef NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_MAIN_FN int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hinstancePrev, PSTR cmdline, int cmdshow)
    #define NT_ARGC __argc
    #define NT_ARGV __argv
#else // (NOT) NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_MAIN_FN int main(int argc, char* argv[])
    #define NT_ARGC argc
    #define NT_ARGV argv
#endif // NT_PLATFORM_FAMILY_MICROSOFT

namespace Nt
{
    extern Application* CreateApplication(int32 argc, char* argv[]);
} // namespace Nt

NT_MAIN_FN
{
    if (!NT_VERSION_CHECK(1, 0, 0))
        throw std::runtime_error("Nautilus requires at least version 1.0.0 to run!");

    auto app = Nt::CreateApplication((Nt::int32)NT_ARGC, NT_ARGV);
    app->Run();
    NT_SAFE_DELETE(app);
    return EXIT_SUCCESS;
}

#endif // _ENTRY_POINT_H_
