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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_SHADER_H_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_SHADER_H_

#include "Nautilus/Renderer/Shader.h"

namespace Nt
{
    class NT_API OpenGLShader :
        public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void UploadUniformFloat(const std::string& name, float value) override;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) override;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) override;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) override;
        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        virtual void UploadUniformInt(const std::string& name, int value) override;
        virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& vector) override;
        virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& vector) override;
        virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& vector) override;
        virtual void UploadUniformBool(const std::string& name, bool value) override;

    private:
        unsigned int m_rendererID;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_SHADER_H_
