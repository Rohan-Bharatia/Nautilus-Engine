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

#ifndef _NT_NAUTILUS_RENDERER_RENDER_COMMAND_H_
    #define _NT_NAUTILUS_RENDERER_RENDER_COMMAND_H_

#include "PCH.h"

#include "RendererAPI.h"
#include "VertexArray.h"

namespace Nt
{
    class RenderCommand
    {
    public:
        static void SetClearColor(const glm::vec4& color);
        static void Clear();
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

    private:
        static RendererAPI* s_api;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDER_COMMAND_H_
