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

#ifndef _PANELS_SCENE_HIERARCHY_PANEL_CPP_
    #define _PANELS_SCENE_HIERARCHY_PANEL_CPP_

#include "SceneHierarchyPanel.h"

namespace Nt
{
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) :
        m_context(scene)
    {}

    void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
    {
        m_context = scene;
    }

    Ref<Scene>& SceneHierarchyPanel::GetContext(void)
    {
        return m_context;
    }

    void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
    {
        m_selectedEntity = entity;
    }

    Entity SceneHierarchyPanel::GetSelectedEntity(void)
    {
        return m_selectedEntity;
    }

    void SceneHierarchyPanel::Display(void)
    {
        ImGui::Begin("Scene Hierarchy");
        m_context->GetRegistry().view<TagComponent>().each([&](auto entityId, auto&)
        {
            Entity entity(entityId, m_context.get());
            DrawEntityNode(entity);
        });
        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
            m_selectedEntity = {};
        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        ImGuiTreeNodeFlags flags = ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx((void*)(uint64)(uint32)entity, flags, (const char*)entity.GetName());
        if (ImGui::IsItemClicked())
            m_selectedEntity = entity;
        if (opened)
            ImGui::TreePop();
    }
} // namespace Nt

#endif // _PANELS_SCENE_HIERARCHY_PANEL_CPP_
