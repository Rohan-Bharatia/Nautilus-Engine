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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_SHADER_CPP_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_SHADER_CPP_

#include "OpenGLShader.h"

namespace Nt
{
    OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLchar const* code  = (const GLchar*)vertexSource.c_str();
        glShaderSource(vertexShader, 1, &code, NULL);
        glCompileShader(vertexShader);

        GLint success = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            NT_CORE_LOG_ERROR("Failed to compile vertex shader: {0}", infoLog.data());
            glDeleteShader(vertexShader);
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        code                  = (const GLchar*)fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &code, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
            NT_CORE_LOG_ERROR("Failed to compile fragment shader:\n{0}", infoLog.data());
            glDeleteShader(fragmentShader);
            return;
        }

        m_rendererID = glCreateProgram();

        glAttachShader(m_rendererID, vertexShader);
        glAttachShader(m_rendererID, fragmentShader);
        glLinkProgram(m_rendererID);

        glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);
            NT_CORE_LOG_ERROR("Failed to link shader m_rendererID:\n{0}", infoLog.data());
            glDeleteProgram(m_rendererID);
            return;
        }

        glDetachShader(m_rendererID, vertexShader);
        glDetachShader(m_rendererID, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        Unbind();
        glDeleteProgram(m_rendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_rendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_SHADER_CPP_
