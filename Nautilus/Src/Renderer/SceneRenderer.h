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

#pragma once

#ifndef _RENDERER_SCENE_RENDERER_H_
    #define _RENDERER_SCENE_RENDERER_H_

#include "RenderCommand.h"
#include "Math/Camera.h"
#include "Texture.h"

namespace Nt
{
    class NT_API SceneRenderer
    {
    public:
        NT_CLASS_DEFAULTS(SceneRenderer)

        static void Initialize(void);
        static void Shutdown(void);

        static void BeginScene(const Camera& camera, const Matrix4& transform);
        static void BeginScene(const OrthographicCamera& camera);
        static void BeginScene(const PerspectiveCamera& camera);
        static void EndScene(void);

        static void DrawQuad(const Vector2& position, const Vector2& size, float32 rotation, const Vector4& color);
        static void DrawQuad(const Vector3& position, const Vector2& size, float32 rotation, const Vector4& color);
        static void DrawQuad(const Vector2& position, const Vector2& size, float32 rotation, const Ref<Texture2D>& texture, float32 tilingFactor=1.0f, const Color& tintColor=NT_COLOR_WHITE);
        static void DrawQuad(const Vector3& position, const Vector2& size, float32 rotation, const Ref<Texture2D>& texture, float32 tilingFactor=1.0f, const Color& tintColor=NT_COLOR_WHITE);

        struct Statistics
        {
            uint32 drawCalls = 0;
            uint32 quadCount = 0;

            uint32 GetTotalVertexCount(void) const;
            uint32 GetTotalIndexCount(void) const;
        };

        static void ResetStats(void);
        static Statistics GetStats(void);

    private:
        static void DrawQuad(const Matrix4& transform, const Ref<Texture2D>& texture, float32 tilingFactor=1.0f, const Color& tintColor=NT_COLOR_WHITE);
        static void StartBatch(void);
        static void NextBatch(void);
        static void Flush(void);
    };
} // namespace Nt

#endif // _RENDERER_SCENE_RENDERER_H_
