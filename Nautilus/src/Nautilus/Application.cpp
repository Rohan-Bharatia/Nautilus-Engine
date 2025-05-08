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
#include "Renderer/Renderer.h"

#define NT_BIND_APPLICATION_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Nt
{
    Application* Application::s_instance = nullptr;

    Application::Application() :
        m_window(std::unique_ptr<Window>(Window::Create(WindowProps{}))), m_isRunning(true), m_imguiLayer(new ImGuiLayer())
    {
        NT_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window->SetEventCallback(NT_BIND_APPLICATION_EVENT_FN(OnEvent));

        PushOverlay(m_imguiLayer);

        m_triangleVAO.reset(VertexArray::Create());

        float triangleVertices[21] =
        {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };

        std::shared_ptr<VertexBuffer> triangleVBO;
        triangleVBO.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

        BufferLayout layout =
        {
            BufferElement{ ShaderDataType::Float3, "aPosition" },
            BufferElement{ ShaderDataType::Float4, "aColor" },
        };

        triangleVBO->SetLayout(layout);
        m_triangleVAO->AddVertexBuffer(triangleVBO);

        GLuint triangleIndices[3] = { 0, 1, 2 };

        std::shared_ptr<IndexBuffer> triangleIBO;
        triangleIBO.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
        m_triangleVAO->SetIndexBuffer(triangleIBO);

        m_quadVAO.reset(VertexArray::Create());

        float quadVertices[12] =
        {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
        };

        std::shared_ptr<VertexBuffer> quadVBO;
        quadVBO.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));

        BufferLayout quadLayout =
        {
            BufferElement{ ShaderDataType::Float3, "aPosition" },
        };

        quadVBO->SetLayout(quadLayout);
        m_quadVAO->AddVertexBuffer(quadVBO);

        uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<IndexBuffer> quadIBO;
        quadIBO.reset(IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
        m_quadVAO->SetIndexBuffer(quadIBO);

        std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec4 aColor;

            out vec3 vPosition;
            out vec4 vColor;

            void main()
            {
                vPosition   = aPosition;
                vColor      = aColor;
                gl_Position = vec4(aPosition, 1.0f);
            }
        )";

        std::string fragmentSource = R"(
            #version 330 core

            layout(location = 0) out vec4 FragColor;

            in vec3 vPosition;
            in vec4 vColor;

            void main()
            {
                FragColor = vec4(vPosition * 0.5f + 0.5f, 1.0f);
                FragColor = vColor;
            }
        )";

        m_triangleShader.reset(Shader::Create(vertexSource, fragmentSource));

        std::string vertexSource2 = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;

            out vec3 vPosition;

            void main()
            {
                vPosition   = aPosition;
                gl_Position = vec4(aPosition, 1.0f);
            }
        )";

        std::string fragmentSource2 = R"(
            #version 330 core

            layout(location = 0) out vec4 FragColor;

            in vec3 vPosition;

            void main()
            {
                FragColor = vec4(0.2f, 0.3f, 0.3f, 1.0f);
            }
        )";

        m_quadShader.reset(Shader::Create(vertexSource2, fragmentSource2));
    }

    Application::~Application()
    {
        m_window.reset();
        m_triangleVAO.reset();
        m_triangleShader.reset();
        m_quadVAO.reset();
        m_quadShader.reset();
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
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene();
                m_quadShader->Bind();
                Renderer::Submit(m_quadVAO);

                m_triangleShader->Bind();
                Renderer::Submit(m_triangleVAO);
            Renderer::EndScene();

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
