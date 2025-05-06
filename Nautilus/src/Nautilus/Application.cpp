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

#ifndef _NT_NAUTILUS_APPLICATION_CPP_
    #define _NT_NAUTILUS_APPLICATION_CPP_

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Input.h"

#define NT_BIND_APPLICATION_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Nt
{
    Application* Application::s_instance = nullptr;

    Application::Application() :
        m_window(std::unique_ptr<Window>(Window::Create(WindowProps{}))), m_isRunning(true), m_imguiLayer(new ImGuiLayer()),
        m_VAO(0)
    {
        NT_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window->SetEventCallback(NT_BIND_APPLICATION_EVENT_FN(OnEvent));

        PushOverlay(m_imguiLayer);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        float vertices[9] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        // m_VBO->Bind();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        GLuint indices[3] = { 0, 1, 2 };

        m_IBO.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        // m_IBO->Bind();

        std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;

            out vec3 vColor;

            void main()
            {
                vColor      = aPosition;
                gl_Position = vec4(vColor, 1.0f);
            }
        )";

        std::string fragmentSource = R"(
            #version 330 core

            layout(location = 0) out vec4 FragColor;

            in vec3 vColor;

            void main()
            {
                FragColor = vec4(vColor * 0.5f + 0.5f, 1.0f);
            }
        )";

        m_shader.reset(Shader::Create(vertexSource, fragmentSource));
    }

    Application::~Application()
    {
        m_window.reset();
        m_VBO.reset();
        m_IBO.reset();
        m_shader.reset();
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Run()
    {
        while (m_isRunning)
        {
            // Clear the window with OpenGL
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->Bind();
            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_layerStack)
                layer->OnUpdate();

            m_imguiLayer->Begin();
            for (Layer* layer : m_layerStack)
                layer->OnImGuiRender();
            m_imguiLayer->End();

            m_window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(NT_BIND_APPLICATION_EVENT_FN(OnWindowClose));

        NT_CORE_LOG_TRACE(e.ToString());

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.IsHandled())
                break;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_isRunning = false;
        return true;
    }

    Application& Application::Get()
    {
        return *s_instance;
    }

    Window& Application::GetWindow()
    {
        return *m_window;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_APPLICATION_CPP_
