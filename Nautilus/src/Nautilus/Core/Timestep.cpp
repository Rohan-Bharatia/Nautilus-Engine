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

#ifndef _NT_NAUTILUS_CORE_TIMESTEP_CPP_
    #define _NT_NAUTILUS_CORE_TIMESTEP_CPP_

#include "Timestep.h"

namespace Nt
{
    Timestep::Timestep(float time) :
        m_time(time)
    {}

    float Timestep::GetSeconds() const
    {
        return m_time;
    }

    float Timestep::GetMilliseconds() const
    {
        return m_time * 1000.0f;
    }

    Timestep::operator float() const
    {
        return m_time;
    }
} // namespace Nt

#endif // _NT_NAUTILUS_CORE_TIMESTEP_CPP_
