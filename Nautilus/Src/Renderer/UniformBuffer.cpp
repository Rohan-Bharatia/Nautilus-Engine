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

#ifndef _RENDERER_UNIFORM_BUFFER_CPP_
    #define _RENDERER_UNIFORM_BUFFER_CPP_

#include "UniformBuffer.h"

namespace Nt
{
    UniformBuffer::UniformBuffer(uint32 size, uint32 binding)
    {
        glCreateBuffers(1, &m_id);
        glNamedBufferStorage(m_id, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
    }

    UniformBuffer::~UniformBuffer(void)
    {
        glDeleteBuffers(1, &m_id);
    }

    void UniformBuffer::SetData(const void* data, uint32 size, uint32 offset)
    {
        glNamedBufferSubData(m_id, offset, size, data);
    }

    uint32 UniformBuffer::GetRenderId(void) const
    {
        return m_id;
    }
} // namespace Nt

#endif // _RENDERER_UNIFORM_BUFFER_CPP_
