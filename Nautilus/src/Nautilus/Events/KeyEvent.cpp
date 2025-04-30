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

#ifndef _NT_NAUTILUS_EVENTS_KEY_EVENT_CPP_
    #define _NT_NAUTILUS_EVENTS_KEY_EVENT_CPP_

#include "KeyEvent.h"

namespace Nt
{
    int KeyEvent::GetKeyCode() const
    {
        return m_keycode;
    }

    KeyEvent::KeyEvent(int keycode) :
        m_keycode(keycode)
    {}

    KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount) :
        KeyEvent(keycode), m_repeatCount(repeatCount)
    {}

    int KeyPressedEvent::GetRepeatCount() const
    {
        return m_repeatCount;
    }

    std::string KeyPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << GetKeyCode() << " (" << GetRepeatCount() << " repeats)";
        return ss.str();
    }

    KeyReleasedEvent::KeyReleasedEvent(int keycode) :
        KeyEvent(keycode)
    {}

    std::string KeyReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << GetKeyCode();
        return ss.str();
    }
} // namespace Nt

#endif // _NT_NAUTILUS_EVENTS_KEY_EVENT_CPP_
