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

#ifndef _RENDERER_VERTEX_ARRAY_CPP_
    #define _RENDERER_VERTEX_ARRAY_CPP_

#include "VertexArray.h"

namespace Nt
{
    VertexArray::VertexArray(void)
    {}

    VertexArray::~VertexArray(void)
    {}

    void VertexArray::Bind(bgfx::Encoder* encoder)
    {
        for (uint32 i = 0; i < m_vertexBuffers.size(); ++i)
            m_vertexBuffers[i]->Bind(encoder);
        m_indexBuffer->Bind(encoder);
    }

    void VertexArray::Unbind(bgfx::Encoder* encoder)
    {
        for (uint32 i = 0; i < m_vertexBuffers.size(); ++i)
            m_vertexBuffers[i]->Unbind(encoder);
        m_indexBuffer->Unbind(encoder);
    }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        // Bind();
        // vertexBuffer->Bind();
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        // Bind();
        // indexBuffer->Bind();
        m_indexBuffer = indexBuffer;
    }

    const std::vector<Ref<VertexBuffer>>& VertexArray::GetVertexBuffers(void) const
    {
        return m_vertexBuffers;
    }

    const Ref<IndexBuffer>& VertexArray::GetIndexBuffer(void) const
    {
        return m_indexBuffer;
    }
} // namespace Nt

#endif // _RENDERER_VERTEX_ARRAY_CPP_
