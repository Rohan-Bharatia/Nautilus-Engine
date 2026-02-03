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

#ifndef _SCENE_SCENE_CPP_
    #define _SCENE_SCENE_CPP_

#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Renderer/SceneRenderer.h"

namespace Nt
{
    template<typename... T>
    static void CopyComponent(entt::registry& dst, entt::registry& src, std::unordered_map<UUID, entt::entity>& entityMap)
    {
        ([&](void)
        {
            auto view = src.view<T>();
            for (auto entity : view)
            {
                entt::entity dstEntity = entityMap.at(src.get<IDComponent>(entity).id);
                auto& srcComponent     = src.get<T>(entity);
                dst.emplace_or_replace<T>(dstEntity, srcComponent);
            }
        }(), ...);
    }

    template<typename... T>
    static void CopyComponent(ComponentGroup<T...>, entt::registry& dst, entt::registry& src, std::unordered_map<UUID, entt::entity>& entityMap)
    {
        CopyComponent<T...>(dst, src, entityMap);
    }

    template<typename... T>
    static void CopyEntityIfExists(Entity dst, Entity src)
    {
        ([&](void)
        {
            if (src.HasComponent<T>())
                dst.AddOrReplaceComponent<T>(src.GetComponent<T>());
        }(), ...);
    }

    template<typename... T>
    static void CopyEntityIfExists(ComponentGroup<T...>, Entity dst, Entity src)
    {
        CopyEntityIfExists<T...>(dst, src);
    }

    Scene::Scene(void) :
        m_viewport(0.0f), m_running(false), m_paused(false), m_step(0), m_entityMap({})
    {}

    Ref<Scene> Scene::Copy(Ref<Scene> scene)
    {
        Ref<Scene> newScene = CreateRef<Scene>();

        newScene->m_viewport = scene->m_viewport;
        newScene->m_running  = scene->m_running;
        newScene->m_paused   = scene->m_paused;
        newScene->m_step     = scene->m_step;

        auto& srcRegistry = scene->m_registry;
        auto& dstRegistry = newScene->m_registry;
        std::unordered_map<UUID, entt::entity> entityMap;

        auto view = srcRegistry.view<IDComponent>();
        for (auto entity : view)
        {
            UUID uuid = srcRegistry.get<IDComponent>(entity).id;
            const String& name = srcRegistry.get<TagComponent>(entity).tag;
            Entity newEntity   = newScene->CreateEntity(uuid, name);
            entityMap[uuid]    = (entt::entity)newEntity;
        }

        CopyComponent(AllComponents{}, dstRegistry, srcRegistry, entityMap);
        return newScene;
    }

    Entity Scene::CreateEntity(const String& name)
    {
        return CreateEntity(UUID(), name);
    }

    Entity Scene::CreateEntity(const UUID& uuid, const String& name)
    {
        NT_ASSERT(this, "Scene is null!");

        Entity entity(m_registry.create(), this);
        entity.AddComponent<IDComponent>(uuid);
        entity.AddComponent<TagComponent>(name == "" ? "Empty Object" : name);
        entity.AddComponent<TransformComponent>(Vector3(0.0f), Vector3(0.0f), Vector3(1.0f), false);
        m_entityMap[uuid] = (entt::entity)entity;
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_entityMap.erase(entity.GetComponent<IDComponent>().id);
        m_registry.destroy((entt::entity)entity);
    }

    Entity Scene::DuplicateEntity(Entity entity)
    {
        String name = entity.GetName();
        Entity newEntity = CreateEntity(name);
        CopyEntityIfExists(AllComponents{}, newEntity, entity);
        return newEntity;
    }

    Entity Scene::FindEntity(const UUID& uuid)
    {
        if (m_entityMap.find(uuid) != m_entityMap.end())
            return Entity(m_entityMap.at(uuid), this);
        return Entity();
    }

    Entity Scene::FindEntity(const String& name)
    {
        auto view = m_registry.view<TagComponent>();
        for (auto entity : view)
        {
            auto& tag = view.get<TagComponent>(entity);
            if (tag.tag == name)
                return Entity(entity, this);
        }
        return Entity();
    }

    Entity Scene::GetPrimaryCamera(void)
    {
        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (cameraComponent.primary)
                return Entity(entity, this);
        }
        return Entity();
    }

    void Scene::OnRuntimeStart(void)
    {
        m_running = true;
    }

    void Scene::OnRuntimeUpdate(float32 deltaTime)
    {
        if (!m_paused || m_step-- > 0)
        {
            Camera* mainCamera      = nullptr;
            Matrix4 cameraTransform = Matrix4(1.0f);
            {
                auto view = m_registry.view<TransformComponent, CameraComponent>();
                for (auto entity : view)
                {
                    auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
                    if (camera.primary)
                    {
                        mainCamera      = &camera.camera;
                        cameraTransform = transform.GetTransform();
                        break;
                    }
                }
            }

            if (mainCamera)
            {
                SceneRenderer::BeginScene(*mainCamera, cameraTransform);
                {
                    auto group = m_registry.group<TransformComponent, SpriteComponent>();
                    for (auto entity : group)
                    {
                        auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
                        SceneRenderer::DrawSprite(transform, sprite);
                    }
                }
                SceneRenderer::EndScene();
            }
        }
    }

    void Scene::OnRuntimeEnd(void)
    {
        m_running = false;
    }

    void Scene::OnViewportResize(uint32 width, uint32 height)
    {
        if (m_viewport.x == (float32)width && m_viewport.y == (float32)height)
            return;

        m_viewport.x = (float32)width;
        m_viewport.y = (float32)height;

        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.fixedRatio)
                cameraComponent.camera.SetViewportSize((uint32)m_viewport.x, (uint32)m_viewport.y);
        }
    }

    bool Scene::IsRunning(void) const
    {
        return m_running;
    }

    bool Scene::IsPaused(void) const
    {
        return m_paused;
    }

    void Scene::Pause(void)
    {
        m_paused  = true;
        m_running = false;
    }

    void Scene::Resume(void)
    {
        m_paused  = false;
        m_running = true;
    }

    void Scene::Step(int32 frames)
    {
        m_paused  = false;
        m_running = true;
        m_step    = frames;
    }

    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T& component)
    {
        NT_ASSERT(sizeof(T) == 0, "No component added");
    }

    template<>
    void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        if (m_viewport.x != 0.0f && m_viewport.y != 0.0f)
            component.camera.SetViewportSize((uint32)m_viewport.x, (uint32)m_viewport.y);
    }

    template<>
    void Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
    {}
} // namespace Nt

#endif // _SCENE_SCENE_CPP_
