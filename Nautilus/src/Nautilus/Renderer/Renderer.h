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

#pragma once

#ifndef _NT_NAUTILUS_RENDERER_RENDERER_H_
    #define _NT_NAUTILUS_RENDERER_RENDERER_H_

#include "PCH.h"

namespace Nt
{
    enum class RendererAPI
    {
        None   = 0,
        OpenGL = 1,
        // TODO: Add Vulkan, DirectX, & Metal support
    };

    class Renderer
    {
    public:
        static RendererAPI GetAPI();

    private:
        static RendererAPI s_API;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDERER_H_
