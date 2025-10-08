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

#ifndef _CORE_CONTROLLER_EVENT_H_
    #define _CORE_CONTROLLER_EVENT_H_

#include "Event.h"

#include "Codes.h"

namespace Nt
{
    class NT_API GamepadButtonEvent :
        public Event
    {
    public:
        GamepadButton GetGamepadButton(void) const;

        EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryInput)

    protected:
        GamepadButtonEvent(uint32 button);

        uint32 m_button;
    };

    class NT_API GamepadButtonPressedEvent :
        public GamepadButtonEvent
    {
    public:
        GamepadButtonPressedEvent(uint32 button);

        String ToString(void) const override;

        EVENT_CLASS_TYPE(GamepadButtonPressed)
    };

    class NT_API GamepadButtonReleasedEvent :
        public GamepadButtonEvent
    {
    public:
        GamepadButtonReleasedEvent(uint32 button);

        String ToString(void) const override;

        EVENT_CLASS_TYPE(GamepadButtonReleased)
    };

    class NT_API JoystickAxisMovedEvent :
        public Event
    {
    public:
        JoystickAxisMovedEvent(int32 axis, float32 value);

        JoystickAxis GetAxis(void) const;
        float32 GetValue(void) const;

        String ToString(void) const override;

        EVENT_CLASS_TYPE(JoystickAxisMoved)
        EVENT_CLASS_CATEGORY(EventCategoryJoystick | EventCategoryInput)

    protected:
        int32 m_axis;
        float32 m_value;
    };
} // namespace Nt

#endif // _CORE_CONTROLLER_EVENT_H_
