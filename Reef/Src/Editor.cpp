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

#ifndef _EDITOR_CPP_
    #define _EDITOR_CPP_

#include "Editor.h"

namespace Nt
{
    EditorLayer::EditorLayer(void) :
        Layer("EditorLayer"), m_viewportSize(0.0f, 0.0f), m_camera(60, 16.0f / 9.0f)
    {}

    void EditorLayer::OnAttach(void)
    {
        Application::Get().GetGUILayer()->BlockEvents(false);
        m_windowStates.dockspace = true;

        FramebufferTextureProps attc;
        attc.texture = FramebufferTextureFormat::RGBA8;
        attc.filter  = FramebufferFilterFormat::Linear;
        attc.wrap    = FramebufferWrapFormat::ClampToEdge;

        FramebufferProps props;
        props.width  = Application::Get().GetWindow().GetWidth();
        props.height = Application::Get().GetWindow().GetHeight();

        props.attachments.attachments.push_back(attc);

        m_framebuffer = CreateRef<Framebuffer>(props);
    }

    void EditorLayer::OnUpdate(float32 deltaTime)
    {
        if (FramebufferProps props = m_framebuffer->GetProps();
            m_viewportSize.x > 0.0f && m_viewportSize.y > 0.0f && (m_viewportSize.x != props.width || m_viewportSize.y != props.height))
        {
            m_framebuffer->Resize((uint32)m_viewportSize.x, (uint32)m_viewportSize.y);
            m_camera.SetViewportSize(m_viewportSize.x, m_viewportSize.y);
        }

        SceneRenderer::ResetStats();
        m_framebuffer->Bind();

        RenderCommand::SetClearColor(NT_COLOR_BLACK);
        RenderCommand::Clear();

        m_camera.OnUpdate(deltaTime);

        SceneRenderer::BeginScene(m_camera);
        SceneRenderer::DrawQuad({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, 0.0f, NT_COLOR_WHITE);
        SceneRenderer::EndScene();

        m_framebuffer->Unbind();
    }

    void EditorLayer::OnGUIRender(float32 deltaTime)
    {
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags windowFlags             = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (m_windowStates.dockspace)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                           ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Dockspace Demo", &m_windowStates.dockspace, windowFlags);
        ImGui::PopStyleVar();

        if (m_windowStates.dockspace)
            ImGui::PopStyleVar(2);

        ImGuiIO& io       = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

        float32 minWinX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;

        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID("MyDockspace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
        }

        style.WindowMinSize.x = minWinX;

        if (ImGui::BeginMenuBar())
        {
            ImGui::Separator();
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("Open Scene", "Ctrl+O");
                ImGui::Separator();
                ImGui::MenuItem("New Scene", "Ctrl+N");
                ImGui::MenuItem("Save Scene", "Ctrl+S");
                ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S");
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Ctrl+Q"))
                    Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::MenuItem("Undo", "Ctrl+Z");
                ImGui::MenuItem("Redo", "Ctrl+Y");
                ImGui::Separator();
                ImGui::MenuItem("Cut", "Ctrl+X");
                ImGui::MenuItem("Copy", "Ctrl+C");
                ImGui::MenuItem("Paste", "Ctrl+V");
                ImGui::MenuItem("Duplicate", "Ctrl+D");
                ImGui::MenuItem("Delete", "Del");
                ImGui::Separator();
                ImGui::MenuItem("Preferences", "Ctrl+,");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("View"))
            {
                ImGui::MenuItem("Reset Layout");
                if (ImGui::MenuItem("Toggle Fullscreen", "F11"))
                    Application::Get().GetWindow().SetFullscreen(!Application::Get().GetWindow().IsFullscreen());
                ImGui::Separator();
                ImGui::MenuItem("Show Grid");
                ImGui::MenuItem("Show Gizmos");
                ImGui::MenuItem("Show Colliders");
                ImGui::MenuItem("Show Lights");
                ImGui::Separator();
                ImGui::MenuItem("Focus Selected", "F");
                ImGui::MenuItem("Frame All", "Shift+F");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Create"))
            {
                ImGui::MenuItem("Empty Object");
                ImGui::MenuItem("Camera");
                ImGui::MenuItem("Light");
                ImGui::Separator();
                if (ImGui::BeginMenu("Primitives"))
                {
                    ImGui::MenuItem("Cube");
                    ImGui::MenuItem("Sphere");
                    ImGui::MenuItem("Cylinder");
                    ImGui::MenuItem("Capsule");
                    ImGui::MenuItem("Plane");
                    ImGui::MenuItem("Cone");
                    ImGui::MenuItem("Torus");
                    ImGui::EndMenu();
                }
                ImGui::MenuItem("3D Model");
                ImGui::MenuItem("Sprite");
                ImGui::MenuItem("UI Canvas");
                ImGui::MenuItem("Text");
                ImGui::MenuItem("Audio Source");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Assets"))
            {
                ImGui::MenuItem("Import Asset", "Ctrl+I");
                ImGui::MenuItem("Reimport All");
                ImGui::MenuItem("Export Selected", "Ctrl+E");
                ImGui::MenuItem("Export All", "Ctrl+Shift+E");
                ImGui::Separator();
                ImGui::MenuItem("Open in File Explorer");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Build"))
            {
                ImGui::MenuItem("Build Project", "Ctrl+B");
                ImGui::MenuItem("Build And Run", "Ctrl+Shift+B");
                ImGui::MenuItem("Clean Project", "Ctrl+Shift+C");
                ImGui::Separator();
                ImGui::MenuItem("Project Settings", "Ctrl+P");
                ImGui::MenuItem("Scene Settings", "Ctrl+Shift+P");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Play"))
            {
                ImGui::MenuItem("Play / Stop", "Ctrl+R");
                ImGui::MenuItem("Pause", "Ctrl+Shift+R");
                ImGui::MenuItem("Step Frame", "F10");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::MenuItem("Viewport", "", &m_windowStates.viewport);
                ImGui::MenuItem("Scene Hierarchy", "", &m_windowStates.sceneHierarchy);
                ImGui::MenuItem("Inspector", "", &m_windowStates.inspector);
                ImGui::MenuItem("Console", "", &m_windowStates.console);
                ImGui::MenuItem("Asset Browser", "", &m_windowStates.assetBrowser);
                ImGui::MenuItem("Metrics", "", &m_windowStates.metrics);
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Documentation"))
                    OpenURL("https://github.com/Rohan-Bharatia/Nautilus-Engine/wiki");
                if (ImGui::MenuItem("About"))
                    OpenURL("https://github.com/Rohan-Bharatia/Nautilus-Engine/blob/main/README.md");
                if (ImGui::MenuItem("Report Issue"))
                    OpenURL("https://github.com/Rohan-Bharatia/Nautilus-Engine/issues/new");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            ImGui::EndMenuBar();
        }

        ImGui::End();

        if (m_windowStates.viewport)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("Viewport");
            Application::Get().GetGUILayer()->BlockEvents(!ImGui::IsWindowHovered());
            m_viewportSize = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };
            ImGui::Image(ImTextureRef((void*)(uint64)m_framebuffer->GetColorAttachmentRenderId(0)), ImVec2(m_viewportSize.x, m_viewportSize.y));
            ImGui::End();
            ImGui::PopStyleVar();
        }

        if (m_windowStates.sceneHierarchy)
            m_sceneHierarchyPanel.Display();

        if (m_windowStates.inspector)
            m_inspectorPanel.Display();

        if (m_windowStates.console)
            m_consolePanel.Display();

        if (m_windowStates.assetBrowser)
            m_assetBrowserPanel.Display();

        if (m_windowStates.metrics)
        {
            auto stats = SceneRenderer::GetStats();

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.8f);
            ImGui::Begin("Metrics");
            ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, 1.0f / deltaTime);
            ImGui::Separator();
            ImGui::BeginChild("Renderer Stats");
            ImGui::Text("Draw Calls: %d", stats.drawCalls);
            ImGui::Text("Triangles: %d", stats.quadCount * 2);
            ImGui::EndChild();
            ImGui::End();
            ImGui::PopStyleVar();
        }
    }

    void EditorLayer::OnEvent(Event& event)
    {
        m_camera.OnEvent(event);

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(NT_BIND_EVENT_FN(EditorLayer::OnWindowResize));
        dispatcher.Dispatch<KeyPressedEvent>(NT_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
    }

    bool EditorLayer::OnWindowResize(WindowResizeEvent& e)
    {
        RendererAPI::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        bool ctrl          = Input::IsKeyPressed(Keycode::LeftControl) || Input::IsKeyPressed(Keycode::RightControl);
        bool shift         = Input::IsKeyPressed(Keycode::LeftShift) || Input::IsKeyPressed(Keycode::RightShift);
        bool alt           = Input::IsKeyPressed(Keycode::LeftAlt) || Input::IsKeyPressed(Keycode::RightAlt);
        switch (e.GetKeyCode())
        {
            case Keycode::Q:
                if (ctrl)
                    Application::Get().Close();
                break;
            case Keycode::F11:
                Application::Get().GetWindow().SetFullscreen(!Application::Get().GetWindow().IsFullscreen());
                break;
            case Keycode::Escape:
                ImGui::FocusWindow(NULL);
                break;
            default:
                break;
        }
        return false;
    }
} // namespace Nt

#endif // _EDITOR_CPP_
