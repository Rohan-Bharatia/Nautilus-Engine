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

#include "Core/Input.h"

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

    void OrthographicCamera::SetViewportSize(uint32 width, uint32 height)
    {
        m_projection = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
        RecalculateView();
    }

    void OrthographicCamera::RecalculateView(void)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
                              glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

        m_view           = glm::inverse(transform);
        m_viewProjection = m_projection * m_view;
    }

    PerspectiveCamera::PerspectiveCamera(float32 fov, float32 aspectRatio, float32 near, float32 far) :
        m_fov(fov), m_ratio(aspectRatio), m_near(near), m_far(far), m_position(0.0f), m_focalPoint(0.0f), m_distance(10.0f), m_pitch(0.0f), m_yaw(0.0f), m_prevMousePosition(0.0f, 0.0f)
    {
        RecalculateView();
    }

    void PerspectiveCamera::OnUpdate(float32 deltaTime)
    {
        if (Input::IsKeyPressed(Keycode::LeftAlt))
        {
            const glm::vec2& mouse{ Input::GetMousePositionX(), Input::GetMousePositionY() };
            glm::vec2 delta     = (mouse - m_prevMousePosition) * 0.003f;
            m_prevMousePosition = mouse;

            if (Input::IsMouseButtonPressed(MouseButton::Middle))
                MousePan(delta);
            if (Input::IsMouseButtonPressed(MouseButton::Left))
                MouseRotate(delta);
            if (Input::IsMouseButtonPressed(MouseButton::Right))
                MouseZoom(delta.y);
        }

        RecalculateView();
    }

    void PerspectiveCamera::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(NT_BIND_EVENT_FN(PerspectiveCamera::OnMouseScroll));
    }

    float32 PerspectiveCamera::GetDistance(void) const
    {
        return m_distance;
    }

    void PerspectiveCamera::SetDistance(float32 distance)
    {
        m_distance = distance;
    }

    const Vector3& PerspectiveCamera::GetPosition(void) const
    {
        return m_position;
    }

    Quaternion PerspectiveCamera::GetOrientation(void)
    {
        return Quaternion(Vector3(-m_pitch, -m_yaw, 0.0f));
    }

    Vector3 PerspectiveCamera::GetUpDirection(void)
    {
        return glm::rotate(GetOrientation(), Vector3(0.0f, 0.0f, 1.0f));
    }

    Vector3 PerspectiveCamera::GetRightDirection(void)
    {
        return glm::rotate(GetOrientation(), Vector3(0.0f, 1.0f, 0.0f));
    }

    Vector3 PerspectiveCamera::GetForwardDirection(void)
    {
        return glm::rotate(GetOrientation(), Vector3(0.0f, 0.0f, -1.0f));
    }

    void PerspectiveCamera::SetViewportSize(uint32 width, uint32 height)
    {
        m_viewport = Vector2(float32(width), float32(height));
        RecalculateProjection();
    }

    void PerspectiveCamera::RecalculateView(void)
    {
        m_position = CalculatePosition();
        m_view     = glm::inverse(glm::translate(Matrix4(1.0f), m_position) * glm::toMat4(GetOrientation()));
        m_viewProjection = m_projection * m_view;
    }

    void PerspectiveCamera::RecalculateProjection(void)
    {
        m_ratio = m_viewport.x / m_viewport.y;
        m_projection = glm::perspective(glm::radians(m_fov), m_ratio, m_near, m_far);
        m_viewProjection = m_projection * m_view;
    }

    glm::vec3 PerspectiveCamera::CalculatePosition(void)
    {
        return m_focalPoint - GetForwardDirection() * m_distance;
    }

    bool PerspectiveCamera::OnMouseScroll(MouseScrolledEvent& e)
    {
        float32 delta = e.GetYOffset() * 0.1f;
        MouseZoom(delta);
        RecalculateView();
        return false;
    }

    void PerspectiveCamera::MousePan(const Vector2& delta)
    {
        glm::vec2 speed = PanSpeed();
        m_focalPoint   -= GetRightDirection() * delta.x * speed.x * m_distance;
        m_focalPoint   += GetUpDirection() * delta.y * speed.y * m_distance;
    }

    void PerspectiveCamera::MouseRotate(const Vector2& delta)
    {
        float32 yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
        m_yaw          += yawSign * delta.x * RotationSpeed();
        m_pitch        += delta.y * RotationSpeed();
    }

    void PerspectiveCamera::MouseZoom(float32 delta)
    {
        m_distance -= delta * ZoomSpeed();
        if (m_distance < 1.0f)
        {
            m_focalPoint += GetForwardDirection();
            m_distance = 1.0f;
        }
    }

    glm::vec2 PerspectiveCamera::PanSpeed(void) const
    {
        float32 x       = std::min(m_viewport.x / 1000.0f, 2.4f);
        float32 xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3025f;
        float32 y       = std::min(m_viewport.y / 1000.0f, 2.4f);
        float32 yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3025f;
        return {xFactor, yFactor};
    }

    float32 PerspectiveCamera::RotationSpeed(void) const
    {
        return 0.8f;
    }

    float32 PerspectiveCamera::ZoomSpeed(void) const
    {
        float32 distance = m_distance * 0.2f;
        distance         = std::max(distance, 0.0f);
        float32 speed    = distance * distance;
        speed            = std::min(speed, 100.0f);
        return speed;
    }
} // namespace Nt

#endif // _MATH_CAMERA_CPP_
