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

#ifndef _RENDERER_RENDER_COMMAND_H_
    #define _RENDERER_RENDER_COMMAND_H_

#include "VertexArray.h"
#include "Math/Color.h"

namespace Nt
{
    class NT_API RenderCommand
    {
    public:
        static void Initialize(void);

        static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
        static void SetScissor(uint32 x, uint32 y, uint32 width, uint32 height);

        static void SetClearColor(const Color& color);
        static void Clear(void);

        static void DrawFillIndexed(const Ref<VertexArray>& vertexArray, uint32 indexCount=0);
        static void DrawWireframeIndexed(const Ref<VertexArray>& vertexArray, uint32 vertexCount);

        static void SetLineWidth(float32 width);
    };
} // namespace Nt

#endif // _RENDERER_RENDER_COMMAND_H_
