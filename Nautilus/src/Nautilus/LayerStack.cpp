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

#ifndef _NT_NAUTILUS_LAYER_STACK_CPP_
    #define _NT_NAUTILUS_LAYER_STACK_CPP_

#include "LayerStack.h"

namespace Nt
{
    LayerStack::LayerStack() :
        m_layerInsertIndex(0)
    {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
        {
            layer->OnDetach();
            delete layer;
            layer = nullptr;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
        ++m_layerInsertIndex;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        Iterator it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
            --m_layerInsertIndex;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        Iterator it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
            m_layers.erase(it);
    }

    LayerStack::Iterator LayerStack::begin()
    {
        return m_layers.begin();
    }

    LayerStack::Iterator LayerStack::end()
    {
        return m_layers.end();
    }
} // namespace Nt

#endif // _NT_NAUTILUS_LAYER_STACK_CPP_
