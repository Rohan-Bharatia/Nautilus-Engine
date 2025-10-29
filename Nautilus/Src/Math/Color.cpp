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

#ifndef _MATH_COLOR_CPP_
    #define _MATH_COLOR_CPP_

#include "Color.h"

namespace Nt
{
    std::ostream& operator<<(std::ostream& stream, const Color& color)
    {
        stream << "(" << color.r << ", " << color.g << ", " << color.b << ")";
        return stream;
    }

    Color CMYKToRGB(float32 c, float32 m, float32 y, float32 k, float32 alpha)
    {
        float32 r = (1.0f - c) * (1.0f - k);
        float32 g = (1.0f - m) * (1.0f - k);
        float32 b = (1.0f - y) * (1.0f - k);
        return Color(r, g, b, alpha);
    }

    Color HSVToRGB(float32 h, float32 s, float32 v, float32 alpha)
    {
        h = std::fmod(h, 360);
        if (h < 0.0f)
            h += 360.0f;

        float32 c = v * s;
        float32 x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float32 m = v - c;

        float32 r, g, b;

        if (h < 60.0f)
        {
            r = c;
            g = x;
            b = 0.0f;
        }
        else if (h < 120.0f)
        {
            r = x;
            g = c;
            b = 0.0f;
        }
        else if (h < 180.0f)
        {
            r = 0.0f;
            g = c;
            b = x;
        }
        else if (h < 240.0f)
        {
            r = 0.0f;
            g = x;
            b = c;
        }
        else if (h < 300.0f)
        {
            r = x;
            g = 0.0f;
            b = c;
        }
        else
        {
            r = c;
            g = 0.0f;
            b = x;
        }

        return Color(r + m, g + m, b + m, alpha);
    }

    Color HSLToRGB(float32 h, float32 s, float32 l, float32 alpha)
    {
        h = std::fmod(h, 360);
        if (h < 0.0f)
            h += 360.0f;

        float32 c = (1.0f - std::abs(2.0f * l - 1.0f)) * s;
        float32 x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float32 m = l - c / 2.0f;

        float32 r, g, b;

        if (h < 60.0f)
        {
            r = c;
            g = x;
            b = 0.0f;
        }
        else if (h < 120.0f)
        {
            r = x;
            g = c;
            b = 0.0f;
        }
        else if (h < 180.0f)
        {
            r = 0.0f;
            g = c;
            b = x;
        }
        else if (h < 240.0f)
        {
            r = 0.0f;
            g = x;
            b = c;
        }
        else if (h < 300.0f)
        {
            r = x;
            g = 0.0f;
            b = c;
        }
        else
        {
            r = c;
            g = 0.0f;
            b = x;
        }

        return Color(r + m, g + m, b + m, alpha);
    }

    Color HexToRGB(uint32 hex, float32 alpha)
    {
        float32 r = ((hex >> 16) & 255) / 255.0f;
        float32 g = ((hex >> 8) & 255) / 255.0f;
        float32 b = (hex & 0xff) / 255.0f;
        return Color(r, g, b, alpha);
    }

    Color OkLabToRGB(float32 l, float32 a, float32 b, float32 alpha)
    {
        float32 L = std::pow(l + 0.3963377774f * a + 0.2158037573f * b, 3);
        float32 M = std::pow(l - 0.1055613458f * a - 0.0638541728f * b, 3);
        float32 S = std::pow(l - 0.0894841775f * a - 1.2914855480f * b, 3);

        float32 r  = +4.0767416621f * L - 3.3077115913f * M + 0.2309699292f * S;
        float32 g  = -1.2684380046f * L + 2.6097574011f * M - 0.3413193965f * S;
        float32 bl = -0.0041960863f * L - 0.7034186147f * M + 1.7076147010f * S;

        return Color(r, g, bl, alpha);
    }
} // namespace Nt

#endif // _MATH_COLOR_CPP_
