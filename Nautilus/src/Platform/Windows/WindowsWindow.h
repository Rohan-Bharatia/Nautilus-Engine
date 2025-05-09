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

#ifndef _NT_NAUTILUS_PLATFORM_WINDOWS_WINDOW_H_
    #define _NT_NAUTILUS_PLATFORM_WINDOWS_WINDOW_H_

#include "PCH.h"

#include "Nautilus/Window.h"
#include "Nautilus/Renderer/GraphicsContext.h"

namespace Nt
{
    class NT_API WindowsWindow :
        public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        std::string GetTitle() const override;
        unsigned int GetWidth() const override;
        unsigned int GetHeight() const override;

        void SetEventCallback(const EventCallbackFn& callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const override;

    private:
        struct WindowData
		{
			std::string title;
			unsigned int width;
            unsigned int height;
			bool vsync;

			EventCallbackFn callback;
		};

        GLFWwindow* m_window;
		WindowData m_data;
        GraphicsContext* m_context;

        void Initialize(const WindowProps& props);
        void Shutdown();
    };
}

#endif // _NT_NAUTILUS_PLATFORM_WINDOWS_WINDOW_H_
