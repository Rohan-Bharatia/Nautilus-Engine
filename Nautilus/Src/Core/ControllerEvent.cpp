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

#ifndef _CORE_CONTROLLER_EVENT_CPP_
    #define _CORE_CONTROLLER_EVENT_CPP_

#include "ControllerEvent.h"

namespace Nt
{
    uint32 GamepadButtonEvent::GetGamepadButton(void) const
    {
        return m_button;
    }

    GamepadButtonEvent::GamepadButtonEvent(uint32 button) :
        m_button(button)
    {}

    GamepadButtonPressedEvent::GamepadButtonPressedEvent(uint32 button) :
        GamepadButtonEvent(button)
    {}

    String GamepadButtonPressedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "GamepadButtonPressedEvent: (" << m_button << ")";
        return String(ss.str());
    }

    GamepadButtonReleasedEvent::GamepadButtonReleasedEvent(uint32 button) :
        GamepadButtonEvent(button)
    {}

    String GamepadButtonReleasedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "GamepadButtonReleasedEvent: (" << m_button << ")";
        return String(ss.str());
    }

    JoystickAxisMovedEvent::JoystickAxisMovedEvent(int32 axis, float32 value) :
        m_axis(axis), m_value(value)
    {}

    int32 JoystickAxisMovedEvent::GetAxis(void) const
    {
        return m_axis;
    }

    float32 JoystickAxisMovedEvent::GetValue(void) const
    {
        return m_value;
    }

    String JoystickAxisMovedEvent::ToString(void) const
    {
        std::stringstream ss;
        ss << "JoystickAxisMovedEvent: (" << m_axis << ", " << m_value << ")";
        return String(ss.str());
    }
} // namespace Nt

#endif // _CORE_CONTROLLER_EVENT_CPP_
