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

#ifndef _MATH_COLOR_H_
    #define _MATH_COLOR_H_

#include "PCH.h"

namespace Nt
{
    enum class NT_API ColorType
    {
        RGB,
        CMYK,
        HSV,
        HSL,
        Hex,
        OkLab,
    };

    class NT_API Color
    {
    public:
        NT_CLASS_DEFAULTS(Color)
        Color(void);
        Color(float32 r, float32 g, float32 b, float32 a=1.0f);
        Color(float32 value);
        Color(float32* values);
        Color(const glm::vec4& color);

        // Typecast operators
        operator float32*(void);
        operator glm::vec4(void) const;

        // Sign operators
        Color operator+(void) const;
        Color operator-(void) const;

        // Arithmetic operators
        Color operator+(const Color& other) const;
        Color operator+(float32 other) const;
        Color operator+(const glm::vec4& other) const;
        Color operator-(const Color& other) const;
        Color operator-(float32 other) const;
        Color operator-(const glm::vec4& other) const;
        Color operator*(const Color& other) const;
        Color operator*(float32 other) const;
        Color operator*(const glm::vec4& other) const;
        Color operator/(const Color& other) const;
        Color operator/(float32 other) const;
        Color operator/(const glm::vec4& other) const;
        Color operator%(const Color& other) const;
        Color operator%(float32 other) const;
        Color operator%(const glm::vec4& other) const;

        // Increment operators
        Color& operator++(void);
        Color operator++(int32);
        Color& operator--(void);
        Color operator--(int32);

        // Assignment operators
        Color& operator+=(const Color& other);
        Color& operator+=(float32 other);
        Color& operator+=(const glm::vec4& other);
        Color& operator-=(const Color& other);
        Color& operator-=(float32 other);
        Color& operator-=(const glm::vec4& other);
        Color& operator*=(const Color& other);
        Color& operator*=(float32 other);
        Color& operator*=(const glm::vec4& other);
        Color& operator/=(const Color& other);
        Color& operator/=(float32 other);
        Color& operator/=(const glm::vec4& other);
        Color& operator%=(const Color& other);
        Color& operator%=(float32 other);
        Color& operator%=(const glm::vec4& other);

        // Comparision operators
        bool operator==(const Color& other) const;
        bool operator==(float32 other) const;
        bool operator==(const glm::vec4& other) const;
        bool operator!=(const Color& other) const;
        bool operator!=(float32 other) const;
        bool operator!=(const glm::vec4& other) const;
        bool operator>(const Color& other) const;
        bool operator>(float32 other) const;
        bool operator>(const glm::vec4& other) const;
        bool operator>=(const Color& other) const;
        bool operator>=(float32 other) const;
        bool operator>=(const glm::vec4& other) const;
        bool operator<(const Color& other) const;
        bool operator<(float32 other) const;
        bool operator<(const glm::vec4& other) const;
        bool operator<=(const Color& other) const;
        bool operator<=(float32 other) const;
        bool operator<=(const glm::vec4& other) const;

        // Index operators
        float32& operator[](uint32 index);
        float32 operator[](uint32 index) const;

        float32 r, g, b, a;
    };

    NT_API Color CMYKToRGB(float32 c, float32 m, float32 y, float32 k);
    NT_API Color HSVToRGB(float32 h, float32 s, float32 v);
    NT_API Color HSLToRGB(float32 h, float32 s, float32 l);
    NT_API Color HexToRGB(uint32 hex);
    NT_API Color OkLabToRGB(float32 l, float32 a, float32 b);
} // namespace Nt

#define NT_COLOR_BLACK      ::Nt::Color(0.0f, 0.0f, 0.0f)
#define NT_COLOR_DARK_GRAY  ::Nt::Color(64.0f, 64.0f, 64.0f)
#define NT_COLOR_GRAY       ::Nt::Color(128.0f, 128.0f, 128.0f)
#define NT_COLOR_SILVER     ::Nt::Color(192.0f, 192.0f, 192.0f)
#define NT_COLOR_WHITE      ::Nt::Color(255.0f, 255.0f, 255.0f)
#define NT_COLOR_RED        ::Nt::Color(255.0f, 0.0f, 0.0f)
#define NT_COLOR_ORANGE     ::Nt::Color(255.0f, 165.0f, 0.0f)
#define NT_COLOR_YELLOW     ::Nt::Color(255.0f, 255.0f, 0.0f)
#define NT_COLOR_CHARTREUSE ::Nt::Color(0.0f, 255.0f, 0.0f)
#define NT_COLOR_GREEN      ::Nt::Color(0.0f, 128.0f, 0.0f)
#define NT_COLOR_TEAL       ::Nt::Color(0.0f, 128.0f, 128.0f)
#define NT_COLOR_CYAN       ::Nt::Color(0.0f, 255.0f, 255.0f)
#define NT_COLOR_BLUE       ::Nt::Color(0.0f, 0.0f, 255.0f)
#define NT_COLOR_MAGENTA    ::Nt::Color(255.0f, 0.0f, 255.0f)
#define NT_COLOR_PURPLE     ::Nt::Color(128.0f, 0.0f, 128.0f)

#endif // _MATH_COLOR_H_
