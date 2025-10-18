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

#ifndef _RENDERER_GRAPHICS_CONTEXT_H_
    #define _RENDERER_GRAPHICS_CONTEXT_H_

#include "Core/Window.h"

#define NT_HIGH_QUAILITY_PRESET BGFX_RESET_MSAA_X8 | BGFX_RESET_MAXANISOTROPY | BGFX_RESET_SRGB_BACKBUFFER | BGFX_RESET_HIDPI
#define NT_BALANCED_PRESET BGFX_RESET_MSAA_X4 | BGFX_RESET_MAXANISOTROPY | BGFX_RESET_SRGB_BACKBUFFER
#define NT_PERFORMANCE_PRESET BGFX_RESET_MSAA_X2
#define NT_DEBUG_PRESET BGFX_RESET_NONE

namespace Nt
{
    class NT_API GraphicsContext
    {
    public:
        NT_CLASS_DEFAULTS(GraphicsContext)
        GraphicsContext(Window* window, uint32 preset=NT_BALANCED_PRESET);
        ~GraphicsContext(void);

        void SwapBuffers(void) const;
        void SetVSync(bool enabled) const;

    private:
        std::vector<bgfx::RendererType::Enum> GetSupportedRenderers(void) const;

        Window* m_window;
        SDL_Window* m_native;
        uint32 m_flags;
    };
} // namespace Nt

#endif // _RENDERER_GRAPHICS_CONTEXT_H_
