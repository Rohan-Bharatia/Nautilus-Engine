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

#ifndef _NT_SANDBOX_SANDBOX_CPP_
    #define _NT_SANDBOX_SANDBOX_CPP_

#if defined(NT_PLATFORM_WINDOWS)
    #define NT_API __declspec(dllimport)
#elif defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)
    #define NT_API __attribute__((visibility("default")))
#else
    #define NT_API
#endif // defined(NT_PLATFORM_WINDOWS), defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_MACOS)

namespace Nt
{
    NT_API void print();
} // namespace Nt

int main(int argc, char* argv[])
{
    Nt::print();

    return 0;
}

#endif // _NT_SANDBOX_SANDBOX_CPP_
