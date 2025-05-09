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

#ifndef _NT_NAUTILUS_H_
    #define _NT_NAUTILUS_H_

// Nautilus application usage
#include "Nautilus/Core.h"
#include "Nautilus/Log.h"
#include "Nautilus/Events/Event.h"
#include "Nautilus/Events/KeyEvent.h"
#include "Nautilus/Events/MouseEvent.h"
#include "Nautilus/Events/ApplicationEvent.h"
#include "Nautilus/Window.h"
#include "Nautilus/Layer.h"
#include "Nautilus/LayerStack.h"
#include "Nautilus/ImGui/ImGuiLayer.h"
#include "Nautilus/KeyCodes.h"
#include "Nautilus/Input.h"
#include "Nautilus/Renderer/GraphicsContext.h"
#include "Nautilus/Renderer/Shader.h"
#include "Nautilus/Renderer/Buffer.h"
#include "Nautilus/Renderer/VertexArray.h"
#include "Nautilus/Renderer/Renderer.h"
#include "Nautilus/Renderer/RendererAPI.h"
#include "Nautilus/Renderer/RenderCommand.h"
#include "Nautilus/Renderer/OrthographicCamera.h"
#include "Nautilus/Application.h"

// Entry point
#include "Nautilus/EntryPoint.h"

#endif // _NT_NAUTILUS_H_
