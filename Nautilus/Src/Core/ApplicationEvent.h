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

#ifndef _CORE_APPLICATION_EVENT_H_
    #define _CORE_APPLICATION_EVENT_H_

#include "Event.h"

namespace Nt
{
    class NT_API WindowCloseEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(WindowCloseEvent)
        WindowCloseEvent(void) = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NT_API WindowResizeEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(WindowResizeEvent)
        WindowResizeEvent(uint32 width, uint32 height);

        uint32 GetWidth(void) const;
        uint32 GetHeight(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        uint32 m_width, m_height;
    };

    class NT_API WindowFocusEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(WindowFocusEvent)
        WindowFocusEvent(void) = default;

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NT_API WindowLostFocusEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(WindowLostFocusEvent)
        WindowLostFocusEvent(void) = default;

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NT_API WindowMovedEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(WindowMovedEvent)
        WindowMovedEvent(int32 x, int32 y);

        int32 GetX(void) const;
        int32 GetY(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        int32 m_x, m_y;
    };

    class NT_API AppTickEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(AppTickEvent)
        AppTickEvent(void) = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NT_API AppUpdateEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(AppUpdateEvent)
        AppUpdateEvent(float32 deltaTime);

        float32 GetDeltaTime(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        float32 m_deltaTime;
    };

    class NT_API AppRenderEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(AppRenderEvent)
        AppRenderEvent(void) = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
} // namespace Nt

#endif // _CORE_APPLICATION_EVENT_H_
