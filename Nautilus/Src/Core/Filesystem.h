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

#ifndef _CORE_FILESYSTEM_H_
    #define _CORE_FILESYSTEM_H_

#include "PCH.h"

namespace fs = std::filesystem;

namespace Nt
{
    struct NT_API File
    {
        NT_STRUCT_DEFAULTS(File)
        File(void);
        File(const String& name, const String& path, const String& content);

        uint32 Size(void);

        operator String(void) const;

        String name;
        String path;
        String content;
    };

    class NT_API Filesystem
    {
    public:
        NT_CLASS_DEFAULTS(Filesystem)
        Filesystem(void);
        Filesystem(const String& root);

        bool DirectoryExists(const String& path);
        bool CreateDirectory(const String& path);
        bool DeleteDirectory(const String& path);
        bool FileExists(const String& path);
        bool CreateFile(const String& path, const String& content="");
        String ReadFile(const String& path);
        bool WriteFile(const String& path, const String& content);
        bool DeleteFile(const String& path);
        std::vector<File> ListFiles(const String& base="");

    private:
        fs::path m_root;
        std::unordered_map<String, File> m_files = {};
    };
} // namespace Nt

#endif // _CORE_FILESYSTEM_H_
