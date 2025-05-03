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

#include <imgui/backends/imgui_impl_glfw.h>

#define NT_BIND_IMGUI_LAYER_EVENT_FN(x) std::bind(&ImGuiLayer::x, this, std::placeholders::_1)

#define NT_ADD_SPECIAL_KEY_START(k) if(e.GetKeyCode() == k) io.KeysData[k].Down = true;
#define NT_ADD_SPECIAL_KEY_CONT(k) else if(e.GetKeyCode() == k) io.KeysData[k].Down = true;
#define NT_ADD_SPECIAL_KEY_END() else io.KeysData[e.GetKeyCode()].Down = true;

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
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnKeyTypedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnMouseScrolledEvent));
        dispatcher.Dispatch<WindowResizeEvent>(NT_BIND_IMGUI_LAYER_EVENT_FN(OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io                      = ImGui::GetIO();
        io.KeysData[e.GetKeyCode()].Down = true;
        io.KeyCtrl                       = io.KeysData[GLFW_KEY_LEFT_CONTROL].Down || io.KeysData[GLFW_KEY_RIGHT_CONTROL].Down;
        io.KeyShift                      = io.KeysData[GLFW_KEY_LEFT_SHIFT].Down   || io.KeysData[GLFW_KEY_RIGHT_SHIFT].Down;
        io.KeyAlt                        = io.KeysData[GLFW_KEY_LEFT_ALT].Down     || io.KeysData[GLFW_KEY_RIGHT_ALT].Down;
        io.KeySuper                      = io.KeysData[GLFW_KEY_LEFT_SUPER].Down   || io.KeysData[GLFW_KEY_RIGHT_SUPER].Down;

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io                      = ImGui::GetIO();
        io.KeysData[e.GetKeyCode()].Down = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        if (e.GetKeyCode() > 0 && e.GetKeyCode() < 0x10000)
            io.AddInputCharacter((unsigned short)e.GetKeyCode());

        return false;
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io                      = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io                      = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io     = ImGui::GetIO();
        io.MouseWheelH += e.GetOffsetX();
        io.MouseWheel  += e.GetOffsetY();

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io                = ImGui::GetIO();
        io.DisplaySize             = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); // (width / width, height / height)

        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_IMGUI_IMGUI_LAYER_CPP_
