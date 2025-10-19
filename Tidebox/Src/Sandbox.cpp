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
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x030303ff, 1.0f, 0);

        struct Vertex
        {
            Nt::float32 x, y, z;
            Nt::uint32 r, g, b, a;
        };

        static Vertex vertices[]    =
        {
            {  0.0f,  0.5f, 0.0f, 255,   0,   0, 255 },
            {  0.5f, -0.5f, 0.0f,   0, 255,   0, 255 },
            { -0.5f, -0.5f, 0.0f,   0,   0, 255, 255 },
        };
        static Nt::uint32 indices[] = { 0, 1, 2 };

        Nt::BufferLayout layout(
        {
            { Nt::ShaderDataType::Float3, "a_position", false },
            { Nt::ShaderDataType::Float4, "a_color0",   false }
        });

        Nt::Ref<Nt::VertexBuffer> vbo = Nt::CreateRef<Nt::VertexBuffer>(layout, (Nt::float32*)vertices, sizeof(Vertex) * 3);
        Nt::Ref<Nt::IndexBuffer> ibo = Nt::CreateRef<Nt::IndexBuffer>(indices, sizeof(Nt::uint16) * 3);
        m_vao                    = Nt::CreateRef<Nt::VertexArray>();
        m_vao->AddVertexBuffer(vbo);
        m_vao->SetIndexBuffer(ibo);

        m_shader = Nt::CreateRef<Nt::Shader>("basic", "Assets/Shaders/basic_vs.bin", "Assets/Shaders/basic_fs.bin");
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        bgfx::Encoder* encoder = bgfx::begin();

        bgfx::setViewRect(0, 0, 0, m_window.GetWidth(), m_window.GetHeight());

        encoder->touch(0);
        encoder->setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA));

        m_vao->Bind(encoder);
        m_shader->Bind(encoder);

        bgfx::end(encoder);
    }

private:
    Nt::Window& m_window = Nt::Application::Get().GetWindow();

    Nt::Ref<Nt::VertexArray> m_vao;
    Nt::Ref<Nt::Shader> m_shader;
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
