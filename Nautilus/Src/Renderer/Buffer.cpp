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

    bgfx::VertexLayout BufferLayout::GetLayout(void) const
    {
        bgfx::VertexLayout layout;
        layout.begin();

        for (auto& element : m_elements)
        {
            switch (element.type)
            {
                case ShaderDataType::Float:
                    layout.add(bgfx::Attrib::Position, 1, bgfx::AttribType::Float);
                    break;
                case ShaderDataType::Float2:
                    layout.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float);
                    break;
                case ShaderDataType::Float3:
                    layout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
                    break;
                case ShaderDataType::Float4:
                    layout.add(bgfx::Attrib::Position, 4, bgfx::AttribType::Float);
                    break;
                case ShaderDataType::Mat3:
                    layout.add(bgfx::Attrib::Position, 3 * 3, bgfx::AttribType::Float);
                    break;
                case ShaderDataType::Mat4:
                    layout.add(bgfx::Attrib::Position, 4 * 4, bgfx::AttribType::Float);
                    break;
                case ShaderDataType::Int:
                    layout.add(bgfx::Attrib::Position, 1, bgfx::AttribType::Int16);
                    break;
                case ShaderDataType::Int2:
                    layout.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Int16);
                    break;
                case ShaderDataType::Int3:
                    layout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Int16);
                    break;
                case ShaderDataType::Int4:
                    layout.add(bgfx::Attrib::Position, 4, bgfx::AttribType::Int16);
                    break;
                case ShaderDataType::Boolean:
                    layout.add(bgfx::Attrib::Position, 1, bgfx::AttribType::Uint8);
                    break;
                default:
                    break;
            }
        }

        layout.end();
        return layout;
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

    VertexBuffer::VertexBuffer(BufferLayout layout, uint32 size) :
        m_layout(layout)
    {
        m_vbh = bgfx::createDynamicVertexBuffer(size, layout.GetLayout(),  BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_ALLOW_RESIZE);
    }

    VertexBuffer::VertexBuffer(BufferLayout layout, float32* vertices, uint32 size) :
        m_layout(layout)
    {
        const bgfx::Memory* mem = bgfx::copy(vertices, size);
        m_vbh = bgfx::createDynamicVertexBuffer(mem, layout.GetLayout(), BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_ALLOW_RESIZE);
    }

    VertexBuffer::~VertexBuffer(void)
    {
        if (bgfx::isValid(m_vbh))
            bgfx::destroy(m_vbh);
    }

    void VertexBuffer::Bind(void) const
    {
        bgfx::setVertexBuffer(0, m_vbh);
    }

    void VertexBuffer::Unbind(void) const
    {
        bgfx::setVertexBuffer(0, nullptr);
    }

    void VertexBuffer::SetData(const void* data, uint32 size)
    {
        const bgfx::Memory* mem = bgfx::copy(data, size);
        bgfx::update(m_vbh, 0, mem);
    }

    const BufferLayout& VertexBuffer::GetLayout(void) const
    {
        return m_layout;
    }

    void VertexBuffer::SetLayout(const BufferLayout& layout)
    {
        m_layout = layout;
    }

    bgfx::DynamicVertexBufferHandle VertexBuffer::GetHandle(void) const
    {
        return m_vbh;
    }

    IndexBuffer::IndexBuffer(uint32* indices, uint32 count) :
        m_count(count)
    {
        const bgfx::Memory* mem = bgfx::copy(indices, count * sizeof(uint32));
        m_ibh                   = bgfx::createDynamicIndexBuffer(mem, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_ALLOW_RESIZE);
    }

    IndexBuffer::~IndexBuffer(void)
    {
        if (bgfx::isValid(m_ibh))
            bgfx::destroy(m_ibh);
    }

    void IndexBuffer::Bind(void) const
    {
        bgfx::setIndexBuffer(m_ibh);
    }

    void IndexBuffer::Unbind(void) const
    {
        bgfx::setIndexBuffer(nullptr);
    }

    uint32 IndexBuffer::GetCount(void) const
    {
        return m_count;
    }

    bgfx::DynamicIndexBufferHandle IndexBuffer::GetHandle(void) const
    {
        return m_ibh;
    }
} // namespace Nt

#endif // _RENDERER_BUFFER_CPP_
