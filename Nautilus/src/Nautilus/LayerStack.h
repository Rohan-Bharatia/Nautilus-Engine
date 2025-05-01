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

#ifndef _NT_NAUTILUS_LAYER_STACK_H_
    #define _NT_NAUTILUS_LAYER_STACK_H_

#include "PCH.h"

#include "Layer.h"

namespace Nt
{
    class NT_API LayerStack
    {
        using Iterator = std::vector<Layer*>::iterator;
        
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        Iterator begin();
        Iterator end();

    private:
        std::vector<Layer*> m_layers;
        Iterator m_layerInsertIndex;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_LAYER_STACK_H_
