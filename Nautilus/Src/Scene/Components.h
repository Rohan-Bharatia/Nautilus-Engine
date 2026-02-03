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

#ifndef _SCENE_COMPONENTS_H_
    #define _SCENE_COMPONENTS_H_

#include "Core/UUID.h"
#include "Math/Color.h"
#include "Math/Camera.h"
#include "Renderer/Texture.h"

namespace Nt
{
    struct NT_API IDComponent
    {
        UUID id;

        NT_STRUCT_DEFAULTS(IDComponent)
        IDComponent(void) = default;
        IDComponent(UUID id) : id(id) {}
    };

    struct NT_API TagComponent
    {
        String tag = "Empty Object";

        NT_STRUCT_DEFAULTS(TagComponent)
        TagComponent(void) = default;
        TagComponent(const String& tag) : tag(tag) {}
    };

    struct NT_API TransformComponent
    {
        Vector3 position = { 0.0f, 0.0f, 0.0f };
        Vector3 rotation = { 0.0f, 0.0f, 0.0f };
        Vector3 scale    = { 1.0f, 1.0f, 1.0f };
        bool lockZAxis   = false;

        NT_STRUCT_DEFAULTS(TransformComponent)
        TransformComponent(void) = default;
        TransformComponent(const Vector3& position, const Vector3& rotation, const Vector3& scale) : position(position), rotation(rotation), scale(scale) {}
        TransformComponent(const Vector3& position, const Vector3& rotation, const Vector3& scale, bool lockZAxis) : position(position), rotation(rotation), scale(scale), lockZAxis(lockZAxis) {}

        Matrix4 GetTransform(void) const
        {
            return glm::translate(Matrix4(1.0f), position) *
                   glm::toMat4(glm::quat(rotation)) *
                   glm::scale(Matrix4(1.0f), scale);
        }
    };

    struct NT_API CameraComponent
    {
        Camera camera;
        bool primary    = false;
        bool fixedRatio = false;

        NT_STRUCT_DEFAULTS(CameraComponent)
        CameraComponent(void) = default;
        CameraComponent(const Camera& camera) : camera(camera) {}
        CameraComponent(const Camera& camera, bool primary, bool fixedRatio) : camera(camera), primary(primary), fixedRatio(fixedRatio) {}
    };

    struct NT_API SpriteComponent
    {
        Color color          = NT_COLOR_WHITE;
        Ref<SubTexture2D> texture;
        float32 tilingFactor = 1.0f;

        NT_STRUCT_DEFAULTS(SpriteComponent)
        SpriteComponent(void) = default;
        SpriteComponent(const Color& color) : color(color) {}
        SpriteComponent(const Color& color, Ref<SubTexture2D> texture) : color(color), texture(texture) {}
        SpriteComponent(const Color& color, Ref<SubTexture2D> texture, float32 tilingFactor) : color(color), texture(texture), tilingFactor(tilingFactor) {}
    };

    template<typename... T>
    struct NT_API ComponentGroup
    {
        NT_STRUCT_DEFAULTS(ComponentGroup)
        ComponentGroup(void) = default;
    };

    using AllComponents = ComponentGroup<IDComponent, TagComponent, TransformComponent, CameraComponent, SpriteComponent>;
} // namespace Nt

#endif // _SCENE_COMPONENTS_H_
