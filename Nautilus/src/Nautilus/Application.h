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

#pragma once

#ifndef _NT_NAUTILUS_APPLICATION_H_
    #define _NT_NAUTILUS_APPLICATION_H_

#include "PCH.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"

#define NT_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Nt
{
    class NT_API Application
    {
    public:
        Application();
        virtual ~Application();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        void Run();

        void OnEvent(Event& e);

        static Application& Get();
        Window& GetWindow();

    private:
        std::shared_ptr<Window> m_window;
        bool m_isRunning;
        LayerStack m_layerStack;
        ImGuiLayer* m_imguiLayer;
        Timestep m_timestep;
        float m_lastFrameTime;

        static Application* s_instance;

        bool OnWindowClose(WindowCloseEvent& e);
    };

    // *Defined by the client*
    Application* CreateApplication();
} // namespace Nt

#endif // _NT_NAUTILUS_APPLICATION_H_
