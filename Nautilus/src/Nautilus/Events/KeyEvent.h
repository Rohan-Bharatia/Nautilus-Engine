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

#ifndef _NT_NAUTILUS_EVENTS_KEY_EVENT_H_
    #define _NT_NAUTILUS_EVENTS_KEY_EVENT_H_

#include "Event.h"

namespace Nt
{
    class NT_API KeyEvent :
        public Event
    {
    public:
        int GetKeyCode() const;

        NT_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keycode);

        int m_keycode;
    };

    class NT_API KeyPressedEvent :
        public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount);

        int GetRepeatCount() const;

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount;
    };

    class NT_API KeyReleasedEvent :
        public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode);

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(KeyReleased)
    };

    class NT_API KeyTypedEvent :
        public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode);

        int GetRepeatCount() const;

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(KeyTyped)
    };
} // namespace Nt

#endif // _NT_NAUTILUS_EVENTS_KEY_EVENT_H_
