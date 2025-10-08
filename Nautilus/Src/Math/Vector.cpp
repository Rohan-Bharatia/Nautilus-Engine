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

#ifndef _MATH_VECTOR_CPP_
    #define _MATH_VECTOR_CPP_

#include "Vector.h"

#include "Angle.h"

namespace Nt
{
    Vector2::Vector2(void) :
        x(0.0f), y(0.0f)
    {}

    Vector2::Vector2(float32 x, float32 y) :
        x(x), y(y)
    {}

    Vector2::Vector2(float32 value) :
        x(value), y(value)
    {}

    Vector2::Vector2(float32* values) :
        x(values[0]), y(values[1])
    {}

    Vector2::Vector2(const glm::vec2& value) :
        x(value.x), y(value.y)
    {}

    Vector2::Vector2(float32 magnitude, const Angle& angle) :
        x(magnitude * std::cosf(angle.Radians())), y(magnitude * std::sinf(angle.Radians()))
    {}

    Vector2::operator float32*(void)
    {
        float32* values = new float32[2];
        values[0] = x;
        values[1] = y;
        return values;
    }

    Vector2::operator glm::vec2(void) const
    {
        return glm::vec2(x, y);
    }

    Vector2 Vector2::operator+(void) const
    {
        return Vector2(+x, +y);
    }

    Vector2 Vector2::operator-(void) const
    {
        return Vector2(-x, -y);
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator+(float32 other) const
    {
        return Vector2(x + other, y + other);
    }

    Vector2 Vector2::operator+(const glm::vec2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator-(float32 other) const
    {
        return Vector2(x - other, y - other);
    }

    Vector2 Vector2::operator-(const glm::vec2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 Vector2::operator*(float32 other) const
    {
        return Vector2(x * other, y * other);
    }

    Vector2 Vector2::operator*(const glm::vec2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 Vector2::operator/(const Vector2& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 Vector2::operator/(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Vector2(x / other, y / other);
    }

    Vector2 Vector2::operator/(const glm::vec2& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 Vector2::operator%(const Vector2& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return Vector2(std::fmod(x, other.x), std::fmod(y, other.y));
    }

    Vector2 Vector2::operator%(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Vector2(std::fmod(x, other), std::fmod(y, other));
    }

    Vector2 Vector2::operator%(const glm::vec2& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return Vector2(std::fmod(x, other.x), std::fmod(y, other.y));
    }

    Vector2& Vector2::operator++(void)
    {
        ++x;
        ++y;
        return *this;
    }

    Vector2 Vector2::operator++(int32)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    Vector2& Vector2::operator--(void)
    {
        --x;
        --y;
        return *this;
    }

    Vector2 Vector2::operator--(int32)
    {
        auto temp = *this;
        --*this;
        return temp;
    }

    Vector2& Vector2::operator+=(const Vector2& other)
    {
        return *this = *this + other;
    }

    Vector2& Vector2::operator+=(float32 other)
    {
        return *this = *this + other;
    }

    Vector2& Vector2::operator+=(const glm::vec2& other)
    {
        return *this = *this + other;
    }

    Vector2& Vector2::operator-=(const Vector2& other)
    {
        return *this = *this - other;
    }

    Vector2& Vector2::operator-=(float32 other)
    {
        return *this = *this - other;
    }

    Vector2& Vector2::operator-=(const glm::vec2& other)
    {
        return *this = *this - other;
    }

    Vector2& Vector2::operator*=(const Vector2& other)
    {
        return *this = *this * other;
    }

    Vector2& Vector2::operator*=(float32 other)
    {
        return *this = *this * other;
    }

    Vector2& Vector2::operator*=(const glm::vec2& other)
    {
        return *this = *this * other;
    }

    Vector2& Vector2::operator/=(const Vector2& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector2& Vector2::operator/=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector2& Vector2::operator/=(const glm::vec2& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector2& Vector2::operator%=(const Vector2& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Vector2& Vector2::operator%=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Vector2& Vector2::operator%=(const glm::vec2& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    bool Vector2::operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator==(float32 other) const
    {
        return x == other && y == other;
    }

    bool Vector2::operator==(const glm::vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other) const
    {
        return x != other.x || y != other.y;
    }

    bool Vector2::operator!=(float32 other) const
    {
        return x != other || y != other;
    }

    bool Vector2::operator!=(const glm::vec2& other) const
    {
        return x != other.x || y != other.y;
    }

    bool Vector2::operator>(const Vector2& other) const
    {
        return x > other.x && y > other.y;
    }

    bool Vector2::operator>(float32 other) const
    {
        return x > other && y > other;
    }

    bool Vector2::operator>(const glm::vec2& other) const
    {
        return x > other.x && y > other.y;
    }

    bool Vector2::operator>=(const Vector2& other) const
    {
        return x >= other.x && y >= other.y;
    }

    bool Vector2::operator>=(float32 other) const
    {
        return x >= other && y >= other;
    }

    bool Vector2::operator>=(const glm::vec2& other) const
    {
        return x >= other.x && y >= other.y;
    }

    bool Vector2::operator<(const Vector2& other) const
    {
        return x < other.x && y < other.y;
    }

    bool Vector2::operator<(float32 other) const
    {
        return x < other && y < other;
    }

    bool Vector2::operator<(const glm::vec2& other) const
    {
        return x < other.x && y < other.y;
    }

    bool Vector2::operator<=(const Vector2& other) const
    {
        return x <= other.x && y <= other.y;
    }

    bool Vector2::operator<=(float32 other) const
    {
        return x <= other && y <= other;
    }

    bool Vector2::operator<=(const glm::vec2& other) const
    {
        return x <= other.x && y <= other.y;
    }

    float32& Vector2::operator[](uint32 index)
    {
        NT_ASSERT(index < 2, "Index out of range");
        return (&x)[index];
    }

    float32 Vector2::operator[](uint32 index) const
    {
        NT_ASSERT(index < 2, "Index out of range");
        return (&x)[index];
    }

    float32 Vector2::Magnitude(void) const
    {
        return std::sqrtf(x * x + y * y);
    }

    Vector2 Vector2::Normalized(void) const
    {
        float32 magnitude = Magnitude();
        return Vector2(x / magnitude, y / magnitude);
    }

    float32 Vector2::Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    Vector2 Vector2::Cross(const Vector2& other) const
    {
        return Vector2(x * other.y - y * other.x, y * other.x - x * other.y);
    }

    float32 Vector2::Distance(const Vector2& other) const
    {
        return (*this - other).Magnitude();
    }

    Angle Vector2::AngleBetween(const Vector2& other) const
    {
        return Angle(std::acosf(Dot(other) / (Magnitude() * other.Magnitude())));
    }

    Vector3::Vector3(void) :
        x(0.0f), y(0.0f), z(0.0f)
    {}

    Vector3::Vector3(float32 x, float32 y, float32 z) :
        x(x), y(y), z(z)
    {}

    Vector3::Vector3(float32 value) :
        x(value), y(value), z(value)
    {}

    Vector3::Vector3(float32* values) :
        x(values[0]), y(values[1]), z(values[2])
    {}

    Vector3::Vector3(const glm::vec3& value) :
        x(value.x), y(value.y), z(value.z)
    {}

    Vector3::Vector3(float32 magnitude, const Angle& angle) :
        x(magnitude * std::cosf(angle.Radians())), y(magnitude * std::sinf(angle.Radians())), z(0.0f)
    {}

    Vector3::operator float32*(void)
    {
        float32* values = new float32[3];
        values[0] = x;
        values[1] = y;
        values[2] = z;
        return values;
    }

    Vector3::operator glm::vec3(void) const
    {
        return glm::vec3(x, y, z);
    }

    Vector3 Vector3::operator+(void) const
    {
        return Vector3(+x, +y, +z);
    }


    Vector3 Vector3::operator-(void) const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator+(float32 other) const
    {
        return Vector3(x + other, y + other, z + other);
    }

    Vector3 Vector3::operator+(const glm::vec3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator-(float32 other) const
    {
        return Vector3(x - other, y - other, z - other);
    }

    Vector3 Vector3::operator-(const glm::vec3& other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator*(const Vector3& other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 Vector3::operator*(float32 other) const
    {
        return Vector3(x * other, y * other, z * other);
    }

    Vector3 Vector3::operator*(const glm::vec3& other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 Vector3::operator/(const Vector3& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    Vector3 Vector3::operator/(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Vector3(x / other, y / other, z / other);
    }

    Vector3 Vector3::operator/(const glm::vec3& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    Vector3 Vector3::operator%(const Vector3& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return Vector3(std::fmod(x, other.x), std::fmod(y, other.y), std::fmod(z, other.z));
    }

    Vector3 Vector3::operator%(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Vector3(std::fmod(x, other), std::fmod(y, other), std::fmod(z, other));
    }

    Vector3 Vector3::operator%(const glm::vec3& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return Vector3(std::fmod(x, other.x), std::fmod(y, other.y), std::fmod(z, other.z));
    }

    Vector3& Vector3::operator++(void)
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    Vector3 Vector3::operator++(int32)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    Vector3& Vector3::operator--(void)
    {
        --x;
        --y;
        --z;
        return *this;
    }

    Vector3 Vector3::operator--(int32)
    {
        auto temp = *this;
        --*this;
        return temp;
    }

    Vector3& Vector3::operator+=(const Vector3& other)
    {
        return *this = *this + other;
    }

    Vector3& Vector3::operator+=(float32 other)
    {
        return *this = *this + other;
    }

    Vector3& Vector3::operator+=(const glm::vec3& other)
    {
        return *this = *this + other;
    }

    Vector3& Vector3::operator-=(const Vector3& other)
    {
        return *this = *this - other;
    }

    Vector3& Vector3::operator-=(float32 other)
    {
        return *this = *this - other;
    }

    Vector3& Vector3::operator-=(const glm::vec3& other)
    {
        return *this = *this - other;
    }

    Vector3& Vector3::operator*=(const Vector3& other)
    {
        return *this = *this * other;
    }

    Vector3& Vector3::operator*=(float32 other)
    {
        return *this = *this * other;
    }

    Vector3& Vector3::operator*=(const glm::vec3& other)
    {
        return *this = *this * other;
    }

    Vector3& Vector3::operator/=(const Vector3& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector3& Vector3::operator/=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector3& Vector3::operator/=(const glm::vec3& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector3& Vector3::operator%=(const Vector3& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Vector3& Vector3::operator%=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Vector3& Vector3::operator%=(const glm::vec3& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    bool Vector3::operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool Vector3::operator==(float32 other) const
    {
        return x == other && y == other && z == other;
    }

    bool Vector3::operator==(const glm::vec3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool Vector3::operator!=(const Vector3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    bool Vector3::operator!=(float32 other) const
    {
        return x != other || y != other || z != other;
    }

    bool Vector3::operator!=(const glm::vec3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    bool Vector3::operator>(const Vector3& other) const
    {
        return x > other.x && y > other.y && z > other.z;
    }

    bool Vector3::operator>(float32 other) const
    {
        return x > other && y > other && z > other;
    }

    bool Vector3::operator>(const glm::vec3& other) const
    {
        return x > other.x && y > other.y && z > other.z;
    }

    bool Vector3::operator>=(const Vector3& other) const
    {
        return x >= other.x && y >= other.y && z >= other.z;
    }

    bool Vector3::operator>=(float32 other) const
    {
        return x >= other && y >= other && z >= other;
    }

    bool Vector3::operator>=(const glm::vec3& other) const
    {
        return x >= other.x && y >= other.y && z >= other.z;
    }

    bool Vector3::operator<(const Vector3& other) const
    {
        return x < other.x && y < other.y && z < other.z;
    }

    bool Vector3::operator<(float32 other) const
    {
        return x < other && y < other && z < other;
    }

    bool Vector3::operator<(const glm::vec3& other) const
    {
        return x < other.x && y < other.y && z < other.z;
    }

    bool Vector3::operator<=(const Vector3& other) const
    {
        return x <= other.x && y <= other.y && z <= other.z;
    }

    bool Vector3::operator<=(float32 other) const
    {
        return x <= other && y <= other && z <= other;
    }

    bool Vector3::operator<=(const glm::vec3& other) const
    {
        return x <= other.x && y <= other.y && z <= other.z;
    }

    float32& Vector3::operator[](uint32 index)
    {
        NT_ASSERT(index < 3, "Index out of range");
        return (&x)[index];
    }

    float32 Vector3::operator[](uint32 index) const
    {
        NT_ASSERT(index < 3, "Index out of range");
        return (&x)[index];
    }

    float32 Vector3::Magnitude(void) const
    {
        return std::sqrtf(x * x + y * y + z * z);
    }

    Vector3 Vector3::Normalized(void) const
    {
        float32 magnitude = Magnitude();
        return Vector3(x / magnitude, y / magnitude, z / magnitude);
    }

    float32 Vector3::Dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::Cross(const Vector3& other) const
    {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    float32 Vector3::Distance(const Vector3& other) const
    {
        return (*this - other).Magnitude();
    }

    Angle Vector3::AngleBetween(const Vector3& other) const
    {
        return Angle(std::acosf(Dot(other) / (Magnitude() * other.Magnitude())));
    }

    Vector4::Vector4(void) :
        x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {}

    Vector4::Vector4(float32 x, float32 y, float32 z, float32 w) :
        x(x), y(y), z(z), w(w)
    {}

    Vector4::Vector4(float32 value) :
        x(value), y(value), z(value), w(value)
    {}

    Vector4::Vector4(float32* values) :
        x(values[0]), y(values[1]), z(values[2]), w(values[3])
    {}

    Vector4::Vector4(const glm::vec4& value) :
        x(value.x), y(value.y), z(value.z), w(value.w)
    {}

    Vector4::Vector4(float32 magnitude, const Angle& angle) :
        x(magnitude * std::cosf(angle.Radians())), y(magnitude * std::sinf(angle.Radians())), z(0.0f), w(0.0f)
    {}

    Vector4::operator float32*(void)
    {
        float32* result = new float32[4];
        result[0] = x;
        result[1] = y;
        result[2] = z;
        result[3] = w;
        return result;
    }

    Vector4::operator glm::vec4(void) const
    {
        return glm::vec4(x, y, z, w);
    }

    Vector4::operator glm::quat(void) const
    {
        return glm::quat(w, x, y, z);
    }

    Vector4 Vector4::operator+(void) const
    {
        return Vector4(+x, +y, +z, +w);
    }

    Vector4 Vector4::operator-(void) const
    {
        return Vector4(-x, -y, -z, -w);
    }

    Vector4 Vector4::operator+(const Vector4& other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 Vector4::operator+(float32 other) const
    {
        return Vector4(x + other, y + other, z + other, w + other);
    }

    Vector4 Vector4::operator+(const glm::vec4& other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 Vector4::operator-(const Vector4& other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 Vector4::operator-(float32 other) const
    {
        return Vector4(x - other, y - other, z - other, w - other);
    }

    Vector4 Vector4::operator-(const glm::vec4& other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 Vector4::operator*(const Vector4& other) const
    {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vector4 Vector4::operator*(float32 other) const
    {
        return Vector4(x * other, y * other, z * other, w * other);
    }

    Vector4 Vector4::operator*(const glm::vec4& other) const
    {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vector4 Vector4::operator/(const Vector4& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vector4 Vector4::operator/(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Vector4(x / other, y / other, z / other, w / other);
    }

    Vector4 Vector4::operator/(const glm::vec4& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vector4 Vector4::operator%(const Vector4& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return Vector4(std::fmod(x, other.x), std::fmod(y, other.y), std::fmod(z, other.z), std::fmod(w, other.w));
    }

    Vector4 Vector4::operator%(float32 other) const
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return Vector4(std::fmod(x, other), std::fmod(y, other), std::fmod(z, other), std::fmod(w, other));
    }

    Vector4 Vector4::operator%(const glm::vec4& other) const
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return Vector4(std::fmod(x, other.x), std::fmod(y, other.y), std::fmod(z, other.z), std::fmod(w, other.w));
    }

    Vector4& Vector4::operator++(void)
    {
        ++x;
        ++y;
        ++z;
        ++w;
        return *this;
    }

    Vector4 Vector4::operator++(int32)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    Vector4& Vector4::operator--(void)
    {
        --x;
        --y;
        --z;
        --w;
        return *this;
    }

    Vector4 Vector4::operator--(int32)
    {
        auto temp = *this;
        --*this;
        return temp;
    }

    Vector4& Vector4::operator+=(const Vector4& other)
    {
        return *this = *this + other;
    }

    Vector4& Vector4::operator+=(float32 other)
    {
        return *this = *this + other;
    }

    Vector4& Vector4::operator+=(const glm::vec4& other)
    {
        return *this = *this + other;
    }

    Vector4& Vector4::operator-=(const Vector4& other)
    {
        return *this = *this - other;
    }

    Vector4& Vector4::operator-=(float32 other)
    {
        return *this = *this - other;
    }

    Vector4& Vector4::operator-=(const glm::vec4& other)
    {
        return *this = *this - other;
    }

    Vector4& Vector4::operator*=(const Vector4& other)
    {
        return *this = *this * other;
    }

    Vector4& Vector4::operator*=(float32 other)
    {
        return *this = *this * other;
    }

    Vector4& Vector4::operator*=(const glm::vec4& other)
    {
        return *this = *this * other;
    }

    Vector4& Vector4::operator/=(const Vector4& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector4& Vector4::operator/=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector4& Vector4::operator/=(const glm::vec4& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return *this = *this / other;
    }

    Vector4& Vector4::operator%=(const Vector4& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Vector4& Vector4::operator%=(float32 other)
    {
        NT_ASSERT(other != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    Vector4& Vector4::operator%=(const glm::vec4& other)
    {
        NT_ASSERT(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f, "Cannot divide by zero");
        return *this = *this % other;
    }

    bool Vector4::operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool Vector4::operator==(float32 other) const
    {
        return x == other && y == other && z == other && w == other;
    }

    bool Vector4::operator==(const glm::vec4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool Vector4::operator!=(const Vector4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    bool Vector4::operator!=(float32 other) const
    {
        return x != other || y != other || z != other || w != other;
    }

    bool Vector4::operator!=(const glm::vec4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    bool Vector4::operator>(const Vector4& other) const
    {
        return x > other.x && y > other.y && z > other.z && w > other.w;
    }

    bool Vector4::operator>(float32 other) const
    {
        return x > other && y > other && z > other && w > other;
    }

    bool Vector4::operator>(const glm::vec4& other) const
    {
        return x > other.x && y > other.y && z > other.z && w > other.w;
    }

    bool Vector4::operator>=(const Vector4& other) const
    {
        return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
    }

    bool Vector4::operator>=(float32 other) const
    {
        return x >= other && y >= other && z >= other && w >= other;
    }

    bool Vector4::operator>=(const glm::vec4& other) const
    {
        return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
    }

    bool Vector4::operator<(const Vector4& other) const
    {
        return x < other.x && y < other.y && z < other.z && w < other.w;
    }

    bool Vector4::operator<(float32 other) const
    {
        return x < other && y < other && z < other && w < other;
    }

    bool Vector4::operator<(const glm::vec4& other) const
    {
        return x < other.x && y < other.y && z < other.z && w < other.w;
    }

    bool Vector4::operator<=(const Vector4& other) const
    {
        return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
    }

    bool Vector4::operator<=(float32 other) const
    {
        return x <= other && y <= other && z <= other && w <= other;
    }

    bool Vector4::operator<=(const glm::vec4& other) const
    {
        return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
    }

    float32& Vector4::operator[](uint32 index)
    {
        NT_ASSERT(index < 4, "Index out of range");
        return (&x)[index];
    }

    float32 Vector4::operator[](uint32 index) const
    {
        NT_ASSERT(index < 4, "Index out of range");
        return (&x)[index];
    }

    float32 Vector4::Magnitude(void) const
    {
        return std::sqrtf(x * x + y * y + z * z + w * w);
    }

    Vector4 Vector4::Normalized(void) const
    {
        float32 magnitude = Magnitude();
        return Vector4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
    }

    float32 Vector4::Dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    Vector4 Vector4::Cross(const Vector4& other) const
    {
        return Vector4(y * other.z - z * other.y, z * other.w - w * other.z, w * other.x - x * other.w, x * other.y - y * other.x);
    }

    float32 Vector4::Distance(const Vector4& other) const
    {
        return (*this - other).Magnitude();
    }

    Angle Vector4::AngleBetween(const Vector4& other) const
    {
        return Angle(std::acosf(Dot(other) / (Magnitude() * other.Magnitude())));
    }

    std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
    {
        stream << "(" << vector.x << ", " << vector.y << ")";
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
    {
        stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
    {
        stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
        return stream;
    }
} // namespace Nt

#endif // _MATH_VECTOR_CPP_
