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
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
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
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
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
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.7f, 0.2f, 1.0f));
        if (ImGui::Button("W", buttonSize))
            values.w = resetValue;
        ImGui::SameLine();
        ImGui::DragFloat("##W", &values.w, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
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

        auto flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (entity.HasComponent<TransformComponent>())
        {
            ImGui::Separator();
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), flags, "Transform"))
            {
                auto& transform = entity.GetComponent<TransformComponent>();

                DrawVec3Control("Translation", transform.position);
                DrawVec3Control("Rotation", transform.rotation);
                DrawVec3Control("Scale", transform.scale, 1.0f);
                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<CameraComponent>())
        {
            ImGui::Separator();
            if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), flags, "Camera"))
            {
                auto& camera             = entity.GetComponent<CameraComponent>();
                SceneCamera& sceneCamera = NT_REINTERPRET_CAST(SceneCamera&, *camera.camera.get());
                const char* types[]      = { "Orthographic", "Perspective" };
                const char* currentType  = types[(int32)sceneCamera.GetCameraType()];

                ImGui::Checkbox("Primary", &camera.primary);
                ImGui::Checkbox("Fixed Aspect Ratio", &camera.fixedRatio);
                if (ImGui::BeginCombo("Projection", currentType))
                {
                    for (int32 i = 0; i < 2; ++i)
                    {
                        bool selected = (currentType = types[i]);
                        if (ImGui::Selectable(types[i], selected))
                        {
                            currentType = types[i];
                            sceneCamera.SetCameraType((CameraType)i);
                        }
                        if (selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                switch (sceneCamera.GetCameraType())
                {
                    case CameraType::Orthographic:
                    {
                        float32 size = sceneCamera.GetOrthographicSize();
                        if (ImGui::DragFloat("Size", &size, 0.1f))
                            sceneCamera.SetOrthographicSize(size);
                        float32 near = sceneCamera.GetOrthographicNear();
                        if (ImGui::DragFloat("Near Clip", &near, 0.1f))
                            sceneCamera.SetOrthographicNear(near);
                        float32 far = sceneCamera.GetOrthographicFar();
                        if (ImGui::DragFloat("Far Clip", &far, 0.1f))
                            sceneCamera.SetOrthographicFar(far);
                        break;
                    }
                    case CameraType::Perspective:
                    {
                        float32 fov = sceneCamera.GetPerspectiveFOV();
                        if (ImGui::DragFloat("Vertical FOV", &fov, 0.1f))
                            sceneCamera.SetPerspectiveFOV(fov);
                        float32 near = sceneCamera.GetPerspectiveNear();
                        if (ImGui::DragFloat("Near Clip", &near, 0.1f))
                            sceneCamera.SetPerspectiveNear(near);
                        float32 far = sceneCamera.GetPerspectiveFar();
                        if (ImGui::DragFloat("Far Clip", &far, 0.1f))
                            sceneCamera.SetPerspectiveFar(far);
                        break;
                    }
                }
                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<SpriteComponent>())
        {
            ImGui::Separator();
            if (ImGui::TreeNodeEx((void*)typeid(SpriteComponent).hash_code(), flags, "Sprite"))
            {
                auto& sprite = entity.GetComponent<SpriteComponent>();

                ImGui::Image(sprite.texture->GetTexture()->GetRenderId(), ImVec2(64, 64));
                if (ImGui::TreeNodeEx((void*)typeid(SpriteComponent).hash_code(), flags, "Texture Coordinates"))
                {
                    DrawVec2Control("UV0", sprite.texture->GetTexCoords()[0]);
                    DrawVec2Control("UV1", sprite.texture->GetTexCoords()[1], 1.0f);
                    ImGui::TreePop();
                }
                ImGui::DragFloat("Tiling Factor", &sprite.tilingFactor, 0.1f);
                Color color = { sprite.color.r / 255.0f, sprite.color.g / 255.0f, sprite.color.b / 255.0f, sprite.color.a };
                if (ImGui::ColorEdit4("Tint", glm::value_ptr(color), 0.1f))
                    sprite.color = { color.r * 255, color.g * 255, color.b * 255, color.a };
                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<NativeScriptComponent>())
        {
            ImGui::Separator();
            if (ImGui::TreeNodeEx((void*)typeid(NativeScriptComponent).hash_code(), flags, "Native Script"))
            {
                auto& script = entity.GetComponent<NativeScriptComponent>();

                ImGui::Text((const char*)script.className);
                ImGui::TreePop();
            }
        }
    }
} // namespace Nt

#endif // _PANELS_INSPECTOR_PANEL_CPP_
