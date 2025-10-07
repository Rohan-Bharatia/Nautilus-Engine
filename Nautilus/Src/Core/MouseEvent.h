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

#ifndef _CORE_MOUSE_EVENT_H_
    #define _CORE_MOUSE_EVENT_H_

#include "Event.h"

#include "Codes.h"

namespace Nt
{
    class NT_API MouseButtonEvent :
        public Event
    {
    public:
        MouseButton GetMouseButton(void) const;

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

    protected:
        MouseButtonEvent(uint32 button);

        uint32 m_button;
    };

    class NT_API MouseButtonPressedEvent :
        public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(uint32 button);

        String ToString(void) const override;

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class NT_API MouseButtonReleasedEvent :
        public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(uint32 button);

        String ToString(void) const override;

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class NT_API MouseMovedEvent :
        public Event
    {
    public:
        MouseMovedEvent(float32 x, float32 y);

        float32 GetX(void) const;
        float32 GetY(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float32 m_x, m_y;
    };

    class NT_API MouseScrolledEvent :
        public Event
    {
    public:
        MouseScrolledEvent(float32 xOffset, float32 yOffset);

        float32 GetXOffset(void) const;
        float32 GetYOffset(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float32 m_xOffset, m_yOffset;
    };
} // namespace Nt

#endif // _CORE_MOUSE_EVENT_H_
