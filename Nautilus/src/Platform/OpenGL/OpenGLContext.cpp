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

#ifndef _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_CONTEXT_CONTEXT_CPP_
    #define _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_CONTEXT_CONTEXT_CPP_

#include "OpenGLContext.h"

namespace Nt
{
    OpenGLContext::OpenGLContext(GLFWwindow* handle) :
        m_handle(handle)
    {
        NT_ASSERT(m_handle, "Window handle is null!");
    }

    void OpenGLContext::Initialize()
    {
        glfwMakeContextCurrent(m_handle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NT_ASSERT(status, "Failed to initialize GLAD!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_handle);
    }
} // namespace Nt

#endif // _NT_NAUTILUS_PLATFORM_OPENGL_OPENGL_CONTEXT_CONTEXT_CPP_
