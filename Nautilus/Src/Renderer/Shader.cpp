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
    Shader::Shader(const String& name, const String& vertexPath, const String& fragmentPath) :
        m_name(name)
    {
        bgfx::ShaderHandle vsh = CreateShader(ReadFile(vertexPath));
        bgfx::ShaderHandle fsh = CreateShader(ReadFile(fragmentPath));
        m_program              = bgfx::createProgram(vsh, fsh, true);
    }

    Shader::~Shader()
    {
        for (auto& [name, handle] : m_uniforms)
        {
            if (bgfx::isValid(handle))
                bgfx::destroy(handle);
        }
        m_uniforms.clear();
        if (bgfx::isValid(m_program))
            bgfx::destroy(m_program);
    }

    void Shader::Bind(void)
    {
        bgfx::submit(0, m_program);
    }

    void Shader::Unbind(void)
    {
        bgfx::submit(0, BGFX_INVALID_HANDLE);
    }

    void Shader::SetFloat(const String& name, float32 value)
    {
        bgfx::UniformHandle handle = GetUniform(name, bgfx::UniformType::Vec4);
        float32 vals[4]            = { value, 0.0f, 0.0f, 0.0f };
        bgfx::setUniform(handle, vals);
        bgfx::destroy(handle);
    }

    void Shader::SetFloat2(const String& name, const Vector2& value)
    {
        bgfx::UniformHandle handle = GetUniform(name, bgfx::UniformType::Vec4);
        float32 vals[4]            = { value.x, value.y, 0.0f, 0.0f };
        bgfx::setUniform(handle, vals);
        bgfx::destroy(handle);
    }

    void Shader::SetFloat3(const String& name, const Vector3& value)
    {
        bgfx::UniformHandle handle = GetUniform(name, bgfx::UniformType::Vec4);
        float32 vals[4]            = { value.x, value.y, value.z, 0.0f };
        bgfx::setUniform(handle, vals);
        bgfx::destroy(handle);
    }

    void Shader::SetFloat4(const String& name, const Vector4& value)
    {
        bgfx::UniformHandle handle = GetUniform(name, bgfx::UniformType::Vec4);
        float32 vals[4]            = { value.x, value.y, value.z, value.w };
        bgfx::setUniform(handle, vals);
        bgfx::destroy(handle);
    }

    void Shader::SetMatrix3(const String& name, const Matrix3& value)
    {
        bgfx::UniformHandle handle = GetUniform(name, bgfx::UniformType::Mat3);
        bgfx::setUniform(handle, value.mat);
        bgfx::destroy(handle);
    }

    void Shader::SetMatrix4(const String& name, const Matrix4& value)
    {
        bgfx::UniformHandle handle = GetUniform(name, bgfx::UniformType::Mat4);
        bgfx::setUniform(handle, value.mat);
        bgfx::destroy(handle);
    }

    void Shader::SetInt(const String& name, int32 value)
    {
        SetFloat(name, (float32)value);
    }

    void Shader::SetInt2(const String& name, const Vector2& value)
    {
        SetFloat2(name, value);
    }

    void Shader::SetInt3(const String& name, const Vector3& value)
    {
        SetFloat3(name, value);
    }

    void Shader::SetInt4(const String& name, const Vector4& value)
    {
        SetFloat4(name, value);
    }

    void Shader::SetBoolean(const String& name, bool value)
    {
        SetInt(name, value);
    }

    const String& Shader::GetName(void) const
    {
        return m_name;
    }

    bgfx::ProgramHandle Shader::GetHandle(void) const
    {
        return m_program;
    }

    bgfx::ShaderHandle Shader::CreateShader(const String& filepath)
    {
        std::ifstream file(((std::string)filepath).c_str(), std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            NT_CORE_ERROR("Failed to open shader file: %s", filepath);
            return BGFX_INVALID_HANDLE;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        const bgfx::Memory* mem = bgfx::alloc((uint32)(size + 1));
        if (!file.read((char*)mem->data, size))
        {
            NT_CORE_ERROR("Failed to read shader binary: %s", filepath);
            file.close();
            return BGFX_INVALID_HANDLE;
        }

        mem->data[size] = '\0';
        file.close();

        bgfx::ShaderHandle shader = bgfx::createShader(mem);
        if (!bgfx::isValid(shader))
        {
            NT_CORE_ERROR("Failed to create shader from binary: %s", filepath);
            return BGFX_INVALID_HANDLE;
        }

        return shader;
    }

    bgfx::UniformHandle Shader::GetUniform(const String& name, bgfx::UniformType::Enum type)
    {
        auto it = m_uniforms.find(name);
        if (it != m_uniforms.end())
            return it->second;

        bgfx::UniformHandle handle = bgfx::createUniform(((std::string)name).c_str(), type);
        m_uniforms[name]           = handle;
        return handle;
    }
} // namespace Nt

#endif // _RENDERER_SHADER_CPP_
