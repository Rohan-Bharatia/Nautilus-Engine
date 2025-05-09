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

#ifndef _NT_NAUTILUS_RENDERER_RENDERER_H_
    #define _NT_NAUTILUS_RENDERER_RENDERER_H_

#include "PCH.h"

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Nt
{
    class NT_API Renderer
    {
    public:
        static void BeginScene(const OrthographicCamera& camera);
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
        static void EndScene();

        static RendererAPI::API GetAPI();

    private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };

        static SceneData* s_sceneData;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_RENDERER_H_
