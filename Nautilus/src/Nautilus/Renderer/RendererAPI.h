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

#ifndef _NT_NAUTILUS_RENDERER_RENDERER_API_H_
    #define _NT_NAUTILUS_RENDERER_RENDERER_API_H_

#include "PCH.h"

#include "VertexArray.h"

namespace Nt
{
    class NT_API RendererAPI
    {
    public:
        enum class API
        {
            None   = 0,
            OpenGL = 1
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        static API GetAPI();

    private:
        static API s_api;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDERER_API_H_
