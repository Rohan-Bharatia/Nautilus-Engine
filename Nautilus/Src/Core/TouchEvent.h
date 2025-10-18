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

#ifndef _CORE_TOUCH_EVENT_H_
    #define _CORE_TOUCH_EVENT_H_

#include "Event.h"

namespace Nt
{
    class NT_API TouchPressedEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(TouchPressedEvent)
        TouchPressedEvent(void) = default;

        EVENT_CLASS_TYPE(TouchPressed)
        EVENT_CLASS_CATEGORY(EventCategoryTouch | EventCategoryInput)
    };

    class NT_API TouchReleasedEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(TouchReleasedEvent)
        TouchReleasedEvent(void) = default;

        EVENT_CLASS_TYPE(TouchReleased)
        EVENT_CLASS_CATEGORY(EventCategoryTouch | EventCategoryInput)
    };

    class NT_API TouchMovedEvent :
        public Event
    {
    public:
        NT_CLASS_DEFAULTS(TouchMovedEvent)
        TouchMovedEvent(float32 x, float32 y);

        float32 GetX(void) const;
        float32 GetY(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(TouchMoved)
        EVENT_CLASS_CATEGORY(EventCategoryTouch | EventCategoryInput)

    private:
        float32 m_x;
        float32 m_y;
    };
} // namespace Nt

#endif // _CORE_TOUCH_EVENT_H_
