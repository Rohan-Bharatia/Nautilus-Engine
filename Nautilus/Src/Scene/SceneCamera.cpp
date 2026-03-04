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

#ifndef _NT_SCENE_SCENE_CAMERA_CPP_
    #define _NT_SCENE_SCENE_CAMERA_CPP_

#include "SceneCamera.h"

namespace Nt
{
    SceneCamera::SceneCamera(CameraType type)
    {
        if (type == CameraType::Orthographic)
            SetOrthographic(1.0f);
        else if (type == CameraType::Perspective)
            SetPerspective(45.0f);
    }

    void SceneCamera::SetProjection(const Matrix4& projection)
	{
		m_camera->SetProjection(projection);
	}

    const Matrix4 SceneCamera::GetProjection(void) const
	{
		return m_camera->GetProjection();
	}

    void SceneCamera::SetView(const Matrix4& view)
	{
		m_camera->SetView(view);
	}

    const Matrix4 SceneCamera::GetView(void) const
	{
		return m_camera->GetView();
	}

    void SceneCamera::SetViewProjection(const Matrix4& viewProjection)
	{
		m_camera->SetViewProjection(viewProjection);
	}

    const Matrix4 SceneCamera::GetViewProjection(void) const
	{
		return m_camera->GetViewProjection();
	}

    void SceneCamera::SetOrthographic(float32 size, float32 near, float32 far)
    {
        m_type = CameraType::Orthographic;
        m_camera.reset<OrthographicCamera>(new OrthographicCamera(-size * m_aspectRatio * 0.5,
                                                                   size * m_aspectRatio * 0.5,
                                                                  -size * 0.5, size * 0.5,
                                                                   near, far));
    }

    void SceneCamera::SetPerspective(float32 fov, float32 near, float32 far)
    {
        m_type = CameraType::Perspective;
        m_camera.reset<PerspectiveCamera>(new PerspectiveCamera(fov, m_aspectRatio, near, far));
    }

    void SceneCamera::SetViewportSize(uint32 width, uint32 height)
    {
        m_aspectRatio = (float32)width / (float32)height;
        m_camera->SetViewportSize(width, height);
    }

    CameraType SceneCamera::GetCameraType(void) const
    {
        return m_type;
    }

    void SceneCamera::OnUpdate(float32 deltaTime)
    {
        m_camera->OnUpdate(deltaTime);
    }

    void SceneCamera::OnEvent(Event& e)
    {
        m_camera->OnEvent(e);
    }
} // namespace Nt

#endif // _NT_SCENE_SCENE_CAMERA_CPP_
