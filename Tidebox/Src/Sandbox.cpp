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
    {
        Nt::float32 ratio = (Nt::float32)m_window.GetWidth() / m_window.GetHeight();
        m_camera          = Nt::OrthographicCamera(-ratio * m_zoom, ratio * m_zoom, -m_zoom, m_zoom);
    }

    ~SandboxLayer(void)
    {}

    virtual void OnAttach(void) override
    {
        Nt::TextureSampler sampler;
        sampler.filter = Nt::TextureFilter::Nearest;
        m_texture      = Nt::CreateRef<Nt::Texture2D>("Assets/Textures/Checkerboard.png", sampler);
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        if (Nt::Input::IsKeyPressed(Nt::Keycode::W))
            m_position.y -= m_tSpeed * deltaTime;
        if (Nt::Input::IsKeyPressed(Nt::Keycode::A))
            m_position.x += m_tSpeed * deltaTime;
        if (Nt::Input::IsKeyPressed(Nt::Keycode::S))
            m_position.y += m_tSpeed * deltaTime;
        if (Nt::Input::IsKeyPressed(Nt::Keycode::D))
            m_position.x -= m_tSpeed * deltaTime;
        if (Nt::Input::IsKeyPressed(Nt::Keycode::Q))
            m_rotation -= m_rSpeed * deltaTime;
        if (Nt::Input::IsKeyPressed(Nt::Keycode::E))
            m_rotation += m_rSpeed * deltaTime;
        if (Nt::Input::IsKeyPressed(Nt::Keycode::R))
        {
            m_position = { 0.0f, 0.0f, 0.0f };
            m_rotation = 0.0f;
        }

        if (m_rotation >= 180.0f)
            m_rotation -= 360.0f;
        if (m_rotation <= -180.0f)
            m_rotation += 360.0f;

        m_camera.SetPosition(m_position);
        m_camera.SetRotation(m_rotation);
        m_tSpeed = m_zoom;

        Nt::RenderCommand::SetClearColor(NT_COLOR_DARK_GRAY);
        Nt::RenderCommand::Clear();

        Nt::SceneRenderer::BeginScene(m_camera);
            Nt::SceneRenderer::DrawQuad({ 0.0f, 0.0f }, { 0.75f, 1.0f }, 0.0f, NT_COLOR_DEFAULT);
            Nt::SceneRenderer::DrawQuad({ 0.5f, 0.5f, 0.1f }, { 1.0f, 1.0f }, -35.0f, m_texture, 2.0f, NT_COLOR_CHARTREUSE);
            Nt::SceneRenderer::DrawQuad({ -1.0f, 0.25f,-0.1f }, { 1.0f, 2.0f }, 15.0f, m_texture, 1.0f, NT_COLOR_RED);
        Nt::SceneRenderer::EndScene();
    }

    virtual void OnEvent(Nt::Event& event) override
    {
        switch (event.GetEventType())
        {
            case Nt::EventType::KeyPressed:
            {
                Nt::KeyPressedEvent& e = (Nt::KeyPressedEvent&)event;

                switch (e.GetKeyCode())
                {
                    case Nt::Keycode::Escape:
                        Nt::Application::Get().Close();
                        break;
                    case Nt::Keycode::F11:
                        m_window.SetFullscreen(!m_window.IsFullscreen());
                        break;
                    default:
                        break;
                }
                break;
            }
            case Nt::EventType::WindowResize:
            {
                Nt::WindowResizeEvent& e = (Nt::WindowResizeEvent&)event;

                Nt::float32 ratio = (Nt::float32)e.GetWidth() / e.GetHeight();
                m_camera.SetProjection(glm::ortho(-ratio * m_zoom, ratio * m_zoom, -m_zoom, m_zoom, -1.0f, 1.0f));

                break;
            }
            case Nt::EventType::MouseScrolled:
            {
                Nt::MouseScrolledEvent& e = (Nt::MouseScrolledEvent&)event;
                m_zoom -= e.GetYOffset() * 0.25f;
                m_zoom  = std::max(m_zoom, 0.25f);

                Nt::float32 ratio = (Nt::float32)m_window.GetWidth() / m_window.GetHeight();
                m_camera.SetProjection(glm::ortho(-ratio * m_zoom, ratio * m_zoom, -m_zoom, m_zoom, -1.0f, 1.0f));
                break;
            }
            default:
                break;
        }
    }

private:
    Nt::Window& m_window = Nt::Application::Get().GetWindow();

    Nt::Ref<Nt::Texture2D> m_texture;

    Nt::OrthographicCamera m_camera;
    Nt::Vector3 m_position = { 0.0f, 0.0f, 0.0f };
    Nt::float32 m_rotation = 0.0f;
    Nt::float32 m_zoom     = 1.0f;
    Nt::float32 m_tSpeed   = 5.0f;
    Nt::float32 m_rSpeed   = 5.0f;
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
