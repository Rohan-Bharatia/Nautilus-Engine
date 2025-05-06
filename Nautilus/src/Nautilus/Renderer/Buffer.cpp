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

#ifndef _NT_NAUTILUS_RENDERER_BUFFER_CPP_
    #define _NT_NAUTILUS_RENDERER_BUFFER_CPP_

#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Nt
{
    VertexBuffer::~VertexBuffer()
    {}

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            default:
                NT_ASSERT(false, "Unknown renderer API!");
                return nullptr;
        }

        NT_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

    IndexBuffer::~IndexBuffer()
    {}

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, count);
            default:
                NT_ASSERT(false, "Unknown renderer API!");
                return nullptr;
        }

        NT_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_BUFFER_CPP_
