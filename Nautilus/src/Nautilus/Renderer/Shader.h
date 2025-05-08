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

#pragma once

#ifndef _NT_NAUTILUS_RENDERER_SHADER_H_
    #define _NT_NAUTILUS_RENDERER_SHADER_H_

#include "PCH.h"

namespace Nt
{
    class NT_API Shader
    {
    public:
        virtual ~Shader();

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformFloat(const std::string& name, float value)              = 0;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) = 0;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) = 0;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) = 0;
        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix)   = 0;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix)   = 0;
        virtual void UploadUniformInt(const std::string& name, int value)                  = 0;
        virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& vector)  = 0;
        virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& vector)  = 0;
        virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& vector)  = 0;
        virtual void UploadUniformBool(const std::string& name, bool value)                = 0;

        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_SHADER_H_
