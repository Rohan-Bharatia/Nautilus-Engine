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

#ifndef _CORE_FILESYSTEM_CPP_
    #define _CORE_FILESYSTEM_CPP_

#include "Filesystem.h"

#include "IO.h"

namespace Nt
{
    File::File(void) :
        name(""), path(""), content("")
    {}

    File::File(const String& name, const String& path, const String& content) :
        name(name), path(path), content(content)
    {}

    uint32 File::Size(void)
    {
        return content.Length();
    }

    File::operator String(void) const
    {
        return content;
    }

    Filesystem::Filesystem(void)
    {
        m_root = fs::current_path();
    }

    Filesystem::Filesystem(const String& root)
    {
        m_root = fs::absolute((std::string)root);
        if (!fs::exists(m_root))
            fs::create_directories(m_root);
    }

    bool Filesystem::DirectoryExists(const String& path)
    {
        return fs::exists((std::string)path);
    }

    bool Filesystem::CreateDirectory(const String& path)
    {
        if (fs::exists((std::string)path))
        {
            NT_CORE_WARN("Directory %s already exists", (const char*)path);
            return false;
        }

        return fs::create_directories((std::string)path);
    }

    bool Filesystem::DeleteDirectory(const String& path)
    {
        if (!fs::exists((std::string)path))
        {
            NT_CORE_ERROR("Directory %s does not exist", (const char*)path);
            return false;
        }

        fs::remove_all((std::string)path);

        for (auto it = m_files.begin(); it != m_files.end();)
        {
            if (String(it->second.path) == path)
                it = m_files.erase(it);
            else
                ++it;
        }

        return true;
    }

    bool Filesystem::FileExists(const String& path)
    {
        if (m_files.find(path) == m_files.end())
            return false;
        return true;
    }

    bool Filesystem::CreateFile(const String& path, const String& content)
    {
        if (m_files.find(path) != m_files.end())
        {
            NT_CORE_ERROR("File %s already exists", (const char*)path);
            return false;
        }

        fs::path p = m_root / (std::string)path;
        fs::create_directories(p.parent_path());

        std::ofstream out(p);
        if (!out)
        {
            NT_CORE_ERROR("Failed to create file %s", (const char*)path);
            return false;                                            }

        out << content;
        out.close();
        m_files[path] = File(String(p.filename().string()), String(path), String(content));

        return true;
    }

    String Filesystem::ReadFile(const String& path)
    {
        if (m_files.find(path) == m_files.end())
        {
            fs::path p = m_root / (std::string)path;
            if (!fs::exists(p))
            {
                NT_CORE_ERROR("File %s does not exist", (const char*)path);
                return "";
            }

            std::ifstream in(p);
            if (!in)
            {
                NT_CORE_ERROR("Failed to read file %s", (const char*)path);
                return "";
            }

            std::string content((std::istreambuf_iterator<char>(in)),
                                (std::istreambuf_iterator<char>()));
            in.close();

            m_files[path] = File(String(p.filename().string()), String(path), String(content));
        }

        return m_files[path].content;
    }

    bool Filesystem::WriteFile(const String& path, const String& content)
    {
        fs::path p = m_root / (std::string)path;
        if (!fs::exists(p))
        {
            NT_CORE_ERROR("File %s does not exist", (const char*)path);
            return false;
        }

        std::ofstream out(p);
        if (!out)
        {
            NT_CORE_ERROR("Failed to write file %s", (const char*)path);
            return false;
        }

        out << content;
        out.close();
        m_files[path] = File(String(p.filename().string()), String(path), String(content));

        return true;
    }

    bool Filesystem::DeleteFile(const String& path)
    {
        fs::path p = m_root / (std::string)path;
        if (!fs::exists(p))
        {
            NT_CORE_ERROR("File %s does not exist", (const char*)path);
            return false;
        }

        fs::remove(p);
        return m_files.erase(path) > 0;
    }

    std::vector<File> Filesystem::ListFiles(const String& base)
    {
        std::vector<File> files;
        for (auto it = m_files.begin(); it != m_files.end(); ++it)
        {
            if (((std::string)it->second.path).find((std::string)base) == std::string::npos)
                files.push_back(it->second);
        }
        return files;
    }
} // namespace Nt

#endif // _CORE_FILESYSTEM_CPP_
