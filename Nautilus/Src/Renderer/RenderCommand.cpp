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

#ifndef _RENDERER_RENDER_COMMAND_CPP_
    #define _RENDERER_RENDER_COMMAND_CPP_

#include "RenderCommand.h"

namespace Nt
{
    void RenderCommand::Initialize(void)
    {
    #ifdef NT_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:
                    NT_CORE_FATAL("OpenGL Fatal (%u): %s", id, message);
                    break;
                case GL_DEBUG_SEVERITY_MEDIUM:
                    NT_CORE_ERROR("OpenGL Error (%u): %s", id, message);
                    break;
                case GL_DEBUG_SEVERITY_LOW:
                    NT_CORE_WARN("OpenGL Warning (%u): %s", id, message);
                    break;
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                    NT_CORE_TRACE("OpenGL Trace (%u): %s", id, message);
                    break;
            }
        }, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_TRUE);
    #endif // NT_DEBUG

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
    }

    void RenderCommand::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
    {
        glViewport(x, y, width, height);
    }

    void RenderCommand::SetScissor(uint32 x, uint32 y, uint32 width, uint32 height)
    {
        glScissor(x, y, width, height);
    }

    void RenderCommand::SetClearColor(const Color& color)
    {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a);
    }

    void RenderCommand::Clear(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::DrawFillIndexed(const Ref<VertexArray>& vertexArray, uint32 indexCount)
    {
        vertexArray->Bind();
        uint32 count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void RenderCommand::DrawWireframeIndexed(const Ref<VertexArray>& vertexArray, uint32 vertexCount)
    {
        vertexArray->Bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
    }

    void RenderCommand::SetLineWidth(float32 width)
    {
        glLineWidth(width);
    }
} // namespace Nt

#endif // _RENDERER_RENDER_COMMAND_CPP_
