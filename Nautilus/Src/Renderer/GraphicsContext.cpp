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

#ifndef _RENDERER_GRAPHICS_CONTEXT_CPP_
    #define _RENDERER_GRAPHICS_CONTEXT_CPP_

#include "GraphicsContext.h"

namespace Nt
{
    GraphicsContext::GraphicsContext(Window* window, uint32 preset) :
        m_native((SDL_Window*)window->GetNativeWindow())
    {
        m_context = SDL_GL_CreateContext(m_native);

    #ifdef NT_DEVICE_DESKTOP
        if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
        {
            NT_CORE_ERROR("Failed to initialize OpenGL (GLAD)!");
            return;
        }
    #else // (NOT) NT_DEVICE_DESKTOP
        if (!gladLoadGLES((GLADloadfunc)SDL_GL_GetProcAddress))
        {
            NT_CORE_ERROR("Failed to initialize OpenGL ES (GLAD)!");
            return;
        }
    #endif // NT_DEVICE_DESKTOP

        SDL_GL_MakeCurrent(m_native, m_context);
        SDL_GL_SetSwapInterval(1);

        NT_CORE_INFO("OpenGL Info:\n  Vendor: %s\n  Renderer: %s\n  Version: %s", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
    }

    GraphicsContext::~GraphicsContext(void)
    {
        SDL_GL_DestroyContext(m_context);
    }

    void GraphicsContext::SwapBuffers(void) const
    {
        SDL_GL_SwapWindow(m_native);
    }

    void GraphicsContext::SetVSync(bool enabled) const
    {
        SDL_GL_SetSwapInterval(enabled ? 1 : 0);
    }

    void* GraphicsContext::GetNativeContext(void) const
    {
        return (void*)&m_context;
    }
} // namespace Nt

#endif // _RENDERER_GRAPHICS_CONTEXT_CPP_
