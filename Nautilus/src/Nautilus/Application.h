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

#ifndef _NT_NAUTILUS_APPLICATION_H_
    #define _NT_NAUTILUS_APPLICATION_H_

#include "PCH.h"

#include "Window.h"

namespace Nt
{
    class NT_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_window;
        bool m_isRunning;
    };

    // *Defined by the client*
    Application* CreateApplication();
} // namespace Nt

#endif // _NT_NAUTILUS_APPLICATION_H_
