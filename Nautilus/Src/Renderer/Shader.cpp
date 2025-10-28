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

#ifndef _RENDERER_SHADER_CPP_
    #define _RENDERER_SHADER_CPP_

#include "Shader.h"

#include "Core/IO.h"

namespace Nt
{
    Shader::Shader(const String& name, const String& vertexSource, const String& fragmentSource) :
        m_name(name)
    {
        const char* vsSource = (const char*)vertexSource;
        const char* fsSource = (const char*)fragmentSource;;

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vsSource, nullptr);
        glCompileShader(vs);

        GLint success;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(vs, 512, nullptr, infoLog);
            NT_CORE_ERROR("Vertex Shader Compilation Failed: %s", infoLog);

            glDeleteShader(vs);
            return;
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fsSource, nullptr);
        glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(fs, 512, nullptr, infoLog);
            NT_CORE_ERROR("Fragment Shader Compilation Failed: %s", infoLog);

            glDeleteShader(vs);
            glDeleteShader(fs);
            return;
        }

        m_id = glCreateProgram();
        glAttachShader(m_id, vs);
        glAttachShader(m_id, fs);
        glLinkProgram(m_id);

        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
            NT_CORE_ERROR("Shader Program Linking Failed: %s", infoLog);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader(void)
    {
        glDeleteProgram(m_id);
    }

    void Shader::Bind(void)
    {
        glUseProgram(m_id);
    }

    void Shader::Unbind(void)
    {
        glUseProgram(0);
    }

    void Shader::SetFloat(const String& name, float32 value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform1f(location, value);
    }

    void Shader::SetFloat2(const String& name, const Vector2& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform2f(location, value.x, value.y);
    }

    void Shader::SetFloat3(const String& name, const Vector3& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::SetFloat4(const String& name, const Vector4& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::SetMatrix3(const String& name, const Matrix3& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, value.mat);
    }

    void Shader::SetMatrix4(const String& name, const Matrix4& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, value.mat);
    }

    void Shader::SetInt(const String& name, int32 value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform1i(location, value);
    }

    void Shader::SetInt2(const String& name, const Vector2& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform2i(location, value.x, value.y);
    }

    void Shader::SetInt3(const String& name, const Vector3& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform3i(location, value.x, value.y, value.z);
    }

    void Shader::SetInt4(const String& name, const Vector4& value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }

    void Shader::SetIntArray(const String& name, int32* values, uint32 count)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform1iv(location, count, values);
    }

    void Shader::SetBoolean(const String& name, bool value)
    {
        GLint location = glGetUniformLocation(m_id, ((std::string)name).c_str());
        glUniform1i(location, value);
    }

    const String& Shader::GetName(void) const
    {
        return m_name;
    }

    uint32 Shader::GetRenderId(void) const
    {
        return m_id;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        if (!Exists(shader->GetName()))
            m_shaders[shader->GetName()] = shader;
        else
            NT_CORE_WARN("Shader with name %d already exists", shader->GetName());
    }

    Ref<Shader> ShaderLibrary::Load(const String& name, const String& vertexPath, const String& fragmentPath)
    {
        Ref<Shader> shader = CreateRef<Shader>(name, vertexPath, fragmentPath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const String& name)
    {
        if (Exists(name))
            return m_shaders[name];
        else
        {
            NT_CORE_WARN("Shader with name %d does not exist", name);
            return nullptr;
        }
    }

    bool ShaderLibrary::Exists(const String& name) const
    {
        return m_shaders.find(name) != m_shaders.end();
    }
} // namespace Nt

#endif // _RENDERER_SHADER_CPP_
