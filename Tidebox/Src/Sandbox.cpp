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

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(Nt::float32), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(Nt::float32), (void*)(3 * sizeof(Nt::float32)));

        static const char* vsSource = R"(
#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

layout(location = 0) out vec4 v_color;

void main(void)
{
    gl_Position = vec4(a_position, 1.0);
    v_color     = a_color;
}
)";
        static const char* fsSource = R"(
#version 460 core

layout(location = 0) in vec4 v_color;

layout(location = 0) out vec4 o_color;

void main(void)
{
    o_color = v_color;
}
)";

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vsSource, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fsSource, NULL);
        glCompileShader(fs);

        m_program = glCreateProgram();
        glAttachShader(m_program, vs);
        glAttachShader(m_program, fs);
        glLinkProgram(m_program);
        glUseProgram(m_program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
        glScissor(0, 0, m_window.GetWidth(), m_window.GetHeight());
    }

    virtual void OnUpdate(Nt::float32 deltaTime) override
    {
        glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
        glScissor(0, 0, m_window.GetWidth(), m_window.GetHeight());

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

    virtual void OnDetach(void) override
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ibo);
        glDeleteVertexArrays(1, &m_vao);
        glDeleteProgram(m_program);
    }

private:
    Nt::Window& m_window = Nt::Application::Get().GetWindow();

    GLuint m_vbo, m_ibo, m_vao, m_program;
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
