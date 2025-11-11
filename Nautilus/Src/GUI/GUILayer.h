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

#ifndef _GUI_GUI_LAYER_H_
    #define _GUI_GUI_LAYER_H_

#include "Core/Layer.h"

namespace Nt
{
    class NT_API GUILayer :
        public Layer
    {
    public:
        NT_CLASS_DEFAULTS(GUILayer)
        GUILayer(void);
        ~GUILayer(void) = default;

        virtual void OnAttach(void) override;
        virtual void OnGUIRender(float32 deltaTime) override;
        virtual void OnDetach(void) override;
        virtual void OnEvent(Event& event) override;

        void Begin(void);
        void End(void);

        void BlockEvents(bool block);
        uint32 GetActiveWidgetId(void) const;

    private:
        void SetDarkThemeColors(void);

        bool m_blockEvents;
    };
} // namespace Nt

#endif // _GUI_GUI_LAYER_H_
