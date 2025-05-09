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

#ifndef _NT_NAUTILUS_EVENTS_EVENT_H_
    #define _NT_NAUTILUS_EVENTS_EVENT_H_

#include "PCH.h"

#define BIT(x) (1 << x)

#define NT_EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                                  virtual EventType GetEventType() const override { return GetStaticType(); } \
                                  virtual const char* GetName() const override { return #type; }

#define NT_EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


namespace Nt
{
    enum class EventType
    {
        None = 0,

        // Window events
		WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        // Application events
		ApplicationTick,
        ApplicationUpdate,
        ApplicationRender,

        // Keyboard events
		KeyPressed,
        KeyReleased,
        KeyTyped,

        // Mouse events
		MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled,
    };

    enum EventCategory
	{
		None                     = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

    class EventDispatcher;

    class NT_API Event
    {
        friend class EventDispatcher;

    public:
        Event();

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const;
        bool IsHandled() const;

        bool IsInCategory(EventCategory category) const;

    protected:
        bool m_handled;
    };

    class NT_API EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event);

        // Must be written here to avoid template instantiations
        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.m_handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };

    std::ostream& operator<<(std::ostream& os, const Event& e);
} // namespace Nt

#endif // _NT_NAUTILUS_EVENTS_EVENT_H_
