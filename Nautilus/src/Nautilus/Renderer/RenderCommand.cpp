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

#ifndef _NT_NAUTILUS_RENDERER_RENDER_COMMAND_CPP_
    #define _NT_NAUTILUS_RENDERER_RENDER_COMMAND_CPP_

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nt
{
    RendererAPI* RenderCommand::s_api = new OpenGLRendererAPI();

    void RenderCommand::SetClearColor(const glm::vec4& color)
    {
        s_api->SetClearColor(color);
    }

    void RenderCommand::Clear()
    {
        s_api->Clear();
    }

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        s_api->DrawIndexed(vertexArray);
    }
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDER_COMMAND_CPP_
