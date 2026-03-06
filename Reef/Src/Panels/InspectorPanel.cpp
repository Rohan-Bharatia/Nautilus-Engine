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
    static void DrawVec2Control(const String& label, Vector2& values, float32 resetValue = 0.0f, float32 columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[1];

        ImGui::PushID((const char*)label);
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text((const char*)label);
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        float32 lineSize = ImGui::GetFontSize() + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineSize + 3.0f, lineSize };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
    }

    static void DrawVec3Control(const String& label, Vector3& values, float32 resetValue = 0.0f, float32 columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[1];

        ImGui::PushID((const char*)label);
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text((const char*)label);
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        float32 lineSize = ImGui::GetFontSize() + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineSize + 3.0f, lineSize };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
    }

    static void DrawVec3Control(const String& label, Vector4& values, float32 resetValue = 0.0f, float32 columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[1];

        ImGui::PushID((const char*)label);
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text((const char*)label);
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        float32 lineSize = ImGui::GetFontSize() + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineSize + 3.0f, lineSize };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.7f, 0.2f, 1.0f));
        ImGui::PushFont(boldFont);
        if (ImGui::Button("W", buttonSize))
            values.w = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##W", &values.w, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
    }

    template<typename T, typename F>
    static void DrawComponent(Entity& entity, const String& name, F uiFunction)
    {
        if (entity.HasComponent<T>())
        {
            auto flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow |
                         ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowOverlap |
                         ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;
            ImVec2 content = ImGui::GetContentRegionAvail();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 4.0f));
            float32 lineHeight = ImGui::GetFontSize() + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, (const char*)name);
            ImGui::PopStyleVar();
            ImGui::SameLine(content.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2(lineHeight, lineHeight)))
                ImGui::OpenPopup("ComponentSettings");
            bool remove = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove Component"))
                    remove = true;
                ImGui::EndPopup();
            }
            if (open)
            {
                uiFunction(entity.GetComponent<T>());
                ImGui::TreePop();
            }
            if (remove)
                entity.RemoveComponent<T>();
        }
    }

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
        {
            DrawComponents(m_selectedEntity);
            ImGui::Separator();
            if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");

            if (ImGui::BeginPopup("AddComponent"))
            {
                if (ImGui::MenuItem("Transform"))
                {
                    m_selectedEntity.AddComponent<TransformComponent>();
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Camera"))
                {
                    m_selectedEntity.AddComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sprite Renderer"))
                {
                    m_selectedEntity.AddComponent<SpriteComponent>();
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Native Script"))
                {
                    m_selectedEntity.AddComponent<NativeScriptComponent>();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    void InspectorPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<IDComponent>() && entity.HasComponent<TagComponent>())
        {
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, (const char*)entity.GetName());
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
                entity.SetName(buffer);
            ImGui::SameLine();
            ImGui::Text("0x%X", (uint64)entity.GetUUID());
        }

        DrawComponent<TransformComponent>(entity, "Transform", [&](auto& component)
        {
            DrawVec3Control("Translation", component.position);
            DrawVec3Control("Rotation", component.rotation);
            DrawVec3Control("Scale", component.scale, 1.0f);
        });

        DrawComponent<CameraComponent>(entity, "Camera", [&](auto& component)
        {
            const char* types[]     = { "Orthographic", "Perspective" };
            const char* currentType = types[(int32)component.camera->GetCameraType()];

            ImGui::Checkbox("Primary", &component.primary);
            ImGui::Checkbox("Fixed Aspect Ratio", &component.fixedRatio);
            if (ImGui::BeginCombo("Projection", currentType))
            {
                for (int32 i = 0; i < 2; ++i)
                {
                    bool selected = (currentType = types[i]);
                    if (ImGui::Selectable(types[i], selected))
                    {
                        currentType = types[i];
                        component.camera->SetCameraType((CameraType)i);
                    }
                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            switch (component.camera->GetCameraType())
            {
                case CameraType::Orthographic:
                {
                    float32 size = component.camera->GetOrthographicSize();
                    if (ImGui::DragFloat("Size", &size, 0.1f))
                        component.camera->SetOrthographicSize(size);
                    float32 near = component.camera->GetOrthographicNear();
                    if (ImGui::DragFloat("Near Clip", &near, 0.1f))
                        component.camera->SetOrthographicNear(near);
                    float32 far = component.camera->GetOrthographicFar();
                    if (ImGui::DragFloat("Far Clip", &far, 0.1f))
                        component.camera->SetOrthographicFar(far);
                    break;
                }
                case CameraType::Perspective:
                {
                    float32 fov = component.camera->GetPerspectiveFOV();
                    if (ImGui::DragFloat("Vertical FOV", &fov, 0.1f))
                        component.camera->SetPerspectiveFOV(fov);
                    float32 near = component.camera->GetPerspectiveNear();
                    if (ImGui::DragFloat("Near Clip", &near, 0.1f))
                        component.camera->SetPerspectiveNear(near);
                    float32 far = component.camera->GetPerspectiveFar();
                    if (ImGui::DragFloat("Far Clip", &far, 0.1f))
                        component.camera->SetPerspectiveFar(far);
                    break;
                }
            }
        });

        DrawComponent<SpriteComponent>(entity, "Sprite Renderer", [&](auto& component)
        {
            ImGui::Image(component.texture->GetTexture()->GetRenderId(), ImVec2(64, 64));
            DrawVec2Control("UV0", component.texture->GetTexCoords()[0]);
            DrawVec2Control("UV1", component.texture->GetTexCoords()[1], 1.0f);
            ImGui::DragFloat("Tiling Factor", &component.tilingFactor, 0.1f);
            Color color = { component.color.r / 255.0f, component.color.g / 255.0f, component.color.b / 255.0f, component.color.a };
            if (ImGui::ColorEdit4("Tint", glm::value_ptr(color), 0.1f))
                component.color = { color.r * 255, color.g * 255, color.b * 255, color.a };
        });

        DrawComponent<NativeScriptComponent>(entity, "Native Script", [&](auto& component)
        {
            ImGui::Text((const char*)component.className);
        });
    }
} // namespace Nt

#endif // _PANELS_INSPECTOR_PANEL_CPP_
