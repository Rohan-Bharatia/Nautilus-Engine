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

#ifndef _MATH_MATRIX_CPP_
    #define _MATH_MATRIX_CPP_

#include "Matrix.h"

namespace Nt
{
    Matrix3::Matrix3(void)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                mat[i * 3 + j] = 0.0f;
    }

    Matrix3::Matrix3(float32 value)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                mat[i * 3 + j] = i == j ? value : 0.0f;
    }

    Matrix3::Matrix3(float32* values)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                mat[i * 3 + j] = values[i * 3 + j];
    }

    Matrix3::Matrix3(const glm::mat3& value)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                mat[i * 3 + j] = value[i][j];
    }

    Matrix3::operator float32*(void) const
    {
        return mat;
    }

    Matrix3::operator glm::mat3(void) const
    {
        glm::mat3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result[i][j] = mat[i * 3 + j];
        return result;
    }

    Matrix3 Matrix3::operator+(void) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = +mat[i * 3 + j];
        return result;
    }

    Matrix3 Matrix3::operator-(void) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = -mat[i * 3 + j];
        return result;
    }

    Matrix3 Matrix3::operator+(const Matrix3& other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + j] + other.mat[i * 3 + j];
        return result;
    }

    Matrix3 Matrix3::operator+(float32 other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + j] + other;
        return result;
    }

    Matrix3 Matrix3::operator-(const Matrix3& other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + j] - other.mat[i * 3 + j];
        return result;
    }

    Matrix3 Matrix3::operator-(float32 other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + j] - other;
        return result;
    }

    Matrix3 Matrix3::operator*(const Matrix3& other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + 0] * other.mat[0 * 3 + j] + mat[i * 3 + 1] * other.mat[1 * 3 + j] + mat[i * 3 + 2] * other.mat[2 * 3 + j] + mat[i * 3 + 3] * other.mat[3 * 3 + j];
        return result;
    }

    Matrix3 Matrix3::operator*(float32 other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + j] * other;
        return result;
    }

    Matrix3 Matrix3::operator/(const Matrix3& other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
        {
            for (int32 j = 0; j < 3; ++j)
            {
                NT_ASSERT(other.mat[i * 3 + j] != 0.0f, "Cannot divide by zero");
                result.mat[i * 3 + j] = mat[i * 3 + j] / other.mat[i * 3 + j];
            }
        }
        return result;
    }

    Matrix3 Matrix3::operator/(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = mat[i * 3 + j] / other;
        return result;
    }

    Matrix3 Matrix3::operator%(const Matrix3& other) const
    {
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
        {
            for (int32 j = 0; j < 3; ++j)
            {
                NT_ASSERT(other.mat[i * 3 + j] != 0.0f, "Cannot divide by zero");
                result.mat[i * 3 + j] = std::fmod(mat[i * 3 + j], other.mat[i * 3 + j]);
            }
        }
        return result;
    }

    Matrix3 Matrix3::operator%(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        Matrix3 result;
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                result.mat[i * 3 + j] = std::fmod(mat[i * 3 + j], other);
        return result;
    }

    Matrix3& Matrix3::operator++(void)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                ++mat[i * 3 + j];
        return *this;
    }

    Matrix3 Matrix3::operator++(int32)
    {
        Matrix3 temp = *this;
        ++*this;
        return temp;
    }

    Matrix3& Matrix3::operator--(void)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                --mat[i * 3 + j];
        return *this;
    }

    Matrix3 Matrix3::operator--(int32)
    {
        Matrix3 temp = *this;
        --*this;
        return temp;
    }

    Matrix3& Matrix3::operator+=(const Matrix3& value)
    {
        return *this = *this + value;
    }

    Matrix3& Matrix3::operator+=(float32 value)
    {
        return *this = *this + value;
    }

    Matrix3& Matrix3::operator-=(const Matrix3& value)
    {
        return *this = *this - value;
    }

    Matrix3& Matrix3::operator-=(float32 value)
    {
        return *this = *this - value;
    }

    Matrix3& Matrix3::operator*=(const Matrix3& value)
    {
        return *this = *this * value;
    }

    Matrix3& Matrix3::operator*=(float32 value)
    {
        return *this = *this * value;
    }

    Matrix3& Matrix3::operator/=(const Matrix3& value)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                NT_ASSERT(value.mat[i * 3 + j] != 0.0f, "Cannot divide by zero");
        return *this = *this / value;
    }

    Matrix3& Matrix3::operator/=(float32 value)
    {
        NT_ASSERT(value != 0.0f, "Cannot divide by zero");
        return *this = *this / value;
    }

    Matrix3& Matrix3::operator%=(const Matrix3& value)
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                NT_ASSERT(value.mat[i * 3 + j] != 0.0f, "Cannot divide by zero");
        return *this = *this % value;
    }

    Matrix3& Matrix3::operator%=(float32 value)
    {
        NT_ASSERT(value != 0.0f, "Cannot divide by zero");
        return *this = *this % value;
    }

    bool Matrix3::operator==(const Matrix3& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] != value.mat[i * 3 + j])
                    return false;
        return true;
    }

    bool Matrix3::operator==(const float32& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] != value)
                    return false;
        return true;
    }

    bool Matrix3::operator!=(const Matrix3& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] != value.mat[i * 3 + j])
                    return true;
        return false;
    }

    bool Matrix3::operator!=(const float32& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] != value)
                    return true;
        return false;
    }

    bool Matrix3::operator>(const Matrix3& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] > value.mat[i * 3 + j])
                    return true;
        return false;
    }

    bool Matrix3::operator>(const float32& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] > value)
                    return true;
        return false;
    }

    bool Matrix3::operator>=(const Matrix3& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] >= value.mat[i * 3 + j])
                    return true;
        return false;
    }

    bool Matrix3::operator>=(const float32& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] >= value)
                    return true;
        return false;
    }

    bool Matrix3::operator<(const Matrix3& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] < value.mat[i * 3 + j])
                    return true;
        return false;
    }

    bool Matrix3::operator<(const float32& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] < value)
                    return true;
        return false;
    }

    bool Matrix3::operator<=(const Matrix3& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] <= value.mat[i * 3 + j])
                    return true;
        return false;
    }

    bool Matrix3::operator<=(const float32& value) const
    {
        for (int32 i = 0; i < 3; ++i)
            for (int32 j = 0; j < 3; ++j)
                if (mat[i * 3 + j] <= value)
                    return true;
        return false;
    }

    float32& Matrix3::operator[](uint32 index)
    {
        NT_ASSERT(index <= 9, "Index out of range");
        return mat[index];
    }

    float32 Matrix3::operator[](uint32 index) const
    {
        NT_ASSERT(index <= 9, "Index out of range");
        return mat[index];
    }

    Matrix4::Matrix4(void)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                mat[i * 4 + j] = 0.0f;
    }

    Matrix4::Matrix4(float32 value)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                mat[i * 4 + j] = i == j ? value : 0.0f;
    }

    Matrix4::Matrix4(float32* values)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                mat[i * 4 + j] = values[i * 4 + j];
    }

    Matrix4::Matrix4(const glm::mat4& value)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                mat[i * 4 + j] = value[i][j];
    }

    Matrix4::Matrix4(const Matrix3& value)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                mat[i * 4 + j] = i < 3 && j < 3 ? value.mat[i * 3 + j] : 0.0f;
    }

    Matrix4::operator float32*(void) const
    {
        return mat;
    }

    Matrix4::operator glm::mat4(void) const
    {
        glm::mat4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result[i][j] = mat[i * 4 + j];
        return result;
    }

    Matrix4 Matrix4::operator+(void) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = +mat[i * 4 + j];
        return result;
    }

    Matrix4 Matrix4::operator-(void) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = -mat[i * 4 + j];
        return result;
    }

    Matrix4 Matrix4::operator+(const Matrix4& other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + j] + other.mat[i * 4 + j];
        return result;
    }

    Matrix4 Matrix4::operator+(float32 other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + j] + other;
        return result;
    }

    Matrix4 Matrix4::operator-(const Matrix4& other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + j] - other.mat[i * 4 + j];
        return result;
    }

    Matrix4 Matrix4::operator-(float32 other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + j] - other;
        return result;
    }

    Matrix4 Matrix4::operator*(const Matrix4& other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + 0] * other.mat[0 * 4 + j] + mat[i * 4 + 1] * other.mat[1 * 4 + j] + mat[i * 4 + 2] * other.mat[2 * 4 + j] + mat[i * 4 + 3] * other.mat[3 * 4 + j];
        return result;
    }

    Matrix4 Matrix4::operator*(float32 other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + j] * other;
        return result;
    }

    Matrix4 Matrix4::operator/(const Matrix4& other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
        {
            for (int32 j = 0; j < 4; ++j)
            {
                NT_ASSERT(other.mat[i * 4 + j] != 0.0f, "Cannot divide by zero");
                result.mat[i * 4 + j] = mat[i * 4 + j] / other.mat[i * 4 + j];
            }
        }
        return result;
    }

    Matrix4 Matrix4::operator/(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = mat[i * 4 + j] / other;
        return result;
    }

    Matrix4 Matrix4::operator%(const Matrix4& other) const
    {
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
        {
            for (int32 j = 0; j < 4; ++j)
            {
                NT_ASSERT(other.mat[i * 4 + j] != 0.0f, "Cannot divide by zero");
                result.mat[i * 4 + j] = std::fmod(mat[i * 4 + j], other.mat[i * 4 + j]);
            }
        }
        return result;
    }

    Matrix4 Matrix4::operator%(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        Matrix4 result;
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                result.mat[i * 4 + j] = std::fmod(mat[i * 4 + j], other);
        return result;
    }

    Matrix4& Matrix4::operator++(void)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                ++mat[i * 4 + j];
        return *this;
    }

    Matrix4 Matrix4::operator++(int32)
    {
        Matrix4 temp = *this;
        ++*this;
        return temp;
    }

    Matrix4& Matrix4::operator--(void)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                --mat[i * 4 + j];
        return *this;
    }

    Matrix4 Matrix4::operator--(int32)
    {
        Matrix4 temp = *this;
        --*this;
        return temp;
    }

    Matrix4& Matrix4::operator+=(const Matrix4& value)
    {
        return *this = *this + value;
    }

    Matrix4& Matrix4::operator+=(float32 value)
    {
        return *this = *this + value;
    }

    Matrix4& Matrix4::operator-=(const Matrix4& value)
    {
        return *this = *this - value;
    }

    Matrix4& Matrix4::operator-=(float32 value)
    {
        return *this = *this - value;
    }

    Matrix4& Matrix4::operator*=(const Matrix4& value)
    {
        return *this = *this * value;
    }

    Matrix4& Matrix4::operator*=(float32 value)
    {
        return *this = *this * value;
    }

    Matrix4& Matrix4::operator/=(const Matrix4& value)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                NT_ASSERT(value.mat[i * 4 + j] != 0.0f, "Cannot divide by zero");
        return *this = *this / value;
    }

    Matrix4& Matrix4::operator/=(float32 value)
    {
        NT_ASSERT(value != 0.0f, "Cannot divide by zero");
        return *this = *this / value;
    }

    Matrix4& Matrix4::operator%=(const Matrix4& value)
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                NT_ASSERT(value.mat[i * 4 + j] != 0.0f, "Cannot divide by zero");
        return *this = *this % value;
    }

    Matrix4& Matrix4::operator%=(float32 value)
    {
        NT_ASSERT(value != 0.0f, "Cannot divide by zero");
        return *this = *this % value;
    }

    bool Matrix4::operator==(const Matrix4& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] != value.mat[i * 4 + j])
                    return false;
        return true;
    }

    bool Matrix4::operator==(const float32& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] != value)
                    return false;
        return true;
    }

    bool Matrix4::operator!=(const Matrix4& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] != value.mat[i * 4 + j])
                    return true;
        return false;
    }

    bool Matrix4::operator!=(const float32& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] != value)
                    return true;
        return false;
    }

    bool Matrix4::operator>(const Matrix4& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] > value.mat[i * 4 + j])
                    return true;
        return false;
    }

    bool Matrix4::operator>(const float32& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] > value)
                    return true;
        return false;
    }

    bool Matrix4::operator>=(const Matrix4& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] >= value.mat[i * 4 + j])
                    return true;
        return false;
    }

    bool Matrix4::operator>=(const float32& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] >= value)
                    return true;
        return false;
    }

    bool Matrix4::operator<(const Matrix4& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] < value.mat[i * 4 + j])
                    return true;
        return false;
    }

    bool Matrix4::operator<(const float32& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] < value)
                    return true;
        return false;
    }

    bool Matrix4::operator<=(const Matrix4& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] <= value.mat[i * 4 + j])
                    return true;
        return false;
    }

    bool Matrix4::operator<=(const float32& value) const
    {
        for (int32 i = 0; i < 4; ++i)
            for (int32 j = 0; j < 4; ++j)
                if (mat[i * 4 + j] <= value)
                    return true;
        return false;
    }

    float32& Matrix4::operator[](uint32 index)
    {
        NT_ASSERT(index <= 16, "Index out of range");
        return mat[index];
    }

    float32 Matrix4::operator[](uint32 index) const
    {
        NT_ASSERT(index <= 16, "Index out of range");
        return mat[index];
    }
} // namespace Nt

#endif // _MATH_MATRIX_CPP_
