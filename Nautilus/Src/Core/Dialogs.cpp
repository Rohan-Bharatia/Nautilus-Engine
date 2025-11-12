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

#ifndef _CORE_DIALOGS_CPP_
    #define _CORE_DIALOGS_CPP_

#include "Dialogs.h"

namespace Nt
{
    static std::vector<SDL_DialogFileFilter> MakeFilters(const std::vector<Filter>& filters)
    {
        std::vector<SDL_DialogFileFilter> result;
        result.reserve(filters.size());

        for (const Filter& filter : filters)
        {
            SDL_DialogFileFilter f;
            new (&f) SDL_DialogFileFilter{ std::move(filter.name), std::move(filter.pattern) };
            result.push_back(f);
        }

        return result;
    }

    struct FileDialogSync
    {
        std::mutex mutex;
        std::condition_variable cv;
        std::vector<String> files;
        bool done = false;
    };

    static void SDLCALL FileDialogCallback(void* userdata, const char* const* filelist, int filterIndex)
    {
        auto* sync = NT_STATIC_CAST(FileDialogSync*, userdata);
        std::unique_lock<std::mutex> lock(sync->mutex);

        if (filelist)
        {
            for (const char* const* f = filelist; *f; ++f)
                sync->files.emplace_back(*f);
        }

        sync->done = true;
        lock.unlock();
        sync->cv.notify_one();
    }

    String OpenFileDialog(Window* window, const std::vector<Filter>& filters)
    {
        FileDialogSync sync;
        auto sdlFilters = MakeFilters(filters);

        SDL_ShowOpenFileDialog(FileDialogCallback, &sync, (SDL_Window*)window->GetNativeWindow(), sdlFilters.empty() ? nullptr : sdlFilters.data(), (int32)sdlFilters.size(), nullptr, false);

        std::unique_lock<std::mutex> lock(sync.mutex);
        sync.cv.wait(lock, [&]() { return sync.done; });
        return sync.files.empty() ? String("") : sync.files.front();
    }

    std::vector<String> OpenMultiFileDialog(Window* window, const std::vector<Filter>& filters)
    {
        FileDialogSync sync;
        auto sdlFilters = MakeFilters(filters);

        SDL_ShowOpenFileDialog(FileDialogCallback, &sync, (SDL_Window*)window->GetNativeWindow(), sdlFilters.empty() ? nullptr : sdlFilters.data(), (int32)sdlFilters.size(), nullptr, true);

        std::unique_lock<std::mutex> lock(sync.mutex);
        sync.cv.wait(lock, [&]() { return sync.done; });
        return sync.files;
    }

    void OpenURL(const String& url)
    {
        SDL_OpenURL((const char*)url);
    }
} // namespace Nt

#endif // _CORE_DIALOGS_CPP_
