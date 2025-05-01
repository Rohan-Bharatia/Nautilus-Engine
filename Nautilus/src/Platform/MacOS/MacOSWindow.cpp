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

#ifndef _NT_NAUTILUS_PLATFORM_MACOS_WINDOW_CPP_
    #define _NT_NAUTILUS_PLATFORM_MACOS_WINDOW_CPP_

#include "MacOSWindow.h"

namespace Nt
{
    static bool s_glfwInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new MacOSWindow(props);
    }

    MacOSWindow::MacOSWindow(const WindowProps& props)
    {
        Initialize(props);
    }

    MacOSWindow::~MacOSWindow()
    {
        Shutdown();
    }

    void MacOSWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    std::string MacOSWindow::GetTitle() const
    {
        return m_data.title;
    }

    unsigned int MacOSWindow::GetWidth() const
    {
        return m_data.width;
    }

    unsigned int MacOSWindow::GetHeight() const
    {
        return m_data.height;
    }

    void MacOSWindow::SetEventCallback(const EventCallbackFn& callback)
    {
        m_data.callback = callback;
    }

    void MacOSWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled);
        m_data.vsync = enabled;
    }

    bool MacOSWindow::IsVSync() const
    {
        return m_data.vsync;
    }

    void MacOSWindow::Initialize(const WindowProps& props)
    {
        m_data.title  = props.title;
        m_data.width  = props.width;
        m_data.height = props.height;

        NT_CORE_LOG_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!s_glfwInitialized)
        {
            int success = glfwInit();
            NT_ASSERT(success, "Could not initialize GLFW!");

            s_glfwInitialized = true;
        }

        m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        glfwSetWindowUserPointer(m_window, &m_data);
        SetVSync(true);
    }

    void MacOSWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

#endif // _NT_NAUTILUS_PLATFORM_MACOS_WINDOW_CPP_
