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

#ifndef _NT_NAUTILUS_PLATFORM_LINUX_INPUT_CPP_
    #define _NT_NAUTILUS_PLATFORM_LINUX_INPUT_CPP_

#include "LinuxInput.h"

#include "Nautilus/Application.h"

namespace Nt
{
    Input* Input::s_instance = new LinuxInput();

    bool LinuxInput::IsKeyPressedImpl(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state          = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state          = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImpl()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return std::pair<float, float>((float)xpos, (float)ypos);
    }

    float LinuxInput::GetMouseXImpl()
    {
        const auto[x, y] = GetMousePositionImpl();
        return x;
    }

    float LinuxInput::GetMouseYImpl()
    {
        const auto[x, y] = GetMousePositionImpl();
        return y;
    }
}

#endif // _NT_NAUTILUS_PLATFORM_LINUX_INPUT_CPP_
