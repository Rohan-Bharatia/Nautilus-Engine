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

#ifndef _CORE_LAYER_STACK_H_
    #define _CORE_LAYER_STACK_H_

#include "Layer.h"

namespace Nt
{
    class NT_API LayerStack
    {
    public:
        NT_CLASS_DEFAULTS(LayerStack)
        LayerStack(void) = default;
        ~LayerStack(void);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin(void);
        std::vector<Layer*>::iterator end(void);
        std::vector<Layer*>::reverse_iterator rbegin(void);
        std::vector<Layer*>::reverse_iterator rend(void);

        std::vector<Layer*>::const_iterator begin(void) const;
        std::vector<Layer*>::const_iterator end(void) const;
        std::vector<Layer*>::const_reverse_iterator rbegin(void) const;
        std::vector<Layer*>::const_reverse_iterator rend(void) const;

    private:
        std::vector<Layer*> m_layers;
        uint32_t m_layerInsertIndex = 0;
    };
} // namespace Nt

#endif // _CORE_LAYER_STACK_H_
