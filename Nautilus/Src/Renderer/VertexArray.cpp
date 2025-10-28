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
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:   return GL_FLOAT;
            case ShaderDataType::Float2:  return GL_FLOAT;
            case ShaderDataType::Float3:  return GL_FLOAT;
            case ShaderDataType::Float4:  return GL_FLOAT;
            case ShaderDataType::Mat3:    return GL_FLOAT;
            case ShaderDataType::Mat4:    return GL_FLOAT;
            case ShaderDataType::Int:     return GL_INT;
            case ShaderDataType::Int2:    return GL_INT;
            case ShaderDataType::Int3:    return GL_INT;
            case ShaderDataType::Int4:    return GL_INT;
            case ShaderDataType::Boolean: return GL_BOOL;
            default:                      return 0;
        }
    }

    VertexArray::VertexArray(void) :
        m_vertexBufferIndex(0)
    {
        glCreateVertexArrays(1, &m_id);
    }

    VertexArray::~VertexArray(void)
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArray::Bind(void)
    {
        glBindVertexArray(m_id);
    }

    void VertexArray::Unbind(void)
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_id);
        vertexBuffer->Bind();

        const BufferLayout& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            switch (element.type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(m_vertexBufferIndex);
                    glVertexAttribPointer(m_vertexBufferIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), element.normalized, layout.GetStride(), (const void*)(uintptr_t)element.offset);
                    ++m_vertexBufferIndex;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint8 count = element.GetComponentCount();
                    for (uint8 i = 0; i < count; ++i)
                    {
                        glEnableVertexAttribArray(m_vertexBufferIndex);
                        glVertexAttribPointer(m_vertexBufferIndex, count, ShaderDataTypeToOpenGLBaseType(element.type), element.normalized, layout.GetStride(), (const void*)(element.offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(m_vertexBufferIndex, 1);
                        ++m_vertexBufferIndex;
                    }
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Boolean:
                {
                    glEnableVertexAttribArray(m_vertexBufferIndex);
                    glVertexAttribIPointer(m_vertexBufferIndex, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), layout.GetStride(), (const void*)(uintptr_t)element.offset);
                    break;
                }
                default:
                    NT_CORE_ERROR("Unknown shader data type (%d)!", element.type);
            }
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_id);
        indexBuffer->Bind();

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

    uint32 VertexArray::GetRenderId(void) const
    {
        return m_id;
    }
} // namespace Nt

#endif // _RENDERER_VERTEX_ARRAY_CPP_
