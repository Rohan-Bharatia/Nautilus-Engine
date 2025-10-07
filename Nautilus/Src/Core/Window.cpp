#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#ifndef _CORE_WINDOW_CPP_
    #define _CORE_WINDOW_CPP_

#include "Window.h"

#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ControllerEvent.h"
#include "Renderer/GraphicsContext.h"

namespace Nt
{
    static uint8 s_windowCount = 0;

    Window::Window(const WindowProperties& props) :
        m_props(props), m_window(nullptr), m_vsync(true)
    {
    #ifdef NT_PLATFORM_FAMILY_UNIX
        if (std::getenv("WAYLAND_DISPLAY") != nullptr)
            SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "wayland");
    #endif // NT_PLATFORM_FAMILY_UNIX

        if (s_windowCount == 0)
        {
            if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD))
            {
                NT_CORE_ERROR("SDL_Init failed: %s!", SDL_GetError());
                return;
            }
        }

        m_window = SDL_CreateWindow((const char*)props.title, (int32)props.width, (int32)props.height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

        if (!m_window)
        {
            NT_CORE_ERROR("SDL_CreateWindow failed: %s!", SDL_GetError());
            return;
        }

        ++s_windowCount;
        SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_ShowWindow(m_window);
        SDL_SyncWindow(m_window);

        m_context = CreateScope<GraphicsContext>(this);
    }

    Window::~Window(void)
    {
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            --s_windowCount;
        }

        if (s_windowCount == 0)
            SDL_Quit();
    }

    void Window::OnUpdate(float32 deltaTime)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // Window Events
                case SDL_EVENT_QUIT:
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                {
                    WindowCloseEvent e;
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    WindowResizeEvent e((uint32)event.window.data1, (uint32)event.window.data2);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_WINDOW_FOCUS_GAINED:
                {
                    WindowFocusEvent e;
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_WINDOW_FOCUS_LOST:
                {
                    WindowLostFocusEvent e;
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_WINDOW_MOVED:
                {
                    WindowMovedEvent e((int32)event.window.data1, (int32)event.window.data2);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }

                // Keyboard events
                case SDL_EVENT_KEY_DOWN:
                {
                    KeyPressedEvent e((uint32)event.key.key, event.key.repeat);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_KEY_UP:
                {
                    KeyReleasedEvent e((uint32)event.key.key);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }

                // Mouse events
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                {
                    MouseButtonPressedEvent e((uint32)event.button.button);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP:
                {
                    MouseButtonReleasedEvent e((uint32)event.button.button);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION:
                {
                    MouseMovedEvent e((float32)event.motion.x, (float32)event.motion.y);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_MOUSE_WHEEL:
                {
                    MouseScrolledEvent e((float32)event.wheel.x, (float32)event.wheel.y);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }

                // Controller events
                case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                {
                    GamepadButtonPressedEvent e((uint32)event.gbutton.button);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_GAMEPAD_BUTTON_UP:
                {
                    GamepadButtonReleasedEvent e((uint32)event.gbutton.button);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
                case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                {
                    JoystickAxisMovedEvent e((int32)event.jaxis.axis, (float32)event.jaxis.value);
                    if (m_eventCallback)
                        m_eventCallback(e);
                    break;
                }
            }
        }

        m_context->SwapBuffers();
    }

    String Window::GetTitle(void) const
    {
        return String(SDL_GetWindowTitle(m_window));
    }

    uint32 Window::GetWidth(void) const
    {
        int32 w;
        SDL_GetWindowSize(m_window, &w, nullptr);
        return (uint32)w;
    }

    uint32 Window::GetHeight(void) const
    {
        int32 h;
        SDL_GetWindowSize(m_window, nullptr, &h);
        return (uint32)h;
    }

    void Window::SetEventCallback(const EventCallbackFn& callback)
    {
        m_eventCallback = callback;
    }

    void Window::SetVSync(bool enabled)
    {
        m_context->SetVSync(enabled);
        m_vsync = enabled;
    }

    bool Window::IsVSync(void) const
    {
        return m_vsync;
    }

    void Window::SetFullscreen(bool fullscreen)
    {
        SDL_SetWindowFullscreen(m_window, fullscreen);
        m_context->Resize(GetWidth(), GetHeight());
        m_fullscreen = fullscreen;
    }

    bool Window::IsFullscreen(void) const
    {
        return m_fullscreen;
    }

    void* Window::GetNativeWindow(void) const
    {
        return (void*)m_window;
    }
} // namespace Nt

#endif // _CORE_WINDOW_CPP_
