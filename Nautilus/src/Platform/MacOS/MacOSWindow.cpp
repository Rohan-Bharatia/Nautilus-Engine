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

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
        m_context->SwapBuffers();
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

    void* MacOSWindow::GetNativeWindow() const
    {
        return static_cast<void*>(m_window);
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

            glfwSetErrorCallback([](int error, const char* description)
            {
                NT_CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
            });

            s_glfwInitialized = true;
        }

        m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
        m_context = new OpenGLContext(m_window);

        m_context->Initialize();

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

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data->callback(event);
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

    void MacOSWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

#endif // _NT_NAUTILUS_PLATFORM_MACOS_WINDOW_CPP_
