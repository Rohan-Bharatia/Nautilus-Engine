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

#ifndef _RENDERER_RENDERER_API_H_
    #define _RENDERER_RENDERER_API_H_

#include "Shader.h"
#include "VertexArray.h"
#include "Math/Matrix.h"
#include "Math/Camera.h"

namespace Nt
{
    class NT_API RendererAPI
    {
    public:
        static void Initialize(void);
        static void Shutdown(void);

        static void OnWindowResize(uint32 width, uint32 height);

        static void BeginScene(const Camera& camera);
        static void EndScene(void);
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Matrix4& transform=Matrix4(1.0f));

    private:
        inline static Matrix4 s_viewProjection = Matrix4(1.0f);
    };
} // namespace Nt

#endif // _RENDERER_RENDERER_API_H_
