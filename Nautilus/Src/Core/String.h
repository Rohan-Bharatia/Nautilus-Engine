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

#ifndef _CORE_STRING_H_
    #define _CORE_STRING_H_

#include "PCH.h"

namespace Nt
{
    class NT_API String
    {
    public:
        NT_CLASS_DEFAULTS(String)
        String(void);
        String(const char* str);
        String(const std::string& str);
        String(const wchar_t* str);
        String(const std::wstring& str);

        operator const char*(void) const;
        operator const std::string&(void) const;
        operator const wchar_t*(void) const;
        operator const std::wstring&(void) const;

        String& operator=(const char* str);
        String& operator=(const std::string& str);
        String& operator=(const wchar_t* str);
        String& operator=(const std::wstring& str);

        String operator+(const char* str) const;
        String operator+(const std::string& str) const;
        String operator+(const wchar_t* str) const;
        String operator+(const std::wstring& str) const;
        String operator+(const String& str) const;

        String& operator+=(const char* str);
        String& operator+=(const std::string& str);
        String& operator+=(const wchar_t* str);
        String& operator+=(const std::wstring& str);
        String& operator+=(const String& str);

        bool operator==(const char* str) const;
        bool operator==(const std::string& str) const;
        bool operator==(const wchar_t* str) const;
        bool operator==(const std::wstring& str) const;
        bool operator==(const String& str) const;

        bool operator!=(const char* str) const;
        bool operator!=(const std::string& str) const;
        bool operator!=(const wchar_t* str) const;
        bool operator!=(const std::wstring& str) const;
        bool operator!=(const String& str) const;

        uint32 Length(void);
        std::vector<String> Split(void);
        std::vector<String> Split(String delim);
        char CharAt(uint32 index);
        bool Contains(String str);
        bool StartsWith(String str);
        bool EndsWith(String str);
        String Substring(uint32 start, uint32 end);
        String Trim(void);
        String& ToLower(void);
        String& ToUpper(void);

    private:
        Ref<std::string> m_data;
    };

    std::ostream& operator<<(std::ostream& stream, const String& str);
} // namespace Nt

namespace std
{
    template<typename T>
    struct hash;

    template<>
    struct hash<Nt::String>
    {
        size_t operator()(const Nt::String& str) const
        {
            return std::hash<std::string>()(((std::string)str).c_str());
        }
    };
}

#endif // _CORE_STRING_H_
