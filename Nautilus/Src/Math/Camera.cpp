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

#ifndef _MATH_CAMERA_CPP_
    #define _MATH_CAMERA_CPP_

#include "Camera.h"

namespace Nt
{
    void Camera::SetProjection(const Matrix4& projection)
    {
        m_projection     = (glm::mat4)projection;
        m_viewProjection = m_projection * m_view;
    }

    const Matrix4 Camera::GetProjection(void) const
    {
        return Matrix4(m_projection);
    }

    void Camera::SetView(const Matrix4& view)
    {
        m_view           = (glm::mat4)view;
        m_viewProjection = m_projection * m_view;
    }

    const Matrix4 Camera::GetView(void) const
    {
        return Matrix4(m_view);
    }

    void Camera::SetViewProjection(const Matrix4& viewProjection)
    {
        m_viewProjection = (glm::mat4)viewProjection;
    }

    const Matrix4 Camera::GetViewProjection(void) const
    {
        return Matrix4(m_viewProjection);
    }

    OrthographicCamera::OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top, float32 near, float32 far) :
        m_left(left), m_right(right), m_bottom(bottom), m_top(top), m_near(near), m_far(far), m_position(0.0f), m_rotation(0.0f)
    {
        m_projection = glm::ortho(left, right, bottom, top, near, far);
        RecalculateView();
    }

    void OrthographicCamera::SetPosition(const Vector3& position)
    {
        m_position = (glm::vec3)position;
        RecalculateView();
    }

    Vector3 OrthographicCamera::GetPosition(void) const
    {
        return Vector3(m_position);
    }

    void OrthographicCamera::SetRotation(const float32& rotation)
    {
        m_rotation = rotation;
        RecalculateView();
    }

    float32 OrthographicCamera::GetRotation(void) const
    {
        return float32(m_rotation * (NT_PI / 180.0f));
    }

    void OrthographicCamera::RecalculateView(void)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
                              glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

        m_view           = glm::inverse(transform);
        m_viewProjection = m_projection * m_view;
    }

    PerspectiveCamera::PerspectiveCamera(float32 fov, float32 aspectRatio, float32 near, float32 far) :
        m_fov(fov), m_aspectRatio(aspectRatio), m_near(near), m_far(far), m_position(0.0f), m_front(0.0f, 0.0f, -1.0f),
        m_up(0.0f, 1.0f, 0.0f)
    {
        m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
        RecalculateView();
    }


    void PerspectiveCamera::SetPosition(const Vector3& position)
    {
        m_position = (glm::vec3)position;
        RecalculateView();
    }

    Vector3 PerspectiveCamera::GetPosition(void) const
    {
        return Vector3(m_position);
    }

    void PerspectiveCamera::SetRotation(const float32& roll, const float32& pitch, const float32& yaw)
    {
        glm::vec3 direction = glm::vec3(roll, pitch, yaw);
        m_front             = glm::normalize(direction);
        RecalculateView();
    }

    float32 PerspectiveCamera::GetRoll(void) const
    {
        return (m_front.x * (NT_PI / 180.0f));
    }

    float32 PerspectiveCamera::GetPitch(void) const
    {
        return (m_front.y * (NT_PI / 180.0f));
    }

    float32 PerspectiveCamera::GetYaw(void) const
    {
        return (m_front.z * (NT_PI / 180.0f));
    }

    void PerspectiveCamera::SetUpDirection(const Vector3& up)
    {
        m_up = (glm::vec3)up;
    }

    Vector3 PerspectiveCamera::GetUpDirection(void) const
    {
        return Vector3(m_up);
    }

    void PerspectiveCamera::SetFOV(float32 fov)
    {
        m_fov        = fov;
        m_projection = glm::perspective(glm::radians(fov), m_aspectRatio, m_near, m_far);
        RecalculateView();
    }

    void PerspectiveCamera::RecalculateView(void)
    {
        m_view           = glm::lookAt(m_position, m_position + m_front, m_up);
        m_viewProjection = m_projection * m_view;
    }
} // namespace Nt

#endif // _MATH_CAMERA_CPP_
