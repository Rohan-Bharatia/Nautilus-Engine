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

#ifndef _NT_NAUTILUS_RENDERER_ORTHOGRAPHIC_CAMERA_H_
    #define _NT_NAUTILUS_RENDERER_ORTHOGRAPHIC_CAMERA_H_

#include "PCH.h"

#define NT_VEC2_ZERO glm::vec2(0.0f, 0.0f)
#define NT_VEC2_ONE glm::vec2(1.0f, 1.0f)
#define NT_VEC2_UP glm::vec2(0.0f, 1.0f)
#define NT_VEC2_DOWN glm::vec2(0.0f, -1.0f)
#define NT_VEC2_LEFT glm::vec2(-1.0f, 0.0f)
#define NT_VEC2_RIGHT glm::vec2(1.0f, 0.0f)
#define NT_VEC3_ZERO glm::vec3(0.0f, 0.0f, 0.0f)
#define NT_VEC3_ONE glm::vec3(1.0f, 1.0f, 1.0f)
#define NT_VEC3_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define NT_VEC3_DOWN glm::vec3(0.0f, -1.0f, 0.0f)
#define NT_VEC3_LEFT glm::vec3(-1.0f, 0.0f, 0.0f)
#define NT_VEC3_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define NT_VEC3_FORWARD glm::vec3(0.0f, 0.0f, -1.0f)
#define NT_VEC3_BACKWARD glm::vec3(0.0f, 0.0f, 1.0f)
#define NT_VEC4_ZERO glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)
#define NT_VEC4_ONE glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define NT_VEC4_UP glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)
#define NT_VEC4_DOWN glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)
#define NT_VEC4_LEFT glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f)
#define NT_VEC4_RIGHT glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
#define NT_VEC4_FORWARD glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)
#define NT_VEC4_BACKWARD glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)

namespace Nt
{
    class NT_API OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        glm::vec3 GetPosition() const;
        void SetPosition(const glm::vec3& position);

        float GetRotation() const;
        void SetRotation(float rotation);

        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetViewProjectionMatrix() const;

    private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_viewProjectionMatrix;
        glm::vec3 m_position;
        float m_rotation;

        void RecalculateViewMatrix();

    };
} // namespace Nt

#endif // _Nt_NAUTILUS_RENDERER_ORTHOGRAPHIC_CAMERA_H_
