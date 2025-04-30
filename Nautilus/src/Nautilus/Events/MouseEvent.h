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

#pragma once

#ifndef _NT_NAUTILUS_EVENTS_MOUSE_EVENT_H_
    #define _NT_NAUTILUS_EVENTS_MOUSE_EVENT_H_

#include "Event.h"

namespace Nt
{
    class NT_API MouseMovedEvent :
        public Event
    {
    public:
        MouseMovedEvent(const float mx, const float my);

        float GetX() const;
        float GetY() const;

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(MouseMoved)
        NT_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_mouseX, m_mouseY;
    };

    class NT_API MouseScrolledEvent :
        public Event
    {
    public:
        MouseScrolledEvent(const float ox, const float oy);

        float GetOffsetX() const;
        float GetOffsetY() const;

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(MouseScrolled)
        NT_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_offsetX, m_offsetY;
    };

    class NT_API MouseButtonEvent :
        public Event
    {
    public:
        int GetMouseButton() const;

        NT_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

    protected:
        MouseButtonEvent(int button);

        int m_button;
    };

    class NT_API MouseButtonPressedEvent :
        public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button, int repeatCount);

        int GetRepeatCount() const;

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(MouseButtonPressed)

    private:
        int m_repeatCount;
    };

    class NT_API MouseButtonReleasedEvent :
        public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button);

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(MouseButtonReleased)
    };
} // namespace Nt

#endif // _NT_NAUTILUS_EVENTS_MOUSE_EVENT_H_
