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

#ifndef _GUI_GUI_LAYER_CPP_
    #define _GUI_GUI_LAYER_CPP_

#include "GUILayer.h"

#include "Core/Application.h"

namespace Nt
{
    GUILayer::GUILayer(void) :
        Layer("GUILayer"), m_blockEvents(true)
    {}

    void GUILayer::OnAttach(void)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io     = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.FontDefault  = io.Fonts->AddFontFromFileTTF("Assets/Fonts/Noto_Sans/NotoSans-VariableFont_wdth,wght.ttf", 18.0f);

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding              = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        SetDarkThemeColors();

        ImGui_ImplSDL3_InitForOpenGL((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), Application::Get().GetWindow().GetNativeContext());
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void GUILayer::OnGUIRender(float32 deltaTime)
    {
        bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void GUILayer::OnDetach(void)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void GUILayer::OnEvent(Event& event)
    {
        if (m_blockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            event.SetHandled(event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse);
            event.SetHandled(event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard);
        }
    }

    void GUILayer::Begin(void)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void GUILayer::End(void)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float32)Application::Get().GetWindow().GetWidth(),
                                (float32)Application::Get().GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backupCurrentWindow = SDL_GL_GetCurrentWindow();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backupCurrentWindow, nullptr);
        }
    }

    void GUILayer::BlockEvents(bool block)
    {
        m_blockEvents = block;
    }

    uint32 GUILayer::GetActiveWidgetId(void) const
    {
        return GImGui->ActiveId;
    }

    void GUILayer::SetDarkThemeColors(void)
    {
        auto& colors = ImGui::GetStyle().Colors;

        // Core Backgrounds
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };
        colors[ImGuiCol_ChildBg]  = ImVec4{ 0.06f, 0.07f, 0.09f, 0.0f };
        colors[ImGuiCol_PopupBg]  = ImVec4{ 0.08f, 0.09f, 0.12f, 0.98f };

        // Borders & Separators
        colors[ImGuiCol_Border]           = ImVec4{ 0.043f, 0.059f, 0.557f, 0.5f };
        colors[ImGuiCol_BorderShadow]     = ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };
        colors[ImGuiCol_Separator]        = ImVec4{ 0.043f, 0.059f, 0.557f, 0.4f };
        colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.7f };
        colors[ImGuiCol_SeparatorActive]  = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Text
        colors[ImGuiCol_Text]         = ImVec4{ 0.85f, 0.88f, 0.95f, 1.0f };
        colors[ImGuiCol_TextDisabled] = ImVec4{ 0.50f, 0.52f, 0.55f, 1.0f };

        // Headers
        colors[ImGuiCol_Header]        = ImVec4{ 0.10f, 0.11f, 0.15f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.85f };
        colors[ImGuiCol_HeaderActive]  = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Buttons
        colors[ImGuiCol_Button]        = ImVec4{ 0.10f, 0.11f, 0.15f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.85f };
        colors[ImGuiCol_ButtonActive]  = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Frame BG (Inputs, Sliders, etc.)
        colors[ImGuiCol_FrameBg]        = ImVec4{ 0.12f, 0.13f, 0.16f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.85f };
        colors[ImGuiCol_FrameBgActive]  = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Tabs
        colors[ImGuiCol_Tab]                = ImVec4{ 0.08f, 0.09f, 0.12f, 1.0f };
        colors[ImGuiCol_TabHovered]         = ImVec4{ 0.043f, 0.059f, 0.557f, 0.85f };
        colors[ImGuiCol_TabActive]          = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };
        colors[ImGuiCol_TabUnfocused]       = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.10f, 0.11f, 0.15f, 1.0f };

        // Title Bars
        colors[ImGuiCol_TitleBg]          = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };
        colors[ImGuiCol_TitleBgActive]    = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };

        // Menus
        colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.07f, 0.08f, 0.10f, 1.0f };

        // Scrollbars
        colors[ImGuiCol_ScrollbarBg]          = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };
        colors[ImGuiCol_ScrollbarGrab]        = ImVec4{ 0.12f, 0.13f, 0.16f, 1.0f };
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.85f };
        colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Check Marks, Radio Buttons, Sliders, etc.
        colors[ImGuiCol_CheckMark]        = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };
        colors[ImGuiCol_SliderGrab]       = ImVec4{ 0.043f, 0.059f, 0.557f, 0.9f };
        colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Resize Grips
        colors[ImGuiCol_ResizeGrip]        = ImVec4{ 0.043f, 0.059f, 0.557f, 0.2f };
        colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.7f };
        colors[ImGuiCol_ResizeGripActive]  = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Docking
        colors[ImGuiCol_DockingPreview] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.7f };
        colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.04f, 0.05f, 0.07f, 1.0f };

        // Plots
        colors[ImGuiCol_PlotLines]            = ImVec4{ 0.043f, 0.059f, 0.557f, 0.7f };
        colors[ImGuiCol_PlotLinesHovered]     = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };
        colors[ImGuiCol_PlotHistogram]        = ImVec4{ 0.043f, 0.059f, 0.557f, 0.9f };
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Tables
        colors[ImGuiCol_TableHeaderBg]     = ImVec4{ 0.08f, 0.09f, 0.12f, 1.0f };
        colors[ImGuiCol_TableBorderStrong] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.7f };
        colors[ImGuiCol_TableBorderLight]  = ImVec4{ 0.043f, 0.059f, 0.557f, 0.3f };
        colors[ImGuiCol_TableRowBg]        = ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };
        colors[ImGuiCol_TableRowBgAlt]     = ImVec4{ 0.06f, 0.07f, 0.09f, 0.4f };

        // Drag & Drop
        colors[ImGuiCol_DragDropTarget] = ImVec4{ 0.043f, 0.059f, 0.557f, 1.0f };

        // Nav Highlight (Keyboard/Gamepad)
        colors[ImGuiCol_NavHighlight]          = ImVec4{ 0.043f, 0.059f, 0.557f, 0.8f };
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4{ 0.043f, 0.059f, 0.557f, 0.7f };
        colors[ImGuiCol_NavWindowingDimBg]     = ImVec4{ 0.06f, 0.07f, 0.09f, 0.6f };
        colors[ImGuiCol_ModalWindowDimBg]      = ImVec4{ 0.06f, 0.07f, 0.09f, 0.6f };
    }
} // namespace Nt

#endif // _GUI_GUI_LAYER_CPP_
