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

#ifndef _NT_NAUTILUS_CORE_TIMESTEP_H_
    #define _NT_NAUTILUS_CORE_TIMESTEP_H_

#include "PCH.h"

namespace Nt
{
    class NT_API Timestep
    {
    public:
        Timestep(float time=0.0f);

        float GetSeconds() const;
        float GetMilliseconds() const;

        operator float() const;

    private:
        float m_time;
    };
} // namespace Nt

#endif // _NT_NAUTILUS_CORE_TIMESTEP_H_
