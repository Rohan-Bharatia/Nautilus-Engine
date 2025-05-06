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
    class NT_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer();

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

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
