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

#ifndef _NT_NAUTILUS_EVENTS_MOUSE_EVENT_CPP_
    #define _NT_NAUTILUS_EVENTS_MOUSE_EVENT_CPP_

#include "MouseEvent.h"

#include <sstream>

namespace Nt
{
    MouseMovedEvent::MouseMovedEvent(const float mx, const float my) :
        m_mouseX(mx), m_mouseY(my)
    {}

    float MouseMovedEvent::GetX() const
    {
        return m_mouseX;
    }

    float MouseMovedEvent::GetY() const
    {
        return m_mouseY;
    }

    std::string MouseMovedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
        return ss.str();
    }

    MouseScrolledEvent::MouseScrolledEvent(const float ox, const float oy) :
        m_offsetX(ox), m_offsetY(oy)
    {}

    float MouseScrolledEvent::GetOffsetX() const
    {
        return m_offsetX;
    }

    float MouseScrolledEvent::GetOffsetY() const
    {
        return m_offsetY;
    }

    std::string MouseScrolledEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetOffsetX() << ", " << GetOffsetY();
        return ss.str();
    }

    int MouseButtonEvent::GetMouseButton() const
    {
        return m_button;
    }

    MouseButtonEvent::MouseButtonEvent(int button) :
        m_button(button)
    {}

    MouseButtonPressedEvent::MouseButtonPressedEvent(int button, int repeatCount) :
        MouseButtonEvent(button), m_repeatCount(repeatCount)
    {}

    int MouseButtonPressedEvent::GetRepeatCount() const
    {
        return m_repeatCount;
    }

    std::string MouseButtonPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << GetMouseButton() << " (" << GetRepeatCount() << " repeats)";
        return ss.str();
    }

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) :
        MouseButtonEvent(button)
    {}

    std::string MouseButtonReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << GetMouseButton();
        return ss.str();
    }
} // namespace Nt

#endif // _NT_NAUTILUS_EVENTS_MOUSE_EVENT_CPP_
