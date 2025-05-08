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

#ifndef _NT_NAUTILUS_RENDERER_BUFFER_H_
    #define _NT_NAUTILUS_RENDERER_BUFFER_H_

#include "PCH.h"

namespace Nt
{
    enum class ShaderDataType
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
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type);

    struct NT_API BufferElement
    {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(ShaderDataType type, std::string name, bool normalized=false);

        uint32_t GetComponentCount() const;
    };

    class NT_API BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& GetElements() const;
        uint32_t GetStride() const;

        std::vector<BufferElement>::iterator begin();
        std::vector<BufferElement>::iterator end();

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride;

        void Calculate();
    };

    class NT_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer();

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const      = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class NT_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer();

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t count);
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_BUFFER_H_
