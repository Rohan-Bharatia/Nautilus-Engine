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

#ifndef _NT_NAUTILUS_LAYER_CPP_
    #define _NT_NAUTILUS_LAYER_CPP_

#include "Layer.h"

namespace Nt
{
    Layer::Layer(const std::string& name) :
        m_debugName(name)
    {}

    Layer::~Layer()
    {}

    void Layer::OnAttach()
    {}

    void Layer::OnDetach()
    {}

    void Layer::OnUpdate()
    {}

    void Layer::OnEvent(Event& event)
    {}

    const std::string& Layer::GetName() const
    {
        return m_debugName;
    }

} // namespace Nt

#endif // _NT_NAUTILUS_LAYER_CPP_
