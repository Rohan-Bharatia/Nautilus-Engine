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
    using Vector2    = glm::vec2;
    using Vector3    = glm::vec3;
    using Vector4    = glm::vec4;
    using Quaternion = glm::quat;

    std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
    std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
    std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
    std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
} // namespace Nt

#endif // _MATH_VECTOR_H_
