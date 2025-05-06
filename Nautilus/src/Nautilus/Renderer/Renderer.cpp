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

#ifndef _NT_NAUTILUS_RENDERER_RENDERER_CPP_
    #define _NT_NAUTILUS_RENDERER_RENDERER_CPP_

#include "Renderer.h"

namespace Nt
{
    RendererAPI Renderer::s_API = RendererAPI::OpenGL;

    RendererAPI Renderer::GetAPI()
    {
        return s_API;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDERER_CPP_
