#ifndef _SANDBOX_CPP_
    #define _SANDBOX_CPP_

#include <Nautilus.h>
#include <EntryPoint.h>

class SandboxLayer :
    public Nt::Layer
{
public:
    SandboxLayer(void) :
        Layer("SandboxLayer"), m_camera(-1.0f, 1.0f, -1.0f, 1.0f)
    {}

    ~SandboxLayer(void)
    {}

    virtual void OnAttach(void) override
    {
        static Nt::float32 vertices[] =
        {
            //  x      y     z     r     g     b     a     u     v
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        };
        static Nt::uint32 indices[]   = { 0, 1, 2, 2, 3, 0 };

        m_vao = Nt::CreateRef<Nt::VertexArray>();

        Nt::Ref<Nt::VertexBuffer> vbo = Nt::CreateRef<Nt::VertexBuffer>(vertices, sizeof(vertices));
        vbo->SetLayout({
            { Nt::ShaderDataType::Float3, "a_position" },
            { Nt::ShaderDataType::Float4, "a_color" },
            { Nt::ShaderDataType::Float2, "a_texCoord" },
        });
        m_vao->AddVertexBuffer(vbo);

        Nt::Ref<Nt::IndexBuffer> ibo = Nt::CreateRef<Nt::IndexBuffer>(indices, NT_ARRAY_COUNT(indices));
        m_vao->SetIndexBuffer(ibo);

        Nt::TextureSampler sampler;
        sampler.filter = Nt::TextureFilter::Nearest;
        sampler.wrap   = Nt::TextureWrap::Repeat;

        m_texture = Nt::CreateRef<Nt::Texture2D>("Assets/Textures/Checkerboard.png", sampler);

        m_program = Nt::CreateRef<Nt::Shader>("basic", "Assets/Shaders/basic_vs.glsl", "Assets/Shaders/basic_fs.glsl");
        m_program->Bind();
        m_program->SetInt("u_texture", 0);
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        Nt::RenderCommand::SetClearColor(NT_COLOR_DARK_GRAY);
        Nt::RenderCommand::Clear();

        Nt::RendererAPI::BeginScene(m_camera);
            m_texture->Bind(0);
            Nt::RendererAPI::Submit(m_program, m_vao);
        Nt::RendererAPI::EndScene();
    }

private:
    Nt::Window& m_window = Nt::Application::Get().GetWindow();

    Nt::Ref<Nt::VertexArray> m_vao;
    Nt::Ref<Nt::Shader> m_program;
    Nt::Ref<Nt::Texture2D> m_texture;
    Nt::OrthographicCamera m_camera;
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
