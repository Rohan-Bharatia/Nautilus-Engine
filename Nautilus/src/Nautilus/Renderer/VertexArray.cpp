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

#ifndef _NT_NAUTILUS_RENDERER_VERTEX_ARRAY_CPP_
    #define _NT_NAUTILUS_RENDERER_VERTEX_ARRAY_CPP_

#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nt
{
    VertexArray::~VertexArray()
    {}

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
            default:
                NT_ASSERT(false, "Unknown renderer API!");
                return nullptr;
        }

        NT_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_VERTEX_ARRAY_CPP_
