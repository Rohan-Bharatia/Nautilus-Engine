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

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Nt
{
    uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                NT_ASSERT(false, "Unknown shader data type!");
                return 0;
        }

        NT_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    BufferElement::BufferElement(ShaderDataType type, std::string name, bool normalized)
        : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
    {}

    uint32_t BufferElement::GetComponentCount() const
    {
        switch (type)
        {
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                NT_ASSERT(false, "Unknown shader data type!");
                return 0;
        }

        NT_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
        m_elements(elements), m_stride(0)
    {
        Calculate();
    }

    const std::vector<BufferElement>& BufferLayout::GetElements() const
    {
        return m_elements;
    }

    uint32_t BufferLayout::GetStride() const
    {
        return m_stride;
    }

    BufferLayout::Iterator BufferLayout::begin()
    {
        return m_elements.begin();
    }

    BufferLayout::Iterator BufferLayout::end()
    {
        return m_elements.end();
    }

    void BufferLayout::Calculate()
    {
        uint32_t offset = 0;
        m_stride        = 0;
        for (auto& elt : m_elements)
        {
            elt.offset = offset;
            offset    += elt.size;
            m_stride  += elt.size;
        }
    }

    VertexBuffer::~VertexBuffer()
    {}

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::OpenGL:
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
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::OpenGL:
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
