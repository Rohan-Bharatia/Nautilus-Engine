#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#pragma once

#ifndef _NAUTILUS_H_
    #define _NAUTILUS_H_

#include "PCH.h"

#include "Core/Application.h"
#include "Core/String.h"
#include "Core/IO.h"
#include "Core/Timer.h"
#include "Core/Log.h"
#include "Core/UUID.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Event.h"
#include "Core/ApplicationEvent.h"
#include "Core/KeyEvent.h"
#include "Core/MouseEvent.h"
#include "Core/ControllerEvent.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Core/Codes.h"
#include "Core/Dialogs.h"
#include "Core/Filesystem.h"

#include "Math/Vector.h"

#include "Renderer/GraphicsContext.h"

#define NT_VERSION_MAJOR 1
#define NT_VERSION_MINOR 0
#define NT_VERSION_PATCH 0
#define NT_VERSION_INT (NT_VERSION_MAJOR * 100 + NT_VERSION_MINOR * 10 + NT_VERSION_PATCH)
#define NT_VERSION_STRING NT_STRINGIFY(NT_VERSION_MAJOR) "." NT_STRINGIFY(NT_VERSION_MINOR) "." NT_STRINGIFY(NT_VERSION_PATCH)
#define NT_VERSION_PRETTY "v" NT_VERSION_STRING
#define NT_VERSION_CHECK(major, minor, patch)                                                    \
    (NT_VERSION_MAJOR > (major) ||                                                               \
    (NT_VERSION_MAJOR == (major) && NT_VERSION_MINOR > (minor)) ||                               \
    (NT_VERSION_MAJOR == (major) && NT_VERSION_MINOR == (minor) && NT_VERSION_PATCH >= (patch)))

#endif // _NAUTILUS_H_
