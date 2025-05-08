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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_BUFFER_H_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_BUFFER_H_

#include "Nautilus/Renderer/Buffer.h"

namespace Nt
{
    class OpenGLVertexBuffer :
        public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override;
        virtual void SetLayout(const BufferLayout& layout) override;

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };

    class NT_API OpenGLIndexBuffer :
        public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override;

    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_BUFFER_H_
