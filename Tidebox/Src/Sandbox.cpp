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
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        float identity[16]{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

        bgfx::setViewTransform(0, identity, identity);
        bgfx::setViewRect(0, 0, 0, m_window.GetWidth(), m_window.GetHeight());
        bgfx::setViewScissor(0, 0, 0, m_window.GetWidth(), m_window.GetHeight());
        bgfx::touch(0);

        bgfx::Encoder* encoder = bgfx::begin();
        bgfx::end(encoder);
    }

private:
    Nt::Window& m_window = Nt::Application::Get().GetWindow();
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
