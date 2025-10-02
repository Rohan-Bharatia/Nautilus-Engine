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

#ifndef _CORE_APPLICATION_EVENT_CPP_
    #define _CORE_APPLICATION_EVENT_CPP_

#include "ApplicationEvent.h"

namespace Nt
{
    WindowResizeEvent::WindowResizeEvent(uint32 width, uint32 height) :
        m_width(width), m_height(height)
    {}

    uint32 WindowResizeEvent::GetWidth(void) const
    {
        return m_width;
    }

    uint32 WindowResizeEvent::GetHeight(void) const
    {
        return m_height;
    }

    String WindowResizeEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: (" << m_width << ", " << m_height << ")";
        return String(ss.str());
    }

    WindowMovedEvent::WindowMovedEvent(int32 x, int32 y) :
        m_x(x), m_y(y)
    {}

    int32 WindowMovedEvent::GetX(void) const
    {
        return m_x;
    }

    int32 WindowMovedEvent::GetY(void) const
    {
        return m_y;
    }

    String WindowMovedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "WindowMovedEvent: (" << m_x << ", " << m_y << ")";
        return String(ss.str());
    }

    AppUpdateEvent::AppUpdateEvent(float32 deltaTime) :
        m_deltaTime(deltaTime)
    {}

    float32 AppUpdateEvent::GetDeltaTime(void) const
    {
        return m_deltaTime;
    }

    String AppUpdateEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "AppUpdateEvent: (" << m_deltaTime << ")";
        return String(ss.str());
    }
} // namespace Nt

#endif // _CORE_APPLICATION_EVENT_CPP_
