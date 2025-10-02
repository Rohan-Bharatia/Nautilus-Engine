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

#ifndef _CORE_UUID_H_
    #define _CORE_UUID_H_

#include "PCH.h"

namespace Nt
{
    class NT_API UUID
    {
    public:
        NT_CLASS_DEFAULTS(UUID)
        UUID(void);
        UUID(uint64 id);
        ~UUID(void);

        operator uint64(void) const;

    private:
        static std::unordered_set<uint64> s_ids;
        static std::random_device s_device;
        static std::mt19937_64 s_random;
        static std::uniform_int_distribution<uint64> s_distribution;
        uint64 m_id;
    };
} // namespace Nt

namespace std
{
    template<typename T>
    struct hash;

    template<>
    struct hash<Nt::UUID>
    {
        size_t operator()(const Nt::UUID& uuid) const
        {
            return (Nt::uint64)uuid;
        }
    };
} // namespace std

#endif // _CORE_UUID_H_
