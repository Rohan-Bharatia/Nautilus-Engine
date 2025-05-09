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

#ifndef _NT_NAUTILUS_INPUT_H_
    #define _NT_NAUTILUS_INPUT_H_

#include "PCH.h"

namespace Nt
{
    class NT_API Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();

    protected:
        virtual bool IsKeyPressedImpl(int keycode)             = 0;
        virtual bool IsMouseButtonPressedImpl(int button)      = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl()                          = 0;
        virtual float GetMouseYImpl()                          = 0;

    private:
        static Input* s_instance;
    };
}

#endif // _NT_NAUTILUS_INPUT_H_
