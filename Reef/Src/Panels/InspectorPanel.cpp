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

#ifndef _PANELS_INSPECTOR_PANEL_CPP_
    #define _PANELS_INSPECTOR_PANEL_CPP_

#include "InspectorPanel.h"

namespace Nt
{
    InspectorPanel::InspectorPanel(const Ref<Scene>& scene) :
        m_context(scene)
    {}

    void InspectorPanel::SetContext(const Ref<Scene>& scene)
    {
        m_context = scene;
    }

    Ref<Scene>& InspectorPanel::GetContext(void)
    {
        return m_context;
    }

    void InspectorPanel::SetSelectedEntity(Entity entity)
    {
        m_selectedEntity = entity;
    }

    Entity InspectorPanel::GetSelectedEntity(void)
    {
        return m_selectedEntity;
    }

    void InspectorPanel::Display(void)
    {
        ImGui::Begin("Inspector");
        if (m_selectedEntity)
            DrawComponents(m_selectedEntity);
        ImGui::End();
    }

    void InspectorPanel::DrawComponents(Entity entity)
    {
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, (const char*)entity.GetName());
        if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            entity.SetName(buffer);

        ImGui::Separator();

        auto flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), flags, "Transform"))
            {
                auto& transform = entity.GetComponent<TransformComponent>();
                ImGui::DragFloat3("Translation", glm::value_ptr(transform.position), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
                ImGui::TreePop();
            }
        }
    }
} // namespace Nt

#endif // _PANELS_INSPECTOR_PANEL_CPP_
