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

#ifndef _CORE_STRING_CPP_
    #define _CORE_STRING_CPP_

#include "String.h"

namespace Nt
{
    static Scope<std::wstring> s_wdata;

    static std::string wstr2str(std::wstring str)
    {
        size_t len = wcstombs(nullptr, str.c_str(), 0) + 1;
        char* buf  = new char[len];
        wcstombs(buf, str.c_str(), len);
        std::string result(buf);
        delete[] buf;
        return result;
    }

    static std::wstring str2wstr(std::string str)
    {
        size_t len   = mbstowcs(nullptr, str.c_str(), 0) + 1;
        wchar_t* buf = new wchar_t[len];
        mbstowcs(buf, str.c_str(), len);
        std::wstring result(buf);
        delete[] buf;
        return result;
    }

    String::String(void) :
        m_data(CreateScope<std::string>(""))
    {
        s_wdata = CreateScope<std::wstring>(L"");
    }

    String::String(const char* str) :
        m_data(CreateScope<std::string>(str))
    {
        s_wdata = CreateScope<std::wstring>(str2wstr(str));
    }

    String::String(const std::string& str) :
        m_data(CreateScope<std::string>(str))
    {
        s_wdata = CreateScope<std::wstring>(str2wstr(str));
    }

    String::String(const wchar_t* str) :
        m_data(CreateScope<std::string>(wstr2str(str)))
    {
        s_wdata = CreateScope<std::wstring>(str);
    }

    String::String(const std::wstring& str) :
        m_data(CreateScope<std::string>(wstr2str(str)))
    {
        s_wdata = CreateScope<std::wstring>(str);
    }

    String::operator const char*(void) const
    {
        return m_data->c_str();
    }

    String::operator const std::string&(void) const
    {
        return *m_data;
    }

    String::operator const wchar_t*(void) const
    {
        return s_wdata->c_str();
    }

    String::operator const std::wstring&(void) const
    {
        return *s_wdata;
    }

    String& String::operator=(const char* str)
    {
        return *this = String(str);
    }

    String& String::operator=(const std::string& str)
    {
        return *this = String(str);
    }

    String& String::operator=(const wchar_t* str)
    {
        return *this = String(str);
    }

    String& String::operator=(const std::wstring& str)
    {
        return *this = String(str);
    }

    String String::operator+(const char* str) const
    {
        return String(m_data->append(str));
    }

    String String::operator+(const std::string& str) const
    {
        return String(m_data->append(str));
    }

    String String::operator+(const wchar_t* str) const
    {
        return String(m_data->append(wstr2str(str)));
    }

    String String::operator+(const std::wstring& str) const
    {
        return String(m_data->append(wstr2str(str)));
    }

    String String::operator+(const String& str) const
    {
        return String(m_data->append(str.m_data->c_str()));
    }

    String& String::operator+=(const char* str)
    {
        return *this = *this + str;
    }

    String& String::operator+=(const std::string& str)
    {
        return *this = *this + str;
    }

    String& String::operator+=(const wchar_t* str)
    {
        return *this = *this + str;
    }

    String& String::operator+=(const std::wstring& str)
    {
        return *this = *this + str;
    }

    String& String::operator+=(const String& str)
    {
        return *this = *this + str;
    }

    bool String::operator==(const char* str) const
    {
        return *m_data == str;
    }

    bool String::operator==(const std::string& str) const
    {
        return *m_data == str;
    }

    bool String::operator==(const wchar_t* str) const
    {
        return *s_wdata == str;
    }

    bool String::operator==(const std::wstring& str) const
    {
        return *s_wdata == str;
    }

    bool String::operator==(const String& str) const
    {
        return *m_data == *str.m_data;
    }

    bool String::operator!=(const char* str) const
    {
        return !(*this == str);
    }

    bool String::operator!=(const std::string& str) const
    {
        return !(*this == str);
    }

    bool String::operator!=(const wchar_t* str) const
    {
        return !(*this == str);
    }

    bool String::operator!=(const std::wstring& str) const
    {
        return !(*this == str);
    }

    bool String::operator!=(const String& str) const
    {
        return !(*this == str);
    }

    uint32 String::Length(void)
    {
        return m_data->length();
    }

    std::vector<String> String::Split(void)
    {
        return Split(" ");
    }

    std::vector<String> String::Split(String delim)
    {
        std::vector<String> result;
        size_t start = 0;
        size_t end   = m_data->find(delim.m_data->c_str());
        while (end != std::string::npos)
        {
            result.push_back(String(m_data->substr(start, end - start)));
            start = end + delim.Length();
            end   = m_data->find(delim.m_data->c_str(), start);
        }
        result.push_back(String(m_data->substr(start)));
        return result;
    }

    char String::CharAt(uint32 index)
    {
        return m_data->at(index);
    }

    bool String::Contains(String str)
    {
        return m_data->find(str.m_data->c_str()) != std::string::npos;
    }

    bool String::StartsWith(String str)
    {
        return m_data->find(str.m_data->c_str()) == 0;
    }

    bool String::EndsWith(String str)
    {
        return m_data->find(str.m_data->c_str()) == m_data->length() - str.Length();
    }

    String String::Substring(uint32 start, uint32 end)
    {
        return String(m_data->substr(start, end - start));
    }

    String String::Trim(void)
    {
        return String(m_data->replace(m_data->find_first_not_of(" \t\r\n"), m_data->find_last_not_of(" \t\r\n") + 1, ""));
    }

    String& String::ToLower(void)
    {
        std::transform(m_data->begin(), m_data->end(), m_data->begin(), ::tolower);
        return *this;
    }

    String& String::ToUpper(void)
    {
        std::transform(m_data->begin(), m_data->end(), m_data->begin(), ::toupper);
        return *this;
    }
} // namespace Nt

#endif // _CORE_STRING_CPP_
