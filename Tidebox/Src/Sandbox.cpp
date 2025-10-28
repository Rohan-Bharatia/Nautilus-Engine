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

        m_program = Nt::CreateRef<Nt::Shader>("triangle", Nt::ReadFile("Assets/Shaders/triangle_vs.glsl"), Nt::ReadFile("Assets/Shaders/triangle_fs.glsl"));
        m_program->Bind();

        Nt::RenderCommand::SetViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
        Nt::RenderCommand::SetScissor(0, 0, m_window.GetWidth(), m_window.GetHeight());
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        Nt::RenderCommand::SetViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
        Nt::RenderCommand::SetScissor(0, 0, m_window.GetWidth(), m_window.GetHeight());

        Nt::RenderCommand::SetClearColor(NT_COLOR_DARK_GRAY);
        Nt::RenderCommand::Clear();

        Nt::RenderCommand::DrawFillIndexed(m_vao);
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
