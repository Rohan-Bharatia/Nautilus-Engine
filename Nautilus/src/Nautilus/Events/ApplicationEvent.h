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

#ifndef _NT_NAUTILUS_EVENTS_APPLICATION_EVENT_H_
    #define _NT_NAUTILUS_EVENTS_APPLICATION_EVENT_H_

#include "Event.h"

namespace Nt
{
    class WindowResizeEvent :
        public Event
    {
    public:
        WindowResizeEvent(const unsigned int width, const unsigned int height);

        unsigned int GetWidth() const;
        unsigned int GetHeight() const;

        std::string ToString() const override;

        NT_EVENT_CLASS_TYPE(WindowResize)
        NT_EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_width;
        unsigned int m_height;
    };

    class WindowCloseEvent :
        public Event
    {
    public:
        WindowCloseEvent() = default;

        NT_EVENT_CLASS_TYPE(WindowClose)
        NT_EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ApplicationTickEvent :
        public Event
    {
    public:
        ApplicationTickEvent() = default;

        NT_EVENT_CLASS_TYPE(ApplicationTick)
        NT_EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ApplicationUpdateEvent :
        public Event
    {
    public:
        ApplicationUpdateEvent() = default;

        NT_EVENT_CLASS_TYPE(ApplicationUpdate)
        NT_EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ApplicationRenderEvent :
        public Event
    {
    public:
        ApplicationRenderEvent() = default;

        NT_EVENT_CLASS_TYPE(ApplicationRender)
        NT_EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
} // namespace Nt

#endif // _NT_NAUTILUS_EVENTS_APPLICATION_EVENT_H_
