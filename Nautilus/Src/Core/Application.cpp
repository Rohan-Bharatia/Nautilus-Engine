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

#ifndef _CORE_APPLICATION_CPP_
    #define _CORE_APPLICATION_CPP_

#include "Application.h"

#include "Timer.h"
#include "Input.h"
#include "Renderer/RendererAPI.h"

namespace Nt
{
    Application::Application(int32 argc, char* argv[]) :
        m_running(true), m_minimized(false), m_lastFrame(0.0f)
    {
        NT_ASSERT(s_instance == nullptr, "Application already exists!");
        s_instance = this;

        Log::Initialize("Nautilus.log");

        WindowProperties props{};
        m_window = CreateScope<Window>(props);
        m_window->SetEventCallback(NT_BIND_EVENT_FN(Application::OnEvent));

        RendererAPI::Initialize();
        m_guiLayer = new GUILayer();
        m_guiLayer->BlockEvents(false);

        PushLayer(new InputLayer());
        PushOverlay(m_guiLayer);
    }

    Application::~Application(void)
    {
        RendererAPI::Shutdown();

        if (s_instance)
            s_instance = nullptr;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(NT_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(NT_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
        {
            if (e.IsHandled())
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::Run(void)
    {
        while (m_running)
        {
            float32 time      = GetSystemTime();
            float32 deltaTime = time - m_lastFrame;
            m_lastFrame       = time;

            ExecuteMainThreadQueue();

            if (!m_minimized)
            {
                m_guiLayer->Begin();
                for (Layer* layer : m_layerStack)
                {
                    layer->OnUpdate(deltaTime);
                    layer->OnGUIRender(deltaTime);
                }
                m_guiLayer->End();
            }

            m_window->OnUpdate(deltaTime);
        }
    }

    void Application::Close(void)
    {
        m_running = false;
    }

    void Application::SubmitToMainThread(const std::function<void()>& func)
    {
        std::scoped_lock<std::mutex> lock(m_mainThreadQueueMutex);
        m_mainThreadQueue.emplace_back(func);
    }

    Window& Application::GetWindow(void)
    {
        return *m_window;
    }

    Application& Application::Get(void)
    {
        return *s_instance;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_minimized = true;
            return false;
        }

        m_minimized = false;
        RendererAPI::OnWindowResize(e.GetWidth(), e.GetHeight());
        return true;
    }

    void Application::ExecuteMainThreadQueue(void)
    {
        std::scoped_lock<std::mutex> lock(m_mainThreadQueueMutex);

        for (auto& func : m_mainThreadQueue)
            func();

        m_mainThreadQueue.clear();
    }
} // namespace Nt

#endif // _CORE_APPLICATION_CPP_
