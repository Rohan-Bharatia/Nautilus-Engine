#ifndef _SANDBOX_CPP_
    #define _SANDBOX_CPP_

#include <Nautilus.h>
#include <EntryPoint.h>

Nt::Application* Nt::CreateApplication(Nt::int32 argc, char* argv[])
{
    return new Nt::Application(argc, argv);
}

#endif // _SANDBOX_CPP_
