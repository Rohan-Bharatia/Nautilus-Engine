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

#ifndef _NT_NAUTILUS_RENDERER_VERTEX_ARRAY_H_
    #define _NT_NAUTILUS_RENDERER_VERTEX_ARRAY_H_

#include "PCH.h"

#include "Buffer.h"

namespace Nt
{
    class NT_API VertexArray
    {
    public:
        virtual ~VertexArray();

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)    = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const                 = 0;

        static VertexArray* Create();
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_VERTEX_ARRAY_H_
