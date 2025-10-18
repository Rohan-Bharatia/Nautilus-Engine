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

#ifndef _CORE_EVENT_H_
    #define _CORE_EVENT_H_

#include "String.h"

namespace Nt
{
    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled,
        GamepadButtonPressed,
        GamepadButtonReleased,
        JoystickAxisMoved,
        TouchPressed,
        TouchReleased,
        TouchMoved,
        TouchScrolled,
    };

    enum EventCategory
    {
        None                     = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),
        EventCategoryMouseButton = BIT(4),
        EventCategoryGamepad     = BIT(5),
        EventCategoryJoystick    = BIT(6),
        EventCategoryTouch       = BIT(7),
    };

    class NT_API Event
    {
    public:
        virtual ~Event(void) = default;

        virtual EventType GetEventType(void) const = 0;
        virtual String GetName(void) const         = 0;
        virtual int GetCategoryFlags(void) const   = 0;
        virtual String ToString(void) const;

        bool IsHandled(void) const;
        void SetHandled(bool handled);

    private:
        bool m_handled = false;
    };

    class NT_API EventDispatcher
    {
    public:
        EventDispatcher(Event& event);

        template <typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.SetHandled(func(NT_STATIC_CAST(T&, m_event)));
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };

    std::ostream& operator<<(std::ostream& os, const Event& e);
} // namespace Nt

#define EVENT_CLASS_TYPE(type) static ::Nt::EventType GetStaticType(void) { return ::Nt::EventType::type; }          \
                               virtual ::Nt::EventType GetEventType(void) const override { return GetStaticType(); } \
                               virtual String GetName(void) const override { return String(#type); }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags(void) const override { return category; }

#endif // _CORE_EVENT_H_
