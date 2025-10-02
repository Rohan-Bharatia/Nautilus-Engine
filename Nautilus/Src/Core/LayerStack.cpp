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

#ifndef _CORE_LAYER_STACK_CPP_
    #define _CORE_LAYER_STACK_CPP_

#include "LayerStack.h"

namespace Nt
{
    LayerStack::~LayerStack(void)
    {
        for (Layer* layer : m_layers)
        {
            layer->OnDetach();
            delete layer;
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
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            layer->OnDetach();
            m_layers.erase(it);
            --m_layerInsertIndex;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
        {
            overlay->OnDetach();
            m_layers.erase(it);
        }
    }

    std::vector<Layer*>::iterator LayerStack::begin(void)
    {
        return m_layers.begin();
    }

    std::vector<Layer*>::iterator LayerStack::end(void)
    {
        return m_layers.end();
    }

    std::vector<Layer*>::reverse_iterator LayerStack::rbegin(void)
    {
        return m_layers.rbegin();
    }

    std::vector<Layer*>::reverse_iterator LayerStack::rend(void)
    {
        return m_layers.rend();
    }

    std::vector<Layer*>::const_iterator LayerStack::begin(void) const
    {
        return m_layers.begin();
    }

    std::vector<Layer*>::const_iterator LayerStack::end(void) const
    {
        return m_layers.end();
    }

    std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin(void) const
    {
        return m_layers.rbegin();
    }

    std::vector<Layer*>::const_reverse_iterator LayerStack::rend(void) const
    {
        return m_layers.rend();
    }
} // namespace Nt

#endif // _CORE_LAYER_STACK_CPP_
