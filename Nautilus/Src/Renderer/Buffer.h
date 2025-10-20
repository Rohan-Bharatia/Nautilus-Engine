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

#ifndef _RENDERER_BUFFER_H_
    #define _RENDERER_BUFFER_H_

#include "PCH.h"

namespace Nt
{
    enum class NT_API ShaderDataType
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Boolean,
    };

    NT_API uint32 ShaderDataTypeSize(ShaderDataType type);

    struct NT_API BufferElement
    {
        String name;
        ShaderDataType type;
        uint32 size;
        uint32 offset;
        bool normalized;

        NT_STRUCT_DEFAULTS(BufferElement)
        BufferElement(void) = default;
        BufferElement(ShaderDataType type, const String& name, bool normalized=false);

        uint8 GetComponentCount(void) const;
    };

    class NT_API BufferLayout
    {
    public:
        NT_CLASS_DEFAULTS(BufferLayout)
        BufferLayout(void) = default;
        BufferLayout(std::initializer_list<BufferElement> elements);

        uint32 GetStride(void) const;
        const std::vector<BufferElement>& GetElements(void) const;

        std::vector<BufferElement>::iterator begin(void);
        std::vector<BufferElement>::iterator end(void);
        std::vector<BufferElement>::const_iterator begin(void) const;
        std::vector<BufferElement>::const_iterator end(void) const;

    private:
        std::vector<BufferElement> m_elements;
        uint32 m_stride;
    };

    class NT_API VertexBuffer
    {
    public:
        NT_CLASS_DEFAULTS(VertexBuffer)
        VertexBuffer(void) = default;
        VertexBuffer(BufferLayout layout, uint32 size);
        VertexBuffer(BufferLayout layout, float32* data, uint32 size);
        ~VertexBuffer(void);

        void Bind(void);
        void Unbind(void);

        void SetData(const void* data, uint32 size);

        const BufferLayout& GetLayout(void) const;
        void SetLayout(const BufferLayout& layout);

    private:
        BufferLayout m_layout;
    };

    class NT_API IndexBuffer
    {
    public:
        NT_CLASS_DEFAULTS(IndexBuffer)
        IndexBuffer(void) = default;
        IndexBuffer(uint32* data, uint32 count);
        ~IndexBuffer(void);

        void Bind(void);
        void Unbind(void);

        uint32 GetCount(void) const;

    private:
        uint32 m_count;
    };
} // namespace Nt

#endif // _RENDERER_BUFFER_H_
