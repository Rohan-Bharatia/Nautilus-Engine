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

#ifndef _SCENE_SCENE_H_
    #define _SCENE_SCENE_H_

#include "Core/UUID.h"
#include "Math/Camera.h"

namespace Nt
{
    class Entity;

    class NT_API Scene
    {
    public:
        NT_CLASS_DEFAULTS(Scene)
        Scene(void);
        ~Scene(void) = default;

        static Ref<Scene> Copy(Ref<Scene> scene);

        Entity CreateEntity(const String& name="");
        Entity CreateEntity(const UUID& uuid, const String& name="");
        void DestroyEntity(Entity entity);
        Entity DuplicateEntity(Entity entity);

        Entity FindEntity(const UUID& uuid);
        Entity FindEntity(const String& name);
        Entity GetPrimaryCamera(void);

        void OnRuntimeStart(void);
        void OnRuntimeUpdate(float32 deltaTime);
        void OnRuntimeEnd(void);
        void OnViewportResize(uint32 width, uint32 height);

        bool IsRunning(void) const;
        bool IsPaused(void) const;

        void Pause(void);
        void Resume(void);
        void Step(int32 frames=1);

        template<typename... T>
        auto GetAllEntitiesWith(void)
        {
            return m_registry.view<T...>();
        }

    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T& component);

        entt::registry m_registry;
        Vector2 m_viewport;
        bool m_running, m_paused;
        int32 m_step;
        std::unordered_map<UUID, entt::entity> m_entityMap;

        friend class Entity;
    };
} // namespace Nt

#endif // _SCENE_SCENE_H_
