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

namespace Nt
{
    class NT_API Camera
    {
    public:
        NT_CLASS_DEFAULTS(Camera)
        Camera(void) = default;

        void SetProjection(const Matrix4& projection);
        const Matrix4 GetProjection(void) const;

        void SetView(const Matrix4& view);
        const Matrix4 GetView(void) const;

        void SetViewProjection(const Matrix4& viewProjection);
        const Matrix4 GetViewProjection(void) const;

        virtual void SetViewportSize(uint32 width, uint32 height) {};

    protected:
        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_viewProjection;
    };

    class NT_API OrthographicCamera :
        public Camera
    {
    public:
        NT_CLASS_DEFAULTS(OrthographicCamera)
        OrthographicCamera(void) = default;
        OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top, float32 near=-1.0f, float32 far=1.0f);

        void SetPosition(const Vector3& position);
        Vector3 GetPosition(void) const;

        void SetRotation(const float32& rotation);
        float32 GetRotation(void) const;

        virtual void SetViewportSize(uint32 width, uint32 height) override;

    private:
        void RecalculateView(void);

        float32 m_left, m_right, m_bottom, m_top, m_near, m_far;
        glm::vec3 m_position;
        float32 m_rotation;
    };

    class NT_API PerspectiveCamera :
        public Camera
    {
    public:
        NT_CLASS_DEFAULTS(PerspectiveCamera)
        PerspectiveCamera(void) = default;
        PerspectiveCamera(float32 fov, float32 aspectRatio, float32 near=0.1f, float32 far=1000.0f);

        float32 GetDistance(void) const;
        void SetDistance(float32 distance);

        const Vector3& GetPosition(void) const;
        Quaternion GetOrientation(void) const;

        Vector3 GetUpDirection(void) const;
        Vector3 GetRightDirection(void) const;
        Vector3 GetForwardDirection(void) const;

        virtual void SetViewportSize(uint32 width, uint32 height) override;

    private:
        void RecalculateProjection(void);
        glm::vec3 CalculatePosition(void);

        float32 m_fov, m_ratio, m_near, m_far;
        glm::vec3 m_position, m_focalPoint;
        float32 m_distance, m_pitch, m_yaw;
        glm::vec2 m_viewport;
    };
} // namespace Nt

#endif // _MATH_CAMERA_H_
