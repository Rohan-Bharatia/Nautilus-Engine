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

#ifndef _RENDERER_BUFFER_CPP_
    #define _RENDERER_BUFFER_CPP_

#include "Buffer.h"

namespace Nt
{
    uint32 ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:   return 4;
            case ShaderDataType::Float2:  return 4 * 2;
            case ShaderDataType::Float3:  return 4 * 3;
            case ShaderDataType::Float4:  return 4 * 4;
            case ShaderDataType::Mat3:    return 4 * 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4 * 4;
            case ShaderDataType::Int:     return 4;
            case ShaderDataType::Int2:    return 4 * 2;
            case ShaderDataType::Int3:    return 4 * 3;
            case ShaderDataType::Int4:    return 4 * 4;
            case ShaderDataType::Boolean: return 1;
            default:                      return 0;
        }
    }

    BufferElement::BufferElement(ShaderDataType type, const String& name, bool normalized) :
        name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
    {}

    uint8 BufferElement::GetComponentCount(void) const
    {
        switch (type)
        {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3;
            case ShaderDataType::Mat4:    return 4;
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Boolean: return 1;
            default:                      return 0;
        }
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) :
        m_elements(elements), m_stride(0)
    {
        uint32 offset = 0;
        for (auto& element : m_elements)
        {
            element.offset = offset;
            offset        += element.size;
            m_stride      += element.size;
        }
    }

    uint32 BufferLayout::GetStride(void) const
    {
        return m_stride;
    }

    const std::vector<BufferElement>& BufferLayout::GetElements(void) const
    {
        return m_elements;
    }

    std::vector<BufferElement>::iterator BufferLayout::begin(void)
    {
        return m_elements.begin();
    }

    std::vector<BufferElement>::iterator BufferLayout::end(void)
    {
        return m_elements.end();
    }

    std::vector<BufferElement>::const_iterator BufferLayout::begin(void) const
    {
        return m_elements.begin();
    }

    std::vector<BufferElement>::const_iterator BufferLayout::end(void) const
    {
        return m_elements.end();
    }

    VertexBuffer::VertexBuffer(uint32 size)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(float32* vertices, uint32 size)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer(void)
    {
        glDeleteBuffers(1, &m_id);
    }

    void VertexBuffer::Bind(void)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBuffer::Unbind(void)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const void* data, uint32 size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    const BufferLayout& VertexBuffer::GetLayout(void) const
    {
        return m_layout;
    }

    void VertexBuffer::SetLayout(const BufferLayout& layout)
    {
        m_layout = layout;
    }

    uint32 VertexBuffer::GetRenderId(void) const
    {
        return m_id;
    }

    IndexBuffer::IndexBuffer(uint32* indices, uint32 count) :
        m_count(count)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer(void)
    {
        glDeleteBuffers(1, &m_id);
    }

    void IndexBuffer::Bind(void)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void IndexBuffer::Unbind(void)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32 IndexBuffer::GetCount(void) const
    {
        return m_count;
    }

    uint32 IndexBuffer::GetRenderId(void) const
    {
        return m_id;
    }
} // namespace Nt

#endif // _RENDERER_BUFFER_CPP_
