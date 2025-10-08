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

#ifndef _MATH_ANGLE_CPP_
    #define _MATH_ANGLE_CPP_

#include "Angle.h"

namespace Nt
{
    Angle::Angle(void) :
        m_rads(0.0f)
    {}

    Angle::Angle(float32 rads) :
        m_rads(rads)
    {}

    Angle::Angle(const Vector2& vec) :
        m_rads(std::atan2(vec.y, vec.x))
    {}

    Angle::operator float32(void) const
    {
        return m_rads;
    }

    Angle Angle::operator+(void) const
    {
        return Angle(+m_rads);
    }

    Angle Angle::operator-(void) const
    {
        return Angle(-m_rads);
    }

    Angle Angle::operator+(const Angle& other) const
    {
        return Angle(m_rads + other.m_rads);
    }

    Angle Angle::operator+(float32 other) const
    {
        return Angle(m_rads + other);
    }

    Angle Angle::operator-(const Angle& other) const
    {
        return Angle(m_rads - other.m_rads);
    }

    Angle Angle::operator-(float32 other) const
    {
        return Angle(m_rads - other);
    }

    Angle Angle::operator*(const Angle& other) const
    {
        return Angle(m_rads * other.m_rads);
    }

    Angle Angle::operator*(float32 other) const
    {
        return Angle(m_rads * other);
    }

    Angle Angle::operator/(const Angle& other) const
    {
        NT_ASSERT(other.m_rads != 0.0f, "Cannot divide by zero");
        return Angle(m_rads / other.m_rads);
    }

    Angle Angle::operator/(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Angle(m_rads / other);
    }

    Angle Angle::operator%(const Angle& other) const
    {
        NT_ASSERT(other.m_rads != 0.0f, "Cannot divide by zero");
        return Angle(std::fmod(m_rads, other.m_rads));
    }

    Angle Angle::operator%(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Angle(std::fmod(m_rads, other));
    }

    Angle& Angle::operator++(void)
    {
        ++m_rads;
        return *this;
    }

    Angle Angle::operator++(int32)
    {
        Angle temp = *this;
        ++m_rads;
        return temp;
    }

    Angle& Angle::operator--(void)
    {
        --m_rads;
        return *this;
    }

    Angle Angle::operator--(int32)
    {
        Angle temp = *this;
        --m_rads;
        return temp;
    }

    Angle& Angle::operator+=(const Angle& other)
    {
        return *this = *this + other;
    }

    Angle& Angle::operator+=(float32 other)
    {
        return *this = *this + other;
    }

    Angle& Angle::operator-=(const Angle& other)
    {
        return *this = *this - other;
    }

    Angle& Angle::operator-=(float32 other)
    {
        return *this = *this - other;
    }

    Angle& Angle::operator*=(const Angle& other)
    {
        return *this = *this * other;
    }

    Angle& Angle::operator*=(float32 other)
    {
        return *this = *this * other;
    }

    Angle& Angle::operator/=(const Angle& other)
    {
        NT_ASSERT(other.m_rads != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Angle& Angle::operator/=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Angle& Angle::operator%=(const Angle& other)
    {
        NT_ASSERT(other.m_rads != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Angle& Angle::operator%=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    bool Angle::operator==(const Angle& other) const
    {
        return m_rads == other.m_rads;
    }

    bool Angle::operator==(float32 other) const
    {
        return m_rads == other;
    }

    bool Angle::operator!=(const Angle& other) const
    {
        return m_rads != other.m_rads;
    }

    bool Angle::operator!=(float32 other) const
    {
        return m_rads != other;
    }

    bool Angle::operator>(const Angle& other) const
    {
        return m_rads > other.m_rads;
    }

    bool Angle::operator>(float32 other) const
    {
        return m_rads > other;
    }

    bool Angle::operator>=(const Angle& other) const
    {
        return m_rads >= other.m_rads;
    }

    bool Angle::operator>=(float32 other) const
    {
        return m_rads >= other;
    }

    bool Angle::operator<(const Angle& other) const
    {
        return m_rads < other.m_rads;
    }

    bool Angle::operator<(float32 other) const
    {
        return m_rads < other;
    }

    bool Angle::operator<=(const Angle& other) const
    {
        return m_rads <= other.m_rads;
    }

    bool Angle::operator<=(float32 other) const
    {
        return m_rads <= other;
    }

    float32 Angle::Radians(void) const
    {
        return m_rads;
    }

    float32 Angle::Degrees(void) const
    {
        return m_rads * (180.0f / NT_PI);
    }

    std::ostream& operator<<(std::ostream& stream, const Angle& angle)
    {
        stream << angle.Radians();
        return stream;
    }

    namespace Literals
    {
        constexpr Angle operator""_deg(float80 value)
        {
            return Angle(((float32)value) * (NT_PI / 180.0f));
        }

        constexpr Angle operator""_deg(uint64 value)
        {
            return Angle(((float32)value) * (NT_PI / 180.0f));
        }

        constexpr Angle operator""_rad(float80 value)
        {
            return Angle((float32)value);
        }

        constexpr Angle operator""_rad(uint64 value)
        {
            return Angle((float32)value);
        }
    } // namespace Literals
} // namespace Nt

#endif // _MATH_ANGLE_CPP_
