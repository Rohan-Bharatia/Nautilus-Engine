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

#ifndef _EDITOR_H_
    #define _EDITOR_H_

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/InspectorPanel.h"
#include "Panels/ConsolePanel.h"
#include "Panels/AssetBrowserPanel.h"

namespace Nt
{
    class NT_API EditorLayer :
        public Layer
    {
    public:
        EditorLayer(void);
        virtual ~EditorLayer(void) = default;

        virtual void OnAttach(void) override;
        virtual void OnUpdate(float32 deltaTime) override;
        virtual void OnGUIRender(float32 deltaTime) override;
        virtual void OnEvent(Event& event) override;

    private:
        bool OnWindowResize(WindowResizeEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);

        struct WindowStates
        {
            bool dockspace      = true;
            bool viewport       = true;
            bool sceneHierarchy = true;
            bool inspector      = true;
            bool console        = true;
            bool assetBrowser   = true;
            bool metrics        = true;
        };

        Vector2 m_viewportSize;
        Ref<Scene> m_activeScene;
        WindowStates m_windowStates;
        Ref<Framebuffer> m_framebuffer;
        SceneHierarchyPanel m_sceneHierarchyPanel;
        InspectorPanel m_inspectorPanel;
        ConsolePanel m_consolePanel;
        AssetBrowserPanel m_assetBrowserPanel;
    };
} // namespace Nt

#endif // _EDITOR_H_
