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

#ifndef _NT_SCENE_SCENE_CAMERA_H_
    #define _NT_SCENE_SCENE_CAMERA_H_

#include "Math/Camera.h"

namespace Nt
{
    class SceneCamera :
        public Camera
    {
    public:
        NT_CLASS_DEFAULTS(SceneCamera)
        SceneCamera(void) = default;
        SceneCamera(CameraType type);
        virtual ~SceneCamera(void) = default;

        virtual void SetProjection(const Matrix4& projection) override;
        virtual const Matrix4 GetProjection(void) const override;

        virtual void SetView(const Matrix4& view) override;
        virtual const Matrix4 GetView(void) const override;

        virtual void SetViewProjection(const Matrix4& viewProjection) override;
        virtual const Matrix4 GetViewProjection(void) const override;

        void SetOrthographic(float32 size, float32 near=-1.0f, float32 far=1.0f);
        void SetPerspective(float32 fov, float32 near=0.01f, float32 far=1000.0f);

        void SetOrthographicSize(float32 size);
        float32 GetOrthographicSize(void) const;
        void SetOrthographicNear(float32 near);
        float32 GetOrthographicNear(void) const;
        void SetOrthographicFar(float32 far);
        float32 GetOrthographicFar(void) const;

        void SetPerspectiveFOV(float32 fov);
        float32 GetPerspectiveFOV(void) const;
        void SetPerspectiveNear(float32 near);
        float32 GetPerspectiveNear(void) const;
        void SetPerspectiveFar(float32 far);
        float32 GetPerspectiveFar(void) const;

        void SetCameraType(CameraType type);
        CameraType GetCameraType(void) const;

        virtual void SetViewportSize(uint32 width, uint32 height) override;
        virtual void OnUpdate(float32 deltaTime) override;
        virtual void OnEvent(Event& e) override;

    private:
        CameraType m_type     = CameraType::Orthographic;
        float32 m_aspectRatio = 16.0f / 9.0f;
        Ref<Camera> m_camera  = CreateRef<PerspectiveCamera>(-1.0f, 1.0f, -1.0f, 1.0f);
        float32 m_orthoSize   = 10.0f,
                m_orthoNear   = -1.0f,
                m_orthoFar    = 1.0f;
        float32 m_perspFOV    = 60.0f,
                m_perspNear   = 0.01f,
                m_perspFar    = 1000.0f;
    };
} // namespace Nt

#endif // _NT_SCENE_SCENE_CAMERA_H_
