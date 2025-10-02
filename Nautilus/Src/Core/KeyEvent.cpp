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

#ifndef _CORE_KEY_EVENT_CPP_
    #define _CORE_KEY_EVENT_CPP_

#include "KeyEvent.h"

namespace Nt
{
    uint32 KeyEvent::GetKeyCode(void) const
    {
        return m_keyCode;
    }

    KeyEvent::KeyEvent(uint32 keyCode) :
        m_keyCode(keyCode)
    {}

    KeyPressedEvent::KeyPressedEvent(uint32 keyCode, bool repeat) :
        KeyEvent(keyCode), m_repeat(repeat)
    {}

    bool KeyPressedEvent::IsRepeat(void) const
    {
        return m_repeat;
    }

    String KeyPressedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: (" << m_keyCode << ", " << m_repeat << ")";
        return String(ss.str());
    }

    KeyReleasedEvent::KeyReleasedEvent(uint32 keyCode) :
        KeyEvent(keyCode)
    {}

    String KeyReleasedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: (" << m_keyCode << ")";
        return String(ss.str());
    }

    KeyTypedEvent::KeyTypedEvent(uint32 keyCode) :
        KeyEvent(keyCode)
    {}

    String KeyTypedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: (" << m_keyCode << ")";
        return String(ss.str());
    }
} // namespace Nt

#endif // _CORE_KEY_EVENT_CPP_
