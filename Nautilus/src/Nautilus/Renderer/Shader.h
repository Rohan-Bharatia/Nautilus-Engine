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

#pragma once

#ifndef _NT_NAUTILUS_RENDERER_SHADER_H_
    #define _NT_NAUTILUS_RENDERER_SHADER_H_

#include "PCH.h"

namespace Nt
{
    class NT_API Shader
    {
    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_rendererID;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_RENDERER_SHADER_H_
