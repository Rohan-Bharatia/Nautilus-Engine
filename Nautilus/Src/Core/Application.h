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

#ifndef _CORE_APPLICATION_H_
    #define _CORE_APPLICATION_H_

#include "LayerStack.h"

namespace Nt
{
    class NT_API Application
    {
    public:
        NT_CLASS_DEFAULTS(Application)
        Application(int32 argc, char* argv[]);
        virtual ~Application(void);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        void Run(void);
        void Close(void);

        void SubmitToMainThread(const std::function<void()>& func);

        static Application& Get(void);

    private:
        void ExecuteMainThreadQueue(void);

        bool m_running;
        bool m_minimized;
        LayerStack m_layerStack;
        float32 m_lastFrame;
        std::vector<std::function<void()>> m_mainThreadQueue;
        std::mutex m_mainThreadQueueMutex;
        static Application* s_instance;
    };
} // namespace Nt

#endif // _CORE_APPLICATION_H_
