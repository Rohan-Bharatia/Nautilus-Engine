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

#pragma once

#ifndef _CORE_WINDOW_H_
    #define _CORE_WINDOW_H_

#include "Event.h"

namespace Nt
{
    struct NT_API WindowProperties
    {
        String title  = "Nautilus Engine";
        uint32 width  = 1280;
        uint32 height = 720;
    };

    class GraphicsContext;

    class NT_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        NT_CLASS_DEFAULTS(Window)
        Window(const WindowProperties& props);
        ~Window(void);

        void OnUpdate(float32 deltaTime);

        String GetTitle(void) const;
        uint32 GetWidth(void) const;
        uint32 GetHeight(void) const;

        void SetEventCallback(const EventCallbackFn& callback);
        void SetVSync(bool enabled);
        bool IsVSync(void) const;
        void SetFullscreen(bool fullscreen);
        bool IsFullscreen(void) const;

        void* GetNativeWindow(void) const;
        void* GetNativeContext(void) const;

    private:
        SDL_Window* m_window;
        WindowProperties m_props;
        Scope<GraphicsContext> m_context;
        bool m_vsync;
        bool m_fullscreen;
        EventCallbackFn m_eventCallback;
    };
} // namespace Nt

#endif // _CORE_WINDOW_H_
