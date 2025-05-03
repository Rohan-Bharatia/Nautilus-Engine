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

#ifndef _NT_NAUTILUS_PLATFORM_MACOS_INPUT_CPP_
    #define _NT_NAUTILUS_PLATFORM_MACOS_INPUT_CPP_

#include "MacOSInput.h"

#include "Nautilus/Application.h"

namespace Nt
{
    Input* Input::s_instance = new MacOSInput();

    bool MacOSInput::IsKeyPressedImpl(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        return glfwGetKey(window, keycode) == (GLFW_PRESS | GLFW_REPEAT);
    }

    bool MacOSInput::IsMouseButtonPressedImpl(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    std::pair<float, float> MacOSInput::GetMousePositionImpl()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::pair<float, float>((float)xpos, (float)ypos);
    }

    float MacOSInput::GetMouseXImpl()
    {
        const auto[x, y] = GetMousePositionImpl();
        return x;
    }

    float MacOSInput::GetMouseYImpl()
    {
        const auto[x, y] = GetMousePositionImpl();
        return y;
    }
}

#endif // _NT_NAUTILUS_PLATFORM_MACOS_INPUT_CPP_
