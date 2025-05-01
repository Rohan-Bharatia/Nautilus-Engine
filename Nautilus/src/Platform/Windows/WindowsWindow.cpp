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

#ifndef _NT_NAUTILUS_PLATFORM_WINDOWS_WINDOW_CPP_
    #define _NT_NAUTILUS_PLATFORM_WINDOWS_WINDOW_CPP_

#include "WindowsWindow.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace Nt
{
    static bool s_glfwInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Initialize(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    std::string WindowsWindow::GetTitle() const
    {
        return m_data.title;
    }

    unsigned int WindowsWindow::GetWidth() const
    {
        return m_data.width;
    }

    unsigned int WindowsWindow::GetHeight() const
    {
        return m_data.height;
    }

    void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
    {
        m_data.callback = callback;
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled);
        m_data.vsync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_data.vsync;
    }

    void WindowsWindow::Initialize(const WindowProps& props)
    {
        m_data.title  = props.title;
        m_data.width  = props.width;
        m_data.height = props.height;

        NT_CORE_LOG_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!s_glfwInitialized)
        {
            int success = glfwInit();
            NT_ASSERT(success, "Could not initialize GLFW!");

            glfwSetErrorCallback([](int error, const char* description)
            {
                NT_CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
            });

            s_glfwInitialized = true;
        }

        m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NT_ASSERT(success, "Could not initialize GLAD!");

        glfwSetWindowUserPointer(m_window, &m_data);
        SetVSync(true);

        // Set window callbacks
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data->callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data->callback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data->callback(event);
                    break;
                }
                default:
                {
                    break;
                }
            };
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button, 0);
                    data->callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data->callback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    MouseButtonPressedEvent event(button, 1);
                    data->callback(event);
                    break;
                }
                default:
                {
                    break;
                }
            };
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data->callback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data->callback(event);
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
            data->width      = width;
            data->height     = height;

            WindowResizeEvent event(width, height);
            data->callback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data->callback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

#endif // _NT_NAUTILUS_PLATFORM_WINDOWS_WINDOW_CPP_
