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

#ifndef _SCENE_ENTITY_H_
    #define _SCENE_ENTITY_H_

#include "Core/UUID.h"

#include "Scene.h"

namespace Nt
{
    class NT_API Entity
    {
    public:
        NT_CLASS_DEFAULTS(Entity)
        Entity(void) = default;
        Entity(entt::entity handle, Scene* scene);

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            if (HasComponent<T>())
                return GetComponent<T>();
            T& component = m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
            m_scene->OnComponentAdded<T>(*this, component);
            return component;
        }

        template<typename T, typename... Args>
        T& AddOrReplaceComponent(Args&&... args)
        {
            T& component = m_scene->m_registry.emplace_or_replace<T>(m_handle, std::forward<Args>(args)...);
            m_scene->OnComponentAdded<T>(*this, component);
            return component;
        }

        template<typename T>
        void RemoveComponent(void)
        {
            if (HasComponent<T>())
                m_scene->m_registry.remove<T>(m_handle);
        }

        template<typename T>
        T& GetComponent(void)
        {
            if (HasComponent<T>())
            {
                T& component = m_scene->m_registry.get<T>(m_handle);
                return component;
            }
            T& component = m_scene->m_registry.emplace<T>(m_handle, T());
            return component;
        }

        template<typename T>
        bool HasComponent(void) const
        {
            return m_scene->m_registry.any_of<T>(m_handle);
        }

        UUID GetUUID(void);
        String GetName(void);

        operator bool(void) const;
        operator entt::entity(void) const;
        operator uint32(void) const;

        bool operator==(const Entity& other) const;
        bool operator!=(const Entity& other) const;

    private:
        entt::entity m_handle = { entt::null };
        Scene* m_scene        = nullptr;
    };
} // namespace Nt

#endif // _SCENE_ENTITY_H_
