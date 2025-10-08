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

#ifndef _MATH_ANGLE_H_
    #define _MATH_ANGLE_H_

#include "Vector.h"

namespace Nt
{
    class NT_API Angle
    {
    public:
        NT_CLASS_DEFAULTS(Angle)
        Angle(void);
        Angle(float32 rads);
        Angle(const Vector2& vec);

        // Typecast operators
        operator float32(void) const;

        // Sign operators
        Angle operator+(void) const;
        Angle operator-(void) const;

        // Arithmetic operators
        Angle operator+(const Angle& other) const;
        Angle operator+(float32 other) const;
        Angle operator-(const Angle& other) const;
        Angle operator-(float32 other) const;
        Angle operator*(const Angle& other) const;
        Angle operator*(float32 other) const;
        Angle operator/(const Angle& other) const;
        Angle operator/(float32 other) const;
        Angle operator%(const Angle& other) const;
        Angle operator%(float32 other) const;

        // Increment operators
        Angle& operator++(void);
        Angle operator++(int32);
        Angle& operator--(void);
        Angle operator--(int32);

        // Assignment operators
        Angle& operator+=(const Angle& other);
        Angle& operator+=(float32 other);
        Angle& operator-=(const Angle& other);
        Angle& operator-=(float32 other);
        Angle& operator*=(const Angle& other);
        Angle& operator*=(float32 other);
        Angle& operator/=(const Angle& other);
        Angle& operator/=(float32 other);
        Angle& operator%=(const Angle& other);
        Angle& operator%=(float32 other);

        // Comparison operators
        bool operator==(const Angle& other) const;
        bool operator==(float32 other) const;
        bool operator!=(const Angle& other) const;
        bool operator!=(float32 other) const;
        bool operator>(const Angle& other) const;
        bool operator>(float32 other) const;
        bool operator>=(const Angle& other) const;
        bool operator>=(float32 other) const;
        bool operator<(const Angle& other) const;
        bool operator<(float32 other) const;
        bool operator<=(const Angle& other) const;
        bool operator<=(float32 other) const;

        float32 Radians(void) const;
        float32 Degrees(void) const;

    private:
        float32 m_rads;
    };

    std::ostream& operator<<(std::ostream& stream, const Angle& angle);

    namespace Literals
    {
        constexpr Angle operator""_deg(float80 value);
        constexpr Angle operator""_deg(uint64 value);
        constexpr Angle operator""_rad(float80 value);
        constexpr Angle operator""_rad(uint64 value);
    } // namespace Literals
} // namespace Nt

namespace std
{
    template<typename T>
    struct hash;

    template<>
    struct hash<Nt::Angle>
    {
        size_t operator()(const Nt::Angle& angle) const
        {
            return std::hash<Nt::float32>()(angle.Radians());
        }
    };
} // namespace std

#endif // _MATH_ANGLE_H_
