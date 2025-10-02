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

#ifndef _CORE_TIMER_CPP_
    #define _CORE_TIMER_CPP_

#include "Timer.h"

namespace Nt
{
    // Timer members:
    // std::chrono::high_resolution_clock::time_point m_start;
    // std::chrono::high_resolution_clock::time_point m_end;
    // bool m_running;
    // bool m_paused;

    void Timer::Reset(void)
    {
        m_start   = std::chrono::high_resolution_clock::time_point();
        m_end     = std::chrono::high_resolution_clock::time_point();
        m_running = false;
        m_paused  = false;
    }

    void Timer::Start(void)
    {
        if (m_running)
            return;

        m_start   = std::chrono::high_resolution_clock::now();
        m_running = true;
        m_paused  = false;
    }

    void Timer::Stop(void)
    {
        if (!m_running)
            return;

        m_end     = std::chrono::high_resolution_clock::now();
        m_running = false;
        m_paused  = false;
    }

    void Timer::Resume(void)
    {
        if (!m_paused)
            return;

        m_start  += std::chrono::high_resolution_clock::now() - m_end;
        m_paused  = false;
        m_running = true;
    }

    void Timer::Pause(void)
    {
        if (m_paused)
            return;

        m_end     = std::chrono::high_resolution_clock::now();
        m_paused  = true;
        m_running = false;
    }

    float32 Timer::GetSeconds(void) const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(m_end - m_start).count();
    }

    float32 Timer::GetMilliseconds(void) const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
    }

    float32 Timer::GetMicroseconds(void) const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count();
    }

    float32 GetSystemTime(void)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
} // namespace Nt

#endif // _CORE_TIMER_CPP_
