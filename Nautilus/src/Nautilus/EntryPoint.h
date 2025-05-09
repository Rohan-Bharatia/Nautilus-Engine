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

#ifndef _NT_NAUTILUS_ENTRY_POINT_H_
    #define _NT_NAUTILUS_ENTRY_POINT_H_

#include "Application.h"
#include "Log.h"

extern Nt::Application* Nt::CreateApplication();

int main(int argc, char** argv)
{
    if (!Nt::Log::Initialize())
        return -1;

    NT_CORE_LOG_INFO("Nautilus Engine initialized!");
    NT_CLIENT_LOG_INFO("Sandbox initialized!");

    auto app = Nt::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif // _NT_NAUTILUS_ENTRY_POINT_H_
