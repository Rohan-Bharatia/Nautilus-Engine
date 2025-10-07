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

#ifndef _CORE_KEY_EVENT_H_
    #define _CORE_KEY_EVENT_H_

#include "Event.h"

#include "Codes.h"

namespace Nt
{
    class NT_API KeyEvent :
        public Event
    {
    public:
        Keycode GetKeyCode(void) const;

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(uint32 keyCode);

        uint32 m_keyCode;
    };

    class NT_API KeyPressedEvent :
        public KeyEvent
    {
    public:
        KeyPressedEvent(uint32 keyCode, bool repeat=false);

        bool IsRepeat(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool m_repeat;
    };

    class NT_API KeyReleasedEvent :
        public KeyEvent
    {
    public:
        KeyReleasedEvent(uint32 keyCode);

        String ToString(void) const override;

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class NT_API KeyTypedEvent :
        public KeyEvent
    {
    public:
        KeyTypedEvent(uint32 keyCode);

        String ToString(void) const override;

        EVENT_CLASS_TYPE(KeyTyped)
    };
} // namespace Nt

#endif // _CORE_KEY_EVENT_H_
