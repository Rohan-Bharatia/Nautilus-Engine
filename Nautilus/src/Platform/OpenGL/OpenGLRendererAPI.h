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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_API_H_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_API_H_

#include "PCH.h"

#include "Nautilus/Renderer/RendererAPI.h"

namespace Nt
{
    class OpenGLRendererAPI :
        public RendererAPI
    {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_API_H_
