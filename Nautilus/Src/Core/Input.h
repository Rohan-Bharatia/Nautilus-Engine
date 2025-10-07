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

#ifndef _CORE_INPUT_H_
    #define _CORE_INPUT_H_

#include "Layer.h"

#include "Codes.h"

namespace Nt
{
    class NT_API Input :
        public Layer
    {
    public:
        Input(void);

        void OnAttach(void) override;
        void OnUpdate(float32 deltaTime) override;
        void OnDetach(void) override;

        static bool IsKeyPressed(Keycode key);
        static bool IsKeyReleased(Keycode key);

        static bool IsMouseButtonPressed(MouseButton button);
        static bool IsMouseButtonReleased(MouseButton button);

        static float32 GetMousePositionX(void);
        static float32 GetMousePositionY(void);

        static bool IsGamepadButtonPressed(GamepadButton button);
        static bool IsGamepadButtonReleased(GamepadButton button);
        static float32 GetJoystickAxisPosition(int32 axis);

    private:
        static const bool* s_keyboardState;
        static int32 s_keyboardStateLength;
        static float32 s_mouseX, s_mouseY;
        static float32 s_prevMouseX, s_prevMouseY;
        static uint32 s_mouseState;
        static SDL_Gamepad* s_gamepad;
    };

    using InputLayer = Input;
} // namespace Nt

#endif // _CORE_INPUT_H_
