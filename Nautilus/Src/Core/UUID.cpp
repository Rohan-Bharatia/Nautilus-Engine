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

#ifndef _CORE_UUID_CPP_
    #define _CORE_UUID_CPP_

#include "UUID.h"

namespace Nt
{
    std::unordered_set<uint64> UUID::s_ids;
    std::random_device UUID::s_device;
    std::mt19937_64 UUID::s_random;
    std::uniform_int_distribution<uint64> UUID::s_distribution;

    UUID::UUID(void)
    {
        if (s_ids.find(m_id) != s_ids.end())
            m_id = s_distribution(s_random);
    }

    UUID::UUID(uint64 id)
    {
        m_id = id;
    }

    UUID::~UUID(void)
    {
        s_ids.erase(m_id);
    }

    UUID::operator uint64(void) const
    {
        return m_id;
    }
} // namespace Nt

#endif // _CORE_UUID_CPP_
