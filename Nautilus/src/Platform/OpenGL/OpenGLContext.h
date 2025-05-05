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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_CONTEXT_CONTEXT_H_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_CONTEXT_CONTEXT_H_

#include "PCH.h"

#include "Nautilus/Renderer/GraphicsContext.h"

namespace Nt
{
    class NT_API OpenGLContext :
        public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* handle);

        virtual void Initialize() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_handle;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_CONTEXT_CONTEXT_H_
