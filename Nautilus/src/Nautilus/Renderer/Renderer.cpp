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

#ifndef _NT_NAUTILUS_RENDERER_RENDERER_CPP_
    #define _NT_NAUTILUS_RENDERER_RENDERER_CPP_

#include "Renderer.h"

namespace Nt
{
    Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::BeginScene(const OrthographicCamera& camera)
    {
        s_sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("uViewProjection", s_sceneData->viewProjectionMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {}

    RendererAPI::API Renderer::GetAPI()
    {
        return RendererAPI::GetAPI();
    }
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDERER_CPP_
