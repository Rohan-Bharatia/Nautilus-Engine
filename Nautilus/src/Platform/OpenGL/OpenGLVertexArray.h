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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H_

#include "PCH.h"

#include "Nautilus/Renderer/VertexArray.h"

namespace Nt
{
    class NT_API OpenGLVertexArray :
        public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
        uint32_t m_rendererID;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H_
