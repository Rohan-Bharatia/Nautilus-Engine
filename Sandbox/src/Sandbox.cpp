#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                                 ...
//
//                  Copyright (c) Rohan Bharatia 2025

#pragma endregion LICENSE

#ifndef _SBX_SANDBOX_CPP_
    #define _SBX_SANDBOX_CPP_

#include <Nautilus.h>

class SandboxLayer : public Nt::Layer
{
public:
    SandboxLayer() :
        Layer("Sandbox")
    {}

    void OnUpdate() override
    {
        NT_CLIENT_LOG_INFO("Sandbox layer updated!");
    }

    void OnEvent(Nt::Event& event) override
    {
        NT_CLIENT_LOG_TRACE(event.ToString());
    }
};

class SandboxApplication :
    public Nt::Application
{
public:
    SandboxApplication()
    {
        PushLayer(new SandboxLayer());
    }

    ~SandboxApplication()
    {}
};

Nt::Application* Nt::CreateApplication()
{
    return new SandboxApplication();
}

#endif // _SBX_SANDBOX_CPP_
