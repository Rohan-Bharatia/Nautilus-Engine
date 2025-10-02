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

#ifndef _CORE_MOUSE_EVENT_CPP_
    #define _CORE_MOUSE_EVENT_CPP_

#include "MouseEvent.h"

namespace Nt
{
    uint32 MouseButtonEvent::GetMouseButton(void) const
    {
        return m_button;
    }

    MouseButtonEvent::MouseButtonEvent(uint32 button) :
        m_button(button)
    {}

    MouseButtonPressedEvent::MouseButtonPressedEvent(uint32 button) :
        MouseButtonEvent(button)
    {}

    String MouseButtonPressedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: (" << m_button << ")";
        return String(ss.str());
    }

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(uint32 button) :
        MouseButtonEvent(button)
    {}

    String MouseButtonReleasedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: (" << m_button << ")";
        return String(ss.str());
    }

    MouseMovedEvent::MouseMovedEvent(float32 x, float32 y) :
        m_x(x), m_y(y)
    {}

    float32 MouseMovedEvent::GetX(void) const
    {
        return m_x;
    }

    float32 MouseMovedEvent::GetY(void) const
    {
        return m_y;
    }

    String MouseMovedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: (" << m_x << ", " << m_y << ")";
        return String(ss.str());
    }

    MouseScrolledEvent::MouseScrolledEvent(float32 xOffset, float32 yOffset) :
        m_xOffset(xOffset), m_yOffset(yOffset)
    {}

    float32 MouseScrolledEvent::GetXOffset(void) const
    {
        return m_xOffset;
    }

    float32 MouseScrolledEvent::GetYOffset(void) const
    {
        return m_yOffset;
    }

    String MouseScrolledEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: (" << m_xOffset << ", " << m_yOffset << ")";
        return String(ss.str());
    }
} // namespace Nt

#endif // _CORE_MOUSE_EVENT_CPP_
