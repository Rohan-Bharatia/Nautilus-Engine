#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#ifndef _RENDERER_RENDERER_API_CPP_
    #define _RENDERER_RENDERER_API_CPP_

#include "RendererAPI.h"

#include "RenderCommand.h"
#include "SceneRenderer.h"

namespace Nt
{
    void RendererAPI::Initialize(void)
    {
        RenderCommand::Initialize();
        SceneRenderer::Initialize();
    };

    void RendererAPI::Shutdown(void)
    {
        SceneRenderer::Shutdown();
        RenderCommand::Shutdown();
    };

    void RendererAPI::OnWindowResize(uint32 width, uint32 height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
        RenderCommand::SetScissor(0, 0, width, height);
    }

    void RendererAPI::BeginScene(const Camera& camera)
    {
        s_viewProjection = camera.GetViewProjection();
    }

    void RendererAPI::EndScene(void)
    {}

    void RendererAPI::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Matrix4& transform)
    {
        shader->Bind();
        shader->SetMatrix4("u_viewProjection", s_viewProjection);
        shader->SetMatrix4("u_transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Nt

#endif // _RENDERER_RENDERER_API_CPP_
