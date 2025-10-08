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
    GraphicsContext::GraphicsContext(Window* window) :
        m_window(window), m_native((SDL_Window*)window->GetNativeWindow())
    {
        SDL_PropertiesID propsId = SDL_GetWindowProperties(m_native);

        bgfx::PlatformData pd{};
    #if defined(NT_PLATFORM_WINDOWS)
        pd.nwh          = (HWND)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
        pd.ndt          = nullptr;
        pd.type         = bgfx::NativeWindowHandleType::Default;
    #elif defined(NT_PLATFORM_MACOS)
        pd.nwh          = (__bridge NSWindow*)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, nullptr);
        pd.ndt          = nullptr;
        pd.type         = bgfx::NativeWindowHandleType::Default;
    #elif defined(NT_PLATFORM_FAMILY_UNIX)
        if (SDL_strcmp( SDL_GetCurrentVideoDriver(), "wayland" ) == 0)
        {
            pd.nwh      = (struct wl_surface*)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
            pd.ndt      = (struct wl_display*)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
            pd.type     = bgfx::NativeWindowHandleType::Wayland;
        }
        else
        {
            pd.nwh      = (::Window*)SDL_GetNumberProperty(propsId, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, (Sint64)0);
            pd.ndt      = (Display*)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr);
            pd.type     = bgfx::NativeWindowHandleType::Default;
        }
    #elif defined(NT_PLATFORM_IOS)
        pd.nwh          = (__bridge UIWindow*)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_UIKIT_WINDOW_POINTER, nullptr);
        pd.ndt          = nullptr;
        pd.type         = bgfx::NativeWindowHandleType::Default;
    #elif defined(NT_PLATFORM_ANDROID)
        pd.nwh          = (ANativeWindow*)SDL_GetPointerProperty(propsId, SDL_PROP_WINDOW_ANDROID_WINDOW_POINTER, nullptr);
        pd.ndt          = nullptr;
        pd.type         = bgfx::NativeWindowHandleType::Default;
    #else
        pd.nwh          = nullptr;
        pd.ndt          = nullptr;
        pd.type         = bgfx::NativeWindowHandleType::Default;
    #endif
        pd.context      = nullptr;
        pd.backBuffer   = nullptr;
        pd.backBufferDS = nullptr;

        bgfx::Init init;
        init.type              = bgfx::RendererType::Count;
        init.vendorId          = BGFX_PCI_ID_NONE;
        init.platformData      = pd;
        init.resolution.width  = window->GetWidth();
        init.resolution.height = window->GetHeight();
        init.resolution.reset  = window->IsVSync() ? BGFX_RESET_VSYNC : BGFX_RESET_NONE;

        bool initialized = false;
        for (auto backend : GetSupportedRenderers())
        {
            init.type = backend;
            if (bgfx::init(init))
            {
                initialized = true;
                break;
            }
            else
                NT_CORE_WARN("Failed to initialize bgfx with renderer %d", backend);
        }

        if (!initialized)
        {
            NT_CORE_ERROR("Failed to initialize bgfx!");
            return;
        }

        bgfx::setDebug(BGFX_DEBUG_TEXT);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
    }

    GraphicsContext::~GraphicsContext(void)
    {
        bgfx::shutdown();
    }

    void GraphicsContext::SwapBuffers(void) const
    {
        bgfx::dbgTextClear();
        bgfx::frame();
    }

    void GraphicsContext::SetVSync(bool enabled) const
    {
        bgfx::reset(m_window->GetWidth(), m_window->GetHeight(), enabled ? BGFX_RESET_VSYNC : BGFX_RESET_NONE);
    }

    std::vector<bgfx::RendererType::Enum> GraphicsContext::GetSupportedRenderers(void) const
    {
        std::vector<bgfx::RendererType::Enum> result;

    #if defined(NT_PLATFORM_FAMILY_MICROSOFT)
        result.push_back(bgfx::RendererType::Direct3D12);
        result.push_back(bgfx::RendererType::Direct3D11);
        result.push_back(bgfx::RendererType::Vulkan);
        result.push_back(bgfx::RendererType::OpenGL);
        result.push_back(bgfx::RendererType::OpenGLES);
    #elif defined(NT_PLATFORM_FAMILY_APPLE)
        result.push_back(bgfx::RendererType::Metal);
        result.push_back(bgfx::RendererType::Vulkan);
        result.push_back(bgfx::RendererType::OpenGL);
        result.push_back(bgfx::RendererType::OpenGLES);
    #elif defined(NT_PLATFORM_FAMILY_UNIX) || defined(NT_PLATFORM_FAMILY_ANDROID)
        result.push_back(bgfx::RendererType::Vulkan);
        result.push_back(bgfx::RendererType::OpenGL);
        result.push_back(bgfx::RendererType::OpenGLES);
    #elif defined(NT_PLATFORM_FAMILY_WASM)
        result.push_back(bgfx::RendererType::OpenGLES);
    #else // (NOT) defined(NT_PLATFORM_FAMILY_MICROSOFT), defined(NT_PLATFORM_FAMILY_APPLE), defined(NT_PLATFORM_FAMILY_UNIX), defined(NT_PLATFORM_FAMILY_ANDROID), defined(NT_PLATFORM_FAMILY_WASM)
        result.push_back(bgfx::RendererType::OpenGL);
        result.push_back(bgfx::RendererType::OpenGLES);
    #endif // defined(NT_PLATFORM_FAMILY_MICROSOFT), defined(NT_PLATFORM_FAMILY_APPLE), defined(NT_PLATFORM_FAMILY_UNIX), defined(NT_PLATFORM_FAMILY_ANDROID), defined(NT_PLATFORM_FAMILY_WASM)

        return result;
    }
} // namespace Nt

#endif // _RENDERER_GRAPHICS_CONTEXT_CPP_
