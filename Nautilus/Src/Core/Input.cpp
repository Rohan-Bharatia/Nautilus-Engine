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

#ifndef _CORE_INPUT_CPP_
    #define _CORE_INPUT_CPP_

#include "Input.h"

namespace Nt
{
    const bool* Input::s_keyboardState = nullptr;
    int32 Input::s_keyboardStateLength = 0;
    float32 Input::s_mouseX            = 0.0f,
            Input::s_mouseY            = 0.0f;
    float32 Input::s_prevMouseX        = 0.0f,
            Input::s_prevMouseY        = 0.0f;
    uint32 Input::s_mouseState         = 0;
    SDL_Gamepad* Input::s_gamepad      = nullptr;

    Input::Input(void) :
        Layer("InputLayer")
    {}

    void Input::OnAttach(void)
    {
        s_keyboardState = SDL_GetKeyboardState(&s_keyboardStateLength);
        s_mouseState    = SDL_GetMouseState(&s_mouseX, &s_mouseY);
        s_prevMouseX    = s_mouseX;
        s_prevMouseY    = s_mouseY;

        int32 count;
        SDL_JoystickID* gamepads = SDL_GetGamepads(&count);
        if (gamepads != nullptr && count > 0)
            s_gamepad = SDL_OpenGamepad(gamepads[0]);
        else
            s_gamepad = nullptr;
    }

    void Input::OnUpdate(float32 deltaTime)
    {
        s_prevMouseX = s_mouseX;
        s_prevMouseY = s_mouseY;
        s_mouseState = SDL_GetMouseState(&s_mouseX, &s_mouseY);
        SDL_PumpEvents();
        s_keyboardState = SDL_GetKeyboardState(&s_keyboardStateLength);
    }

    void Input::OnDetach(void)
    {
        if (s_gamepad)
            SDL_CloseGamepad(s_gamepad);
    }

    bool Input::IsKeyPressed(Keycode key)
    {
        SDL_Keymod mods       = SDL_GetModState();
        SDL_Scancode scancode = SDL_GetScancodeFromKey((SDL_Keycode)key, &mods);
        if (scancode < 0 || scancode >= s_keyboardStateLength)
            return false;
        return s_keyboardState[scancode] != 0;
    }

    bool Input::IsKeyReleased(Keycode key)
    {
        return !IsKeyPressed(key);
    }

    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        return (s_mouseState & (1 << (((int32)button) - 1))) != 0;
    }

    bool Input::IsMouseButtonReleased(MouseButton button)
    {
        return !IsMouseButtonPressed(button);
    }

    float32 Input::GetMousePositionX(void)
    {
        return s_mouseX;
    }

    float32 Input::GetMousePositionY(void)
    {
        return s_mouseY;
    }

    bool Input::IsGamepadButtonPressed(GamepadButton button)
    {
        if (!s_gamepad)
            return false;
        return SDL_GetGamepadButton(s_gamepad, (SDL_GamepadButton)button) != 0;
    }

    bool Input::IsGamepadButtonReleased(GamepadButton button)
    {
        return !IsGamepadButtonPressed(button);
    }

    float32 Input::GetJoystickAxisPosition(int32 axis)
    {
        if (!s_gamepad)
            return 0.0f;
        auto value = SDL_GetGamepadAxis(s_gamepad, (SDL_GamepadAxis)axis);
        return value / 32767.0f; // Normalize to [-1.0, 1.0]
    }
} // namespace Nt

#endif // _CORE_INPUT_CPP_
