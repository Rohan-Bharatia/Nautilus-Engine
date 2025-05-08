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

#ifndef _NT_NAUTILUS_RENDERER_ORTHOGRAPHIC_CAMERA_CPP_
    #define _NT_NAUTILUS_RENDERER_ORTHOGRAPHIC_CAMERA_CPP_

#include "OrthographicCamera.h"

namespace Nt
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
        m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_viewMatrix(1.0f),
        m_viewProjectionMatrix(m_projectionMatrix * m_viewMatrix), m_position(0.0f), m_rotation(0.0f)
    {
    }

    glm::vec3 OrthographicCamera::GetPosition() const
    {
        return m_position;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        m_position = position;
        RecalculateViewMatrix();
    }

    float OrthographicCamera::GetRotation() const
    {
        return m_rotation;
    }

    void OrthographicCamera::SetRotation(float rotation)
    {
        m_rotation = rotation;
        RecalculateViewMatrix();
    }

    const glm::mat4& OrthographicCamera::GetProjectionMatrix() const
    {
        return m_projectionMatrix;
    }

    const glm::mat4& OrthographicCamera::GetViewMatrix() const
    {
        return m_viewMatrix;
    }

    const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const
    {
        return m_viewProjectionMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform    = glm::translate(glm::mat4(1.0f), m_position) *
                                 glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
        m_viewMatrix           = glm::inverse(transform);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
} // namespace Nt

#endif // _Nt_NAUTILUS_RENDERER_ORTHOGRAPHIC_CAMERA_CPP_
