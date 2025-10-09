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

#ifndef _MATH_CAMERA_H_
    #define _MATH_CAMERA_H_

#include "Matrix.h"
#include "Vector.h"
#include "Angle.h"

namespace Nt
{
    class NT_API OrthographicCamera
    {
    public:
        NT_CLASS_DEFAULTS(OrthographicCamera)
        OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top, float32 near=-1.0f, float32 far=1.0f);

        void SetPosition(const Vector3& position);
        Vector3 GetPosition(void) const;

        void SetRotation(const Angle& rotation);
        Angle GetRotation(void) const;

        const Matrix4 GetProjection(void) const;
        const Matrix4 GetView(void) const;
        const Matrix4 GetViewProjection(void) const;

    private:
        void RecalculateView(void);

        float32 m_left, m_right, m_bottom, m_top, m_near, m_far;
        glm::vec3 m_position;
        float32 m_rotation;
        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_viewProjection;
    };

    class NT_API PerspectiveCamera
    {
    public:
        NT_CLASS_DEFAULTS(PerspectiveCamera)
        PerspectiveCamera(float32 fov, float32 aspectRatio, float32 near=0.1f, float32 far=1000.0f);

        void SetPosition(const Vector3& position);
        Vector3 GetPosition(void) const;

        void SetRotation(const Angle& roll, const Angle& pitch, const Angle& yaw);
        Angle GetRoll(void) const;
        Angle GetPitch(void) const;
        Angle GetYaw(void) const;

        void SetUpDirection(const Vector3& up);
        Vector3 GetUpDirection(void) const;

        void SetFOV(float32 fov);

        const Matrix4 GetProjection(void) const;
        const Matrix4 GetView(void) const;
        const Matrix4 GetViewProjection(void) const;

    private:
        void RecalculateView(void);

        float32 m_fov, m_aspectRatio, m_near, m_far;
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_viewProjection;
    };
} // namespace Nt

#endif // _MATH_CAMERA_H_
