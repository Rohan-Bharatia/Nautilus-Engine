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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_CPP_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_CPP_

#include "OpenGLVertexArray.h"

namespace Nt
{
    static GLenum ShaderTypeDataToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            default:
                NT_ASSERT(false, "Unknown shader data type!");
                return 0;
        }
        NT_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() :
        m_rendererID(0)
    {
        glCreateVertexArrays(1, &m_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_rendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        NT_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

        glBindVertexArray(m_rendererID);
        vertexBuffer->Bind();

        for (int i = 0; i < vertexBuffer->GetLayout().GetElements().size(); ++i)
        {
            BufferElement elt = vertexBuffer->GetLayout().GetElements()[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, elt.GetComponentCount(), ShaderTypeDataToOpenGLBaseType(elt.type), elt.normalized,
                                  vertexBuffer->GetLayout().GetStride(), reinterpret_cast<const void*>(std::uintptr_t(elt.offset)));
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererID);
        indexBuffer->Bind();

        m_indexBuffer = indexBuffer;
    }

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
    {
        return m_vertexBuffers;
    }

    const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_indexBuffer;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_CPP_
