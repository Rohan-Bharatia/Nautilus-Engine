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

#ifndef _RENDERER_SHADER_H_
    #define _RENDERER_SHADER_H_

#include "Core/String.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace Nt
{
    enum class NT_API ShaderType
    {
        None = 0,
        Vertex,
        Fragment,
        Compute,
    };

    class NT_API Shader
    {
    public:
        NT_CLASS_DEFAULTS(Shader)
        Shader(const String& name, const String& vertexPath, const String& fragmentPath);
        ~Shader(void);

        void Bind(void);
        void Unbind(void);

        void SetFloat(const String& name, float32 value);
        void SetFloat2(const String& name, const Vector2& value);
        void SetFloat3(const String& name, const Vector3& value);
        void SetFloat4(const String& name, const Vector4& value);
        void SetMatrix3(const String& name, const Matrix3& value);
        void SetMatrix4(const String& name, const Matrix4& value);
        void SetInt(const String& name, int32 value);
        void SetInt2(const String& name, const Vector2& value);
        void SetInt3(const String& name, const Vector3& value);
        void SetInt4(const String& name, const Vector4& value);
        void SetBoolean(const String& name, bool value);

        const String& GetName(void) const;

    private:
        String m_name;
    };

    class NT_API ShaderLibrary
    {
    public:
        NT_CLASS_DEFAULTS(ShaderLibrary)
        ~ShaderLibrary(void);

        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const String& name, const String& vertexPath, const String& fragmentPath);
        Ref<Shader> Get(const String& name);
        bool Exists(const String& name) const;

    private:
        std::unordered_map<String, Ref<Shader>> m_shaders;
    };
} // namespace Nt

#endif // _RENDERER_SHADER_H_
