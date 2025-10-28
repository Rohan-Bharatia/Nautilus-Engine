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
    {}

    Shader::~Shader(void)
    {}

    void Shader::Bind(void)
    {}

    void Shader::Unbind(void)
    {}

    void Shader::SetFloat(const String& name, float32 value)
    {}

    void Shader::SetFloat2(const String& name, const Vector2& value)
    {}

    void Shader::SetFloat3(const String& name, const Vector3& value)
    {}

    void Shader::SetFloat4(const String& name, const Vector4& value)
    {}

    void Shader::SetMatrix3(const String& name, const Matrix3& value)
    {}

    void Shader::SetMatrix4(const String& name, const Matrix4& value)
    {}

    void Shader::SetInt(const String& name, int32 value)
    {
        SetFloat(name, (float32)value);
    }

    void Shader::SetInt2(const String& name, const Vector2& value)
    {}

    void Shader::SetInt3(const String& name, const Vector3& value)
    {}

    void Shader::SetInt4(const String& name, const Vector4& value)
    {}

    void Shader::SetBoolean(const String& name, bool value)
    {}

    const String& Shader::GetName(void) const
    {
        return m_name;
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
