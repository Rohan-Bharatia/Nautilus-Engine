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

#ifndef _SBX_SANDBOX_CPP_
    #define _SBX_SANDBOX_CPP_

#include <Nautilus.h>

class SandboxLayer :
    public Nt::Layer
{
public:
    SandboxLayer() :
        Layer("Sandbox"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f), m_cameraRotation(0.0f),
        m_cameraPositionSpeed(7.5f), m_cameraRotationSpeed(180.0f), m_quadPosition(0.0f)
    {
        m_triangleVAO.reset(Nt::VertexArray::Create());

        float triangleVertices[21] =
        {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };

        std::shared_ptr<Nt::VertexBuffer> triangleVBO;
        triangleVBO.reset(Nt::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

        Nt::BufferLayout triangleLayout =
        {
            Nt::BufferElement{ Nt::ShaderDataType::Float3, "aPosition" },
            Nt::BufferElement{ Nt::ShaderDataType::Float4, "aColor" },
        };

        triangleVBO->SetLayout(triangleLayout);
        m_triangleVAO->AddVertexBuffer(triangleVBO);

        GLuint triangleIndices[3] = { 0, 1, 2 };

        std::shared_ptr<Nt::IndexBuffer> triangleIBO;
        triangleIBO.reset(Nt::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
        m_triangleVAO->SetIndexBuffer(triangleIBO);

        m_quadVAO.reset(Nt::VertexArray::Create());

        float quadVertices[12] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };

        std::shared_ptr<Nt::VertexBuffer> quadVBO;
        quadVBO.reset(Nt::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));

        Nt::BufferLayout quadLayout =
        {
            Nt::BufferElement{ Nt::ShaderDataType::Float3, "aPosition" },
        };

        quadVBO->SetLayout(quadLayout);
        m_quadVAO->AddVertexBuffer(quadVBO);

        uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<Nt::IndexBuffer> quadIBO;
        quadIBO.reset(Nt::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
        m_quadVAO->SetIndexBuffer(quadIBO);

        std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec4 aColor;

            uniform mat4 uViewProjection;
            uniform mat4 uTransform;

            out vec3 vPosition;
            out vec4 vColor;

            void main()
            {
                vPosition   = aPosition;
                vColor      = aColor;
                gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0f);
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

        m_triangleShader.reset(Nt::Shader::Create(vertexSource, fragmentSource));

        std::string vertexSource2 = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;

            uniform mat4 uViewProjection;
            uniform mat4 uTransform;

            out vec3 vPosition;

            void main()
            {
                vPosition   = aPosition;
                gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0f);
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

        m_quadShader.reset(Nt::Shader::Create(vertexSource2, fragmentSource2));
    }

    ~SandboxLayer()
    {
        m_triangleVAO.reset();
        m_triangleShader.reset();
        m_quadVAO.reset();
        m_quadShader.reset();
    }

    void OnUpdate(Nt::Timestep ts) override
    {
        // WASD camera movement
        if (Nt::Input::IsKeyPressed(NT_KEY_D))
            m_cameraPosition.x += m_cameraPositionSpeed * ts;
        else if (Nt::Input::IsKeyPressed(NT_KEY_A))
            m_cameraPosition.x -= m_cameraPositionSpeed * ts;
        if (Nt::Input::IsKeyPressed(NT_KEY_W))
            m_cameraPosition.y += m_cameraPositionSpeed * ts;
        else if (Nt::Input::IsKeyPressed(NT_KEY_S))
            m_cameraPosition.y -= m_cameraPositionSpeed * ts;

        // QE camera rotation
        if (Nt::Input::IsKeyPressed(NT_KEY_Q))
            m_cameraRotation -= m_cameraRotationSpeed * ts;
        else if (Nt::Input::IsKeyPressed(NT_KEY_E))
            m_cameraRotation += m_cameraRotationSpeed * ts;

        // R to reset
        if (Nt::Input::IsKeyPressed(NT_KEY_R))
        {
            m_cameraPosition = { 0.0f, 0.0f, 0.0f };
            m_cameraRotation = 0.0f;
        }

        Nt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Nt::RenderCommand::Clear();

        m_camera.SetPosition(m_cameraPosition);
        m_camera.SetRotation(m_cameraRotation);

        Nt::Renderer::BeginScene(m_camera);

            static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            for (int x = 0; x < 10; ++x)
            {
                for (int y = 0; y < 10; ++y)
                {
                    glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                    Nt::Renderer::Submit(m_quadShader, m_quadVAO, transform);
                }
            }

            Nt::Renderer::Submit(m_triangleShader, m_triangleVAO);
        Nt::Renderer::EndScene();
    }

    void OnEvent(Nt::Event& event) override
    {}

private:
    std::shared_ptr<Nt::VertexArray> m_triangleVAO;
    std::shared_ptr<Nt::Shader> m_triangleShader;
    std::shared_ptr<Nt::VertexArray> m_quadVAO;
    std::shared_ptr<Nt::Shader> m_quadShader;
    glm::vec3 m_quadPosition;
    Nt::OrthographicCamera m_camera;
    glm::vec3 m_cameraPosition;
    float m_cameraPositionSpeed;
    float m_cameraRotation;
    float m_cameraRotationSpeed;
};

class SandboxApplication :
    public Nt::Application
{
public:
    SandboxApplication()
    {
        PushLayer(new SandboxLayer());
    }

    ~SandboxApplication()
    {}
};

Nt::Application* Nt::CreateApplication()
{
    return new SandboxApplication();
}

#endif // _SBX_SANDBOX_CPP_
