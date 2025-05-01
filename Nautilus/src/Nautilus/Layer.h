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

#ifndef _NT_NAUTILUS_LAYER_H_
    #define _NT_NAUTILUS_LAYER_H_

#include "PCH.h"

#include "Events/Event.h"

namespace Nt
{
    class NT_API Layer
    {
    public:
        Layer(const std::string& name="Layer");
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event& event);

        const std::string& GetName() const;

    protected:
        std::string m_debugName;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_LAYER_H_
