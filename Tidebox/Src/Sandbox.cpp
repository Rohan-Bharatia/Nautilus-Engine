#ifndef _SANDBOX_CPP_
    #define _SANDBOX_CPP_

#include <Nautilus.h>
#include <EntryPoint.h>

class Sandbox :
    public Nt::Application
{
public:
    Sandbox(Nt::int32 argc, char* argv[]) :
        Application(argc, argv)
    {}

    ~Sandbox(void)
    {}
};

Nt::Application* Nt::CreateApplication(Nt::int32 argc, char* argv[])
{
    return new Sandbox(argc, argv);
}

#endif // _SANDBOX_CPP_
