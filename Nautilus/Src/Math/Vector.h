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

#ifndef _MATH_VECTOR_H_
    #define _MATH_VECTOR_H_

#include "PCH.h"

namespace Nt
{
    class NT_API Vector2
    {
    public:
        NT_CLASS_DEFAULTS(Vector2)
        Vector2(void);
        Vector2(float32 x, float32 y);
        Vector2(float32 value);
        Vector2(float32* values);
        Vector2(const glm::vec2& value);

        // Typecast operators
        operator float32*(void);
        operator glm::vec2(void) const;

        // Sign operators
        Vector2 operator+(void) const;
        Vector2 operator-(void) const;

        // Arithmetic operators
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator+(float32 other) const;
        Vector2 operator+(const glm::vec2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator-(float32 other) const;
        Vector2 operator-(const glm::vec2& other) const;
        Vector2 operator*(const Vector2& other) const;
        Vector2 operator*(float32 other) const;
        Vector2 operator*(const glm::vec2& other) const;
        Vector2 operator/(const Vector2& other) const;
        Vector2 operator/(float32 other) const;
        Vector2 operator/(const glm::vec2& other) const;
        Vector2 operator%(const Vector2& other) const;
        Vector2 operator%(float32 other) const;
        Vector2 operator%(const glm::vec2& other) const;

        // Increment operators
        Vector2& operator++(void);
        Vector2 operator++(int32);
        Vector2& operator--(void);
        Vector2 operator--(int32);

        // Assignment operators
        Vector2& operator+=(const Vector2& other);
        Vector2& operator+=(float32 other);
        Vector2& operator+=(const glm::vec2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator-=(float32 other);
        Vector2& operator-=(const glm::vec2& other);
        Vector2& operator*=(const Vector2& other);
        Vector2& operator*=(float32 other);
        Vector2& operator*=(const glm::vec2& other);
        Vector2& operator/=(const Vector2& other);
        Vector2& operator/=(float32 other);
        Vector2& operator/=(const glm::vec2& other);
        Vector2& operator%=(const Vector2& other);
        Vector2& operator%=(float32 other);
        Vector2& operator%=(const glm::vec2& other);

        // Comparison operators
        bool operator==(const Vector2& other) const;
        bool operator==(float32 other) const;
        bool operator==(const glm::vec2& other) const;
        bool operator!=(const Vector2& other) const;
        bool operator!=(float32 other) const;
        bool operator!=(const glm::vec2& other) const;
        bool operator>(const Vector2& other) const;
        bool operator>(float32 other) const;
        bool operator>(const glm::vec2& other) const;
        bool operator>=(const Vector2& other) const;
        bool operator>=(float32 other) const;
        bool operator>=(const glm::vec2& other) const;
        bool operator<(const Vector2& other) const;
        bool operator<(float32 other) const;
        bool operator<(const glm::vec2& other) const;
        bool operator<=(const Vector2& other) const;
        bool operator<=(float32 other) const;
        bool operator<=(const glm::vec2& other) const;

        // Index operators
        float32& operator[](uint32 index);
        float32 operator[](uint32 index) const;

        float32 Magnitude(void) const;
        Vector2 Normalized(void) const;
        float32 Dot(const Vector2& other) const;
        Vector2 Cross(const Vector2& other) const;
        float32 Distance(const Vector2& other) const;

        float32 x;
        float32 y;
    };

    class NT_API Vector3
    {
    public:
        NT_CLASS_DEFAULTS(Vector3)
        Vector3(void);
        Vector3(float32 x, float32 y, float32 z);
        Vector3(float32 value);
        Vector3(float32* values);
        Vector3(const glm::vec3& value);

        // Typecast operators
        operator float32*(void);
        operator glm::vec3(void) const;

        // Sign operators
        Vector3 operator+(void) const;
        Vector3 operator-(void) const;

        // Arithmetic operators
        Vector3 operator+(const Vector3& other) const;
        Vector3 operator+(float32 other) const;
        Vector3 operator+(const glm::vec3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator-(float32 other) const;
        Vector3 operator-(const glm::vec3& other) const;
        Vector3 operator*(const Vector3& other) const;
        Vector3 operator*(float32 other) const;
        Vector3 operator*(const glm::vec3& other) const;
        Vector3 operator/(const Vector3& other) const;
        Vector3 operator/(float32 other) const;
        Vector3 operator/(const glm::vec3& other) const;
        Vector3 operator%(const Vector3& other) const;
        Vector3 operator%(float32 other) const;
        Vector3 operator%(const glm::vec3& other) const;

        // Increment operators
        Vector3& operator++(void);
        Vector3 operator++(int32);
        Vector3& operator--(void);
        Vector3 operator--(int32);

        // Assignment operators
        Vector3& operator+=(const Vector3& other);
        Vector3& operator+=(float32 other);
        Vector3& operator+=(const glm::vec3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator-=(float32 other);
        Vector3& operator-=(const glm::vec3& other);
        Vector3& operator*=(const Vector3& other);
        Vector3& operator*=(float32 other);
        Vector3& operator*=(const glm::vec3& other);
        Vector3& operator/=(const Vector3& other);
        Vector3& operator/=(float32 other);
        Vector3& operator/=(const glm::vec3& other);
        Vector3& operator%=(const Vector3& other);
        Vector3& operator%=(float32 other);
        Vector3& operator%=(const glm::vec3& other);

        // Comparison operators
        bool operator==(const Vector3& other) const;
        bool operator==(float32 other) const;
        bool operator==(const glm::vec3& other) const;
        bool operator!=(const Vector3& other) const;
        bool operator!=(float32 other) const;
        bool operator!=(const glm::vec3& other) const;
        bool operator>(const Vector3& other) const;
        bool operator>(float32 other) const;
        bool operator>(const glm::vec3& other) const;
        bool operator>=(const Vector3& other) const;
        bool operator>=(float32 other) const;
        bool operator>=(const glm::vec3& other) const;
        bool operator<(const Vector3& other) const;
        bool operator<(float32 other) const;
        bool operator<(const glm::vec3& other) const;
        bool operator<=(const Vector3& other) const;
        bool operator<=(float32 other) const;
        bool operator<=(const glm::vec3& other) const;

        // Index operators
        float32& operator[](uint32 index);
        float32 operator[](uint32 index) const;

        float32 Magnitude(void) const;
        Vector3 Normalized(void) const;
        float32 Dot(const Vector3& other) const;
        Vector3 Cross(const Vector3& other) const;
        float32 Distance(const Vector3& other) const;

        float32 x;
        float32 y;
        float32 z;
    };

    class NT_API Vector4
    {
    public:
        NT_CLASS_DEFAULTS(Vector4)
        Vector4(void);
        Vector4(float32 x, float32 y, float32 z, float32 w);
        Vector4(float32 value);
        Vector4(float32* values);
        Vector4(const glm::vec4& value);

        // Typecast operators
        operator float32*(void);
        operator glm::vec4(void) const;

        // Sign operators
        Vector4 operator+(void) const;
        Vector4 operator-(void) const;

        // Arithmetic operators
        Vector4 operator+(const Vector4& other) const;
        Vector4 operator+(float32 other) const;
        Vector4 operator+(const glm::vec4& other) const;
        Vector4 operator-(const Vector4& other) const;
        Vector4 operator-(float32 other) const;
        Vector4 operator-(const glm::vec4& other) const;
        Vector4 operator*(const Vector4& other) const;
        Vector4 operator*(float32 other) const;
        Vector4 operator*(const glm::vec4& other) const;
        Vector4 operator/(const Vector4& other) const;
        Vector4 operator/(float32 other) const;
        Vector4 operator/(const glm::vec4& other) const;
        Vector4 operator%(const Vector4& other) const;
        Vector4 operator%(float32 other) const;
        Vector4 operator%(const glm::vec4& other) const;

        // Increment operators
        Vector4& operator++(void);
        Vector4 operator++(int32);
        Vector4& operator--(void);
        Vector4 operator--(int32);

        // Assignment operators
        Vector4& operator+=(const Vector4& other);
        Vector4& operator+=(float32 other);
        Vector4& operator+=(const glm::vec4& other);
        Vector4& operator-=(const Vector4& other);
        Vector4& operator-=(float32 other);
        Vector4& operator-=(const glm::vec4& other);
        Vector4& operator*=(const Vector4& other);
        Vector4& operator*=(float32 other);
        Vector4& operator*=(const glm::vec4& other);
        Vector4& operator/=(const Vector4& other);
        Vector4& operator/=(float32 other);
        Vector4& operator/=(const glm::vec4& other);
        Vector4& operator%=(const Vector4& other);
        Vector4& operator%=(float32 other);
        Vector4& operator%=(const glm::vec4& other);

        // Comparison operators
        bool operator==(const Vector4& other) const;
        bool operator==(float32 other) const;
        bool operator==(const glm::vec4& other) const;
        bool operator!=(const Vector4& other) const;
        bool operator!=(float32 other) const;
        bool operator!=(const glm::vec4& other) const;
        bool operator>(const Vector4& other) const;
        bool operator>(float32 other) const;
        bool operator>(const glm::vec4& other) const;
        bool operator>=(const Vector4& other) const;
        bool operator>=(float32 other) const;
        bool operator>=(const glm::vec4& other) const;
        bool operator<(const Vector4& other) const;
        bool operator<(float32 other) const;
        bool operator<(const glm::vec4& other) const;
        bool operator<=(const Vector4& other) const;
        bool operator<=(float32 other) const;
        bool operator<=(const glm::vec4& other) const;

        // Index operators
        float32& operator[](uint32 index);
        float32 operator[](uint32 index) const;

        float32 Magnitude(void) const;
        Vector4 Normalized(void) const;
        float32 Dot(const Vector4& other) const;
        Vector4 Cross(const Vector4& other) const;
        float32 Distance(const Vector4& other) const;

        float32 x;
        float32 y;
        float32 z;
        float32 w;
    };
} // namespace Nt

#endif // _MATH_VECTOR_H_
