#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                                 ...
//
//                  Copyright (c) Rohan Bharatia 2025

#pragma endregion LICENSE

#ifndef _NT_NAUTILUS_IMGUI_IMGUI_LAYER_CPP_
    #define _NT_NAUTILUS_IMGUI_IMGUI_LAYER_CPP_

#include "ImGuiLayer.h"

#include "Nautilus/Application.h"

namespace Nt
{
    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer"), m_time(0.0f)
    {}

    ImGuiLayer::~ImGuiLayer()
    {}

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImGuiLayer::OnUpdate()
    {
        Application& app = Application::Get();
        ImGuiIO& io      = ImGui::GetIO();
        io.DisplaySize   = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        float time   = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : 1.0f / 60.0f;
        m_time       = time;

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnDetach()
    {}

    void ImGuiLayer::OnEvent(Event& event)
    {}
} // namespace Nt

#endif // _NT_NAUTILUS_IMGUI_IMGUI_LAYER_CPP_
