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

#ifndef _NT_NAUTILUS_RENDERER_SHADER_CPP_
    #define _NT_NAUTILUS_RENDERER_SHADER_CPP_

#include "Shader.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Nt
{
    Shader::~Shader()
    {}

    Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexSource, fragmentSource);
            default:
                NT_ASSERT(false, "Unknown renderer API!");
                return nullptr;
        }

        NT_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_SHADER_CPP_
