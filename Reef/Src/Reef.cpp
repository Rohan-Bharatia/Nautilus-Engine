#ifndef _SANDBOX_CPP_
    #define _SANDBOX_CPP_

#include "Editor.h"

#include <Nautilus.h>
#include <EntryPoint.h>

class EditorApplication :
    public Nt::Application
{
public:
    EditorApplication(void) :
        Application("Nautilus Editor")
    {
        PushLayer(new Nt::EditorLayer());
    }

    ~EditorApplication(void)
    {}
};

Nt::Application* Nt::CreateApplication(Nt::int32 argc, char* argv[])
{
    return new EditorApplication();
}

#endif // _SANDBOX_CPP_
