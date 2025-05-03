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

#ifndef _NT_NAUTILUS_INPUT_CPP_
    #define _NT_NAUTILUS_INPUT_CPP_

#include "Input.h"

namespace Nt
{
    bool Input::IsKeyPressed(int keycode)
    {
        return s_instance->IsKeyPressedImpl(keycode);
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        return s_instance->IsMouseButtonPressedImpl(button);
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        return s_instance->GetMousePositionImpl();
    }

    float Input::GetMouseX()
    {
        return s_instance->GetMouseXImpl();
    }

    float Input::GetMouseY()
    {
        return s_instance->GetMouseYImpl();
    }
}

#endif // _NT_NAUTILUS_INPUT_CPP_
