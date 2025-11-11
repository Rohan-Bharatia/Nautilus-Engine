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

#ifndef _RENDERER_SCENE_RENDERER_CPP_
    #define _RENDERER_SCENE_RENDERER_CPP_

#include "SceneRenderer.h"

#include "VertexArray.h"
#include "Shader.h"

#define MAX_QUADS         (20000)
#define MAX_VERTICES      (MAX_QUADS * 4)
#define MAX_INDICES       (MAX_QUADS * 6)
#define MAX_TEXTURE_SLOTS (32)

namespace Nt
{
    struct QuadVertexData
    {
        Vector3 position;
        Vector4 color;
        Vector2 texCoord;
        float32 texIndex;
        float32 tilingFactor;
    };

    struct SceneRendererData
    {
        Ref<VertexArray> quadVA;
        Ref<VertexBuffer> quadVB;
        Ref<Shader> quadProgram;
        uint32 quadIndexCount       = 0;
        QuadVertexData* quadVBStart = nullptr;
        QuadVertexData* quadVBEnd   = nullptr;

        std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> textureSlots;
        uint32 textureSlotIndex = 1; // 0 is reserved for base white texture

        SceneRenderer::Statistics stats;
    };

    static SceneRendererData s_data;

    void SceneRenderer::Initialize(void)
    {
        s_data.quadVA = CreateRef<VertexArray>();

        s_data.quadVB = CreateRef<VertexBuffer>(MAX_VERTICES * sizeof(QuadVertexData));
        s_data.quadVB->SetLayout(
        {
            { ShaderDataType::Float3, "a_position"     },
            { ShaderDataType::Float4, "a_color"        },
            { ShaderDataType::Float2, "a_texCoord"     },
            { ShaderDataType::Float,  "a_texIndex"     },
            { ShaderDataType::Float,  "a_tilingFactor" },
        });
        s_data.quadVA->AddVertexBuffer(s_data.quadVB);

        s_data.quadVBStart = new QuadVertexData[MAX_VERTICES];

        uint32* indices = new uint32[MAX_INDICES];
        uint32 offset   = 0;
        for (uint32 i = 0; i < MAX_INDICES; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset        += 4;
        }

        Ref<IndexBuffer> quadIB = CreateRef<IndexBuffer>(indices, MAX_INDICES);
        s_data.quadVA->SetIndexBuffer(quadIB);
        delete[] indices;

        TextureProps props{};
        s_data.textureSlots[0] = CreateRef<Texture2D>(props);
        uint32 whiteData       = 0xffffffff;
        s_data.textureSlots[0]->SetData(&whiteData, sizeof(whiteData));

        s_data.quadProgram = CreateRef<Shader>("Scene Renderer Quad Shader", "Assets/Shaders/quad_vs.glsl", "Assets/Shaders/quad_fs.glsl");
        s_data.quadProgram->Bind();
        int32* slots = new int32[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; ++i)
            slots[i] = i;
        s_data.quadProgram->SetIntArray("u_textures", slots, MAX_TEXTURE_SLOTS);
        delete[] slots;
    }

    void SceneRenderer::Shutdown(void)
    {
        delete[] s_data.quadVBStart;
    }

    void SceneRenderer::BeginScene(const Camera& camera, const Matrix4& transform)
    {
        s_data.quadProgram->Bind();
        s_data.quadProgram->SetMatrix4("u_viewProjection", camera.GetViewProjection() * glm::inverse(transform));

        StartBatch();
    }

    void SceneRenderer::BeginScene(const OrthographicCamera& camera)
    {
        BeginScene(camera, Matrix4(1.0f));
    }

    void SceneRenderer::BeginScene(const PerspectiveCamera& camera)
    {
        BeginScene(camera, Matrix4(1.0f));
    }

    void SceneRenderer::EndScene(void)
    {
        Flush();
    }

    void SceneRenderer::DrawQuad(const Vector2& position, const Vector2& size, float32 rotation, const Vector4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void SceneRenderer::DrawQuad(const Vector3& position, const Vector2& size, float32 rotation, const Vector4& color)
    {
        DrawQuad(position, size, rotation, s_data.textureSlots[0], 1.0f, color);
    }

    void SceneRenderer::DrawQuad(const Vector2& position, const Vector2& size, float32 rotation, const Ref<Texture2D>& texture, float32 tilingFactor, const Vector4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }

    void SceneRenderer::DrawQuad(const Vector3& position, const Vector2& size, float32 rotation, const Ref<Texture2D>& texture, float32 tilingFactor, const Vector4& tintColor)
    {
        Matrix4 transform = glm::translate(glm::mat4(1.0f), position) *
                            glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
                            glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, texture, tilingFactor, tintColor);
    }

    uint32 SceneRenderer::Statistics::GetTotalVertexCount(void) const
    {
        return quadCount * 4;
    }

    uint32 SceneRenderer::Statistics::GetTotalIndexCount(void) const
    {
        return quadCount * 6;
    }

    void SceneRenderer::ResetStats(void)
    {
        memset(&s_data.stats, 0, sizeof(Statistics));
    }

    SceneRenderer::Statistics SceneRenderer::GetStats(void)
    {
        return s_data.stats;
    }


    void SceneRenderer::DrawQuad(const Matrix4& transform, const Ref<Texture2D>& texture, float32 tilingFactor, const Color& tintColor)
    {
        if ((s_data.quadIndexCount + 6) > MAX_INDICES)
            NextBatch();

        float32 texIndex = 0.0f;
        for (uint32 i = 1; i < s_data.textureSlotIndex; ++i)
        {
            if (texture->GetRenderId() == s_data.textureSlots[i]->GetRenderId())
            {
                texIndex = (float32)i;
                break;
            }
        }

        if (texIndex == 0.0f)
        {
            if (s_data.textureSlotIndex >= MAX_TEXTURE_SLOTS)
                NextBatch();

            texIndex                                       = (float32)s_data.textureSlotIndex;
            s_data.textureSlots[s_data.textureSlotIndex++] = texture;
        }

        Vector4 positions[4] =
        {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f },
        };
        Vector2 texCoords[4] =
        {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f },
        };

        for (uint32 i = 0; i < 4; ++i)
        {
            s_data.quadVBEnd->position     = transform * positions[i];
            s_data.quadVBEnd->color        = { tintColor.r / 255.0f, tintColor.g / 255.0f, tintColor.b / 255.0f, tintColor.a };
            s_data.quadVBEnd->texCoord     = texCoords[i];
            s_data.quadVBEnd->texIndex     = texIndex;
            s_data.quadVBEnd->tilingFactor = tilingFactor;
            ++s_data.quadVBEnd;
        }

        s_data.quadIndexCount += 6;
        ++s_data.stats.quadCount;
    }

    void SceneRenderer::StartBatch(void)
    {
        s_data.quadIndexCount = 0;
        s_data.quadVBEnd      = s_data.quadVBStart;

        s_data.textureSlotIndex = 1;
    }

    void SceneRenderer::NextBatch(void)
    {
        Flush();
        StartBatch();
    }

    void SceneRenderer::Flush(void)
    {
        if (s_data.quadIndexCount > 0)
        {
            s_data.quadVB->SetData(s_data.quadVBStart, (uint32)((uint8*)s_data.quadVBEnd - (uint8*)s_data.quadVBStart));

            for (uint32 i = 0; i < s_data.textureSlotIndex; ++i)
                s_data.textureSlots[i]->Bind(i);

            s_data.quadProgram->Bind();
            RenderCommand::DrawIndexed(s_data.quadVA, s_data.quadIndexCount);
            ++s_data.stats.drawCalls;
        }
    }
} // namespace Nt

#endif // _RENDERER_SCENE_RENDERER_CPP_
