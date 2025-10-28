#ifndef _SANDBOX_CPP_
    #define _SANDBOX_CPP_

#include <Nautilus.h>
#include <EntryPoint.h>

class SandboxLayer :
    public Nt::Layer
{
public:
    SandboxLayer(void) :
        Layer("SandboxLayer")
    {}

    ~SandboxLayer(void)
    {}

    virtual void OnAttach(void) override
    {
        glEnable(GL_DEPTH_TEST);

        static Nt::float32 vertices[] =
        {
            //  x      y     z     r     g     b     a
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };
        static Nt::uint32 indices[]   = { 0, 1, 2 };

        m_vao = Nt::CreateRef<Nt::VertexArray>();

        Nt::Ref<Nt::VertexBuffer> vbo = Nt::CreateRef<Nt::VertexBuffer>(vertices, sizeof(vertices));
        vbo->SetLayout({
            { Nt::ShaderDataType::Float3, "a_position" },
            { Nt::ShaderDataType::Float4, "a_color" }
        });
        m_vao->AddVertexBuffer(vbo);

        Nt::Ref<Nt::IndexBuffer> ibo = Nt::CreateRef<Nt::IndexBuffer>(indices, sizeof(indices));
        m_vao->SetIndexBuffer(ibo);

        static Nt::String vsSource = R"(#version 460 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_color;

layout(location=0) out vec4 v_color;

void main()
{
    gl_Position = vec4(a_position, 1.0);
    v_color     = a_color;
}
)";
        static Nt::String fsSource = R"(#version 460 core

layout (location = 0) in vec4 v_color;

layout (location = 0) out vec4 o_color;

void main()
{
    o_color = v_color;
}
)";

        m_program = Nt::CreateRef<Nt::Shader>("triangle", vsSource, fsSource);
        m_program->Bind();

        glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
        glScissor(0, 0, m_window.GetWidth(), m_window.GetHeight());
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
        glScissor(0, 0, m_window.GetWidth(), m_window.GetHeight());

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(m_vao->GetRenderId());
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

private:
    Nt::Window& m_window = Nt::Application::Get().GetWindow();

    Nt::Ref<Nt::VertexArray> m_vao;
    Nt::Ref<Nt::Shader> m_program;
};

class SandboxApplication :
    public Nt::Application
{
public:
    SandboxApplication(Nt::int32 argc, char* argv[]) :
        Application(argc, argv)
    {
        PushLayer(new SandboxLayer());
    }

    ~SandboxApplication(void)
    {}
};

Nt::Application* Nt::CreateApplication(Nt::int32 argc, char* argv[])
{
    return new SandboxApplication(argc, argv);
}

#endif // _SANDBOX_CPP_
