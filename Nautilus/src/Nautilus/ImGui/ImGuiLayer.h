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

#ifndef _NT_NAUTILUS_IMGUI_IMGUI_LAYER_H_
    #define _NT_NAUTILUS_IMGUI_IMGUI_LAYER_H_

#include "PCH.h"

#include "Nautilus/Layer.h"

#include "Nautilus/Events/KeyEvent.h"
#include "Nautilus/Events/MouseEvent.h"
#include "Nautilus/Events/ApplicationEvent.h"

namespace Nt
{
    class NT_API ImGuiLayer :
        public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnUpdate() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& event) override;

    private:
        float m_time;

        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
    };
} // namespace Nt

#endif // _NT_NAUTILUS_IMGUI_IMGUI_LAYER_H_
