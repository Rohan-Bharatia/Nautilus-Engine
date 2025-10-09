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

#ifndef _MATH_MATRIX_H_
    #define _MATH_MATRIX_H_

#include "Vector.h"

namespace Nt
{
    class NT_API Matrix3
    {
    public:
        NT_CLASS_DEFAULTS(Matrix3)
        Matrix3(void);
        Matrix3(float32 value);
        Matrix3(float32* value);
        Matrix3(const glm::mat3& value);

        // Typecast operators
        operator float32*(void) const;
        operator glm::mat3(void) const;

        // Sign operators
        Matrix3 operator+(void) const;
        Matrix3 operator-(void) const;

        // Arithmetic operators
        Matrix3 operator+(const Matrix3& value) const;
        Matrix3 operator+(float32 value) const;
        Matrix3 operator-(const Matrix3& value) const;
        Matrix3 operator-(float32 value) const;
        Matrix3 operator*(const Matrix3& value) const;
        Matrix3 operator*(float32 value) const;
        Matrix3 operator/(const Matrix3& value) const;
        Matrix3 operator/(float32 value) const;
        Matrix3 operator%(const Matrix3& value) const;
        Matrix3 operator%(float32 value) const;

        // Increment operators
        Matrix3& operator++(void);
        Matrix3 operator++(int32);
        Matrix3& operator--(void);
        Matrix3 operator--(int32);

        // Assignment operators
        Matrix3& operator+=(const Matrix3& value);
        Matrix3& operator+=(float32 value);
        Matrix3& operator-=(const Matrix3& value);
        Matrix3& operator-=(float32 value);
        Matrix3& operator*=(const Matrix3& value);
        Matrix3& operator*=(float32 value);
        Matrix3& operator/=(const Matrix3& value);
        Matrix3& operator/=(float32 value);
        Matrix3& operator%=(const Matrix3& value);
        Matrix3& operator%=(float32 value);

        // Comparison operators
        bool operator==(const Matrix3& value) const;
        bool operator==(const float32& value) const;
        bool operator!=(const Matrix3& value) const;
        bool operator!=(const float32& value) const;
        bool operator>(const Matrix3& value) const;
        bool operator>(const float32& value) const;
        bool operator>=(const Matrix3& value) const;
        bool operator>=(const float32& value) const;
        bool operator<(const Matrix3& value) const;
        bool operator<(const float32& value) const;
        bool operator<=(const Matrix3& value) const;
        bool operator<=(const float32& value) const;

        float32& operator[](uint32 index);
        float32 operator[](uint32 index) const;

        float32* mat;
    };

    class NT_API Matrix4
    {
    public:
        NT_CLASS_DEFAULTS(Matrix4)
        Matrix4(void);
        Matrix4(float32 value);
        Matrix4(float32* value);
        Matrix4(const glm::mat4& value);
        Matrix4(const Matrix3& value);

        // Typecast operators
        operator float32*(void) const;
        operator glm::mat4(void) const;

        // Sign operators
        Matrix4 operator+(void) const;
        Matrix4 operator-(void) const;

        // Arithmetic operators
        Matrix4 operator+(const Matrix4& value) const;
        Matrix4 operator+(float32 value) const;
        Matrix4 operator-(const Matrix4& value) const;
        Matrix4 operator-(float32 value) const;
        Matrix4 operator*(const Matrix4& value) const;
        Matrix4 operator*(float32 value) const;
        Matrix4 operator/(const Matrix4& value) const;
        Matrix4 operator/(float32 value) const;
        Matrix4 operator%(const Matrix4& value) const;
        Matrix4 operator%(float32 value) const;

        // Increment operators
        Matrix4& operator++(void);
        Matrix4 operator++(int32);
        Matrix4& operator--(void);
        Matrix4 operator--(int32);

        // Assignment operators
        Matrix4& operator+=(const Matrix4& value);
        Matrix4& operator+=(float32 value);
        Matrix4& operator-=(const Matrix4& value);
        Matrix4& operator-=(float32 value);
        Matrix4& operator*=(const Matrix4& value);
        Matrix4& operator*=(float32 value);
        Matrix4& operator/=(const Matrix4& value);
        Matrix4& operator/=(float32 value);
        Matrix4& operator%=(const Matrix4& value);
        Matrix4& operator%=(float32 value);

        // Comparison operators
        bool operator==(const Matrix4& value) const;
        bool operator==(const float32& value) const;
        bool operator!=(const Matrix4& value) const;
        bool operator!=(const float32& value) const;
        bool operator>(const Matrix4& value) const;
        bool operator>(const float32& value) const;
        bool operator>=(const Matrix4& value) const;
        bool operator>=(const float32& value) const;
        bool operator<(const Matrix4& value) const;
        bool operator<(const float32& value) const;
        bool operator<=(const Matrix4& value) const;
        bool operator<=(const float32& value) const;

        float32& operator[](uint32 index);
        float32 operator[](uint32 index) const;

        float32* mat;
    };
} // namespace Nt

#endif // _MATH_MATRIX_H_
