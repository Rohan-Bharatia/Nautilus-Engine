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

#ifndef _PCH_H_
    #define _PCH_H_

// C++ standard version detection
#ifdef _MSC_VER
    #define NT_CPP_VERSION _MSVC_LANG
#else // (NOT) _MSC_VER
    #define NT_CPP_VERSION __cplusplus
#endif // _MSC_VER
#define NT_CPP98 199711L
#define NT_CPP11 201103L
#define NT_CPP14 201402L
#define NT_CPP17 201703L
#define NT_CPP20 202002L
#define NT_CPP23 202302L
#define NT_CHECK_CPP_VERSION(version) (NT_CPP_VERSION >= version)
#if !NT_CHECK_CPP_VERSION(NT_CPP17)
    #error Nautilus Engine requires C++17 or higher!
#endif // !NT_CHECK_CPP_VERSION(NT_CPP17)

// C/C++ standard library headers
#ifndef _GLIBCXX_NO_ASSERT
    #include <cassert>
#endif // _GLIBCXX_NO_ASSERT
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#if NT_CHECK_CPP_VERSION(NT_CPP11)
    #include <cfenv>
    #include <cinttypes>
    #include <cstdint>
    #include <cuchar>
#endif // NT_CHECK_CPP_VERSION(NT_CPP11)
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#if NT_CHECK_CPP_VERSION(NT_CPP11)
    #include <array>
    #include <atomic>
    #include <chrono>
    #include <codecvt>
    #include <condition_variable>
    #include <forward_list>
    #include <future>
    #include <initializer_list>
    #include <mutex>
    #include <random>
    #include <ratio>
    #include <regex>
    #include <scoped_allocator>
    #include <system_error>
    #include <thread>
    #include <tuple>
    #include <typeindex>
    #include <type_traits>
    #include <unordered_map>
    #include <unordered_set>
#endif // NT_CHECK_CPP_VERSION(NT_CPP11)
#if NT_CHECK_CPP_VERSION(NT_CPP14)
    #include <shared_mutex>
#endif // NT_CHECK_CPP_VERSION(NT_CPP14)
#if NT_CHECK_CPP_VERSION(NT_CPP17)
    #include <any>
    #include <charconv>
    #include <execution>
    #include <filesystem>
    #include <optional>
    #include <memory_resource>
    #include <string_view>
    #include <variant>
#endif // NT_CHECK_CPP_VERSION(NT_CPP17)
#if NT_CHECK_CPP_VERSION(NT_CPP20)
    #include <barrier>
    #include <bit>
    #include <compare>
    #include <concepts>
    #if defined(__cpp_impl_coroutine)
        #include <coroutine>
    #endif // defined(__cpp_impl_coroutine)
    #include <latch>
    #include <numbers>
    #include <ranges>
    #include <span>
    #include <stop_token>
    #include <semaphore>
    #include <source_location>
    #include <syncstream>
    #include <version>
#endif // NT_CHECK_CPP_VERSION(NT_CPP20)

// Compiler detection
#if defined(__clang__)
    #define NT_COMPILER_CLANG
    #define NT_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
    #define NT_CHECK_COMPILER_VERSION(version) (NT_CLANG_VERSION >= version)
    #define NT_DEPRECATED(msg) __attribute__((__deprecated__(msg)))
    #define NT_PRETTY_FUNCTION __PRETTY_FUNCTION__
    #define NT_PRAGMA(x) _Pragma(#x)
    #define NT_WARNING_DISABLE(warn) NT_PRAGMA(clang diagnostic ignored warn)
    #define NT_WARNING_POP() NT_PRAGMA(clang diagnostic pop)
    #define NT_WARNING_PUSH() NT_PRAGMA(clang diagnostic push)
    #define NT_UNUSED __attribute__((unused))
    #define NT_INLINE __attribute__((always_inline)) inline
    #define NT_NORETURN __attribute__((noreturn))
    #define NT_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
    #define NT_FALLTHROUGH __attribute__((fallthrough))
    #define NT_NODISCARD __attribute__((warn_unused_result))
    #define NT_MALLOC __attribute__((malloc))
    #define NT_ALLOC_SIZE(ptr) __attribute__((alloc_size(1)))
    #define NT_ALLOC_SIZE2(ptr1, ptr2) __attribute__((alloc_size(1, 2)))
    #ifdef __MINGW32__
        #define NT_COMPILER_MINGW
        #ifdef __MINGW64_VERSION_MAJOR
            #define NT_COMPILER_MINGW_W64
        #endif // __MINGW64_VERSION_MAJOR
    #endif // __MINGW32__
#elif defined(__GNUC__) || defined(__MINGW32__)
    #define NT_COMPILER_GCC
    #define NT_COMPILER_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
    #define NT_CHECK_COMPILER_VERSION(version) (NT_GCC_VERSION >= version)
    #define NT_DEPRECATED(msg) __attribute__((__deprecated__(msg)))
    #define NT_PRETTY_FUNCTION __PRETTY_FUNCTION__
    #define NT_PRAGMA(x) _Pragma(#x)
    #define NT_WARNING_DISABLE(warn) NT_PRAGMA(GCC diagnostic ignored warn)
    #define NT_WARNING_POP() NT_PRAGMA(GCC diagnostic pop)
    #define NT_WARNING_PUSH() NT_PRAGMA(GCC diagnostic push)
    #define NT_UNUSED __attribute__((unused))
    #define NT_INLINE __attribute__((always_inline)) inline
    #define NT_NORETURN __attribute__((noreturn))
    #define NT_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
    #define NT_FALLTHROUGH __attribute__((fallthrough))
    #define NT_NODISCARD __attribute__((warn_unused_result))
    #define NT_MALLOC __attribute__((malloc))
    #define NT_ALLOC_SIZE(ptr) __attribute__((alloc_size(1)))
    #define NT_ALLOC_SIZE2(ptr1, ptr2) __attribute__((alloc_size(1, 2)))
    #ifdef __MINGW32__
        #define NT_COMPILER_MINGW
        #ifdef __MINGW64_VERSION_MAJOR
            #define NT_COMPILER_MINGW_W64
        #endif // __MINGW64_VERSION_MAJOR
    #endif // __MINGW32__
#elif defined(__INTEL_COMPILER) || defined(__ICL)
    #define NT_COMPILER_INTEL
    #define NT_COMPILER_VERSION (__INTEL_COMPILER)
    #define NT_CHECK_COMPILER_VERSION(version) (NT_INTEL_VERSION >= version)
    #define NT_DEPRECATED(msg) [[deprecated(msg)]]
    #define NT_PRETTY_FUNCTION __FUNCTION__
    #define NT_PRAGMA(x) _Pragma(#x)
    #define NT_WARNING_DISABLE(warn) NT_PRAGMA(warning(disable : warn))
    #define NT_WARNING_POP() NT_PRAGMA(warning(pop))
    #define NT_WARNING_PUSH() NT_PRAGMA(warning(push))
    #define NT_UNUSED __declspec(unused)
    #define NT_INLINE inline
    #define NT_NORETURN __declspec(noreturn)
    #define NT_ANALYZER_NORETURN __declspec(analyzer_noreturn)
    #define NT_FALLTHROUGH __declspec(fallthrough)
    #define NT_NODISCARD __declspec(nodiscard)
    #define NT_MALLOC __declspec(malloc)
    #define NT_ALLOC_SIZE(ptr) __declspec(alloc_size(1))
    #define NT_ALLOC_SIZE2(ptr1, ptr2) __declspec(alloc_size(1, 2))
#elif defined(_MSC_VER)
    #define NT_COMPILER_MSVC
    #define NT_COMPILER_VERSION (_MSC_VER)
    #define NT_CHECK_COMPILER_VERSION(version) (NT_MSVC_VERSION >= version)
    #define NT_DEPRECATED(msg) __declspec(deprecated(msg))
    #define NT_PRETTY_FUNCTION __FUNCSIG__
    #define NT_PRAGMA(x) __pragma(x)
    #define NT_WARNING_DISABLE(warn) NT_PRAGMA(warning(disable : warn))
    #define NT_WARNING_POP() NT_PRAGMA(warning(pop))
    #define NT_WARNING_PUSH() NT_PRAGMA(warning(push))
    #define NT_UNUSED __declspec(unused)
    #define NT_INLINE __forceinline
    #define NT_NORETURN __declspec(noreturn)
    #define NT_ANALYZER_NORETURN __declspec(analyzer_noreturn)
    #define NT_FALLTHROUGH __declspec(fallthrough)
    #define NT_NODISCARD __declspec(nodiscard)
    #define NT_MALLOC __declspec(malloc)
    #define NT_ALLOC_SIZE(ptr) __declspec(alloc_size(1))
    #define NT_ALLOC_SIZE2(ptr1, ptr2) __declspec(alloc_size(1, 2))
#else // (NOT) defined(__clang__), defined(__GNUC__) || defined(__MINGW32__), defined(__INTEL_COMPILER) || defined(__ICL), defined(_MSC_VER)
    #define NT_COMPILER_UNKNOWN
    #define NT_COMPILER_VERSION 0
    #define NT_CHECK_COMPILER_VERSION(version) false
    #define NT_DEPRECATED(msg)
    #define NT_PRETTY_FUNCTION
    #define NT_PRAGMA(x)
    #define NT_WARNING_DISABLE(warn)
    #define NT_WARNING_POP()
    #define NT_WARNING_PUSH()
    #define NT_UNUSED
    #define NT_INLINE
    #define NT_NORETURN
    #define NT_ANALYZER_NORETURN
    #define NT_FALLTHROUGH
    #define NT_NODISCARD
    #define NT_MALLOC
    #define NT_ALLOC_SIZE(ptr)
    #define NT_ALLOC_SIZE2(ptr1, ptr2)
    #error Nautilus Engine does not support this compiler!
#endif // defined(__clang__), defined(__GNUC__) || defined(__MINGW32__), defined(__INTEL_COMPILER) || defined(__ICL), defined(_MSC_VER)

#ifdef NT_COMPILER_MINGW
    #if defined(__USING_MCFGTHREAD__)
        #define NT_COMPILER_MINGW_THREADS_MCF
    #elif defined(_REENTRANT)
        #define NT_COMPILER_MINGW_THREADS_POSIX
    #else // (NOT) defined(__USING_MCFGTHREAD__), defined(_REENTRANT)
        #define NT_COMPILER_MINGW_THREADS_WIN32
    #endif // defined(__USING_MCFGTHREAD__), defined(_REENTRANT)
#endif // NT_COMPILER_MINGW

// Platform detection
#if defined(_WIN32)
    #ifdef _WIN64
        #ifndef WIN32_LEAN_AND_MEAN
            #define WIN32_LEAN_AND_MEAN
        #endif // WIN32_LEAN_AND_MEAN
        #ifndef NOMINMAX
            #define NOMINMAX
        #endif // NOMINMAX
        #ifndef UNICODE
            #define UNICODE
        #endif // UNICODE
        #include <winapifamily.h>
        #if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
            #define NT_PLATFORM_WINDOWS
            #define NT_PLATFORM_NAME "Windows"
            #define NT_DEVICE_DESKTOP
            #include <Windows.h>
        #elif WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
            #if defined(_GAMING_XBOX_XBOXONE)
                #define NT_PLATFORM_XBOX_ONE
                #define NT_PLATFORM_NAME "Xbox One"
                #define NT_DEVICE_CONSOLE
                #include <xdk.h>
            #elif defined(_GAMING_XBOX_XBOX_SCARLETT)
                #define NT_PLATFORM_XBOX_SERIES
                #define NT_PLATFORM_NAME "Xbox Series X/S"
                #define NT_DEVICE_CONSOLE
                #include <xdk.h>
            #else // (NOT) defined(_GAMING_XBOX_XBOXONE), defined(_GAMING_XBOX_XBOX_SCARLETT)
                #define NT_PLATFORM_XBOX
                #define NT_PLATFORM_NAME "Xbox (UWP)"
                #define NT_DEVICE_CONSOLE
                #include <IUnknown.h>
            #endif // defined(_GAMING_XBOX_XBOXONE), defined(_GAMING_XBOX_XBOX_SCARLETT)
        #else // (NOT) WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP), WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
            #define NT_PLATFORM_UNKNOWN
            #define NT_PLATFORM_NAME "Unknown Microsoft Platform"
            #define NT_DEVICE_UNKNOWN
            #error Nautilus Engine does not support this Microsoft platform!
        #endif // WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP), WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
    #else // (NOT) _WIN64
        #define NT_PLATFORM_UNKNOWN
        #define NT_PLATFORM_NAME "Unsupported (x86) Windows"
        #define NT_DEVICE_UNKNOWN
        #error Nautilus Engine does not support x86 Windows!
    #endif // _WIN64
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define NT_PLATFORM_IOS
        #define NT_PLATFORM_NAME "iOS"
        #define NT_DEVICE_MOBILE
        #include <UIKit/UIKit.h>
    #elif TARGET_OS_MAC || TARGET_OS_OSX
        #define NT_PLATFORM_MACOS
        #define NT_PLATFORM_NAME "macOS"
        #define NT_DEVICE_DESKTOP
        #include <AppKit/AppKit.h>
    #elif TARGET_OS_WATCH
        #define NT_PLATFORM_WATCHOS
        #define NT_PLATFORM_NAME "watchOS"
        #define NT_DEVICE_EMBEDDED
        #include <WatchKit/WatchKit.h>
    #elif TARGET_OS_TV
        #define NT_PLATFORM_TVOS
        #define NT_PLATFORM_NAME "tvOS"
        #define NT_DEVICE_EMBEDDED
        #include <TVMLKit/TVMLKit.h>
    #elif TARGET_OS_EMBEDDED
        #define NT_PLATFORM_EMBEDDED
        #define NT_PLATFORM_NAME "embeddedOS"
        #define NT_DEVICE_EMBEDDED
        #include <CoreFoundation/CoreFoundation.h>
    #else // (NOT) TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR, TARGET_OS_MAC || TARGET_OS_OSX, TARGET_OS_WATCH, TARGET_OS_TV, TARGET_OS_EMBEDDED
        #define NT_PLATFORM_UNKNOWN
        #define NT_PLATFORM_NAME "Unknown Apple Platform"
        #define NT_DEVICE_UNKNOWN
        #error Nautilus Engine does not support this Apple platform!
    #endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR, TARGET_OS_MAC || TARGET_OS_OSX, TARGET_OS_WATCH, TARGET_OS_TV, TARGET_OS_EMBEDDED
#elif defined(__ANDROID__)
    #define NT_PLATFORM_ANDROID
    #define NT_PLATFORM_NAME "Android"
    #define NT_DEVICE_MOBILE
    #include <android/native_activity.h>
    #include <android/native_window.h>
#elif defined(__ORBIS__)
    #define NT_PLATFORM_PS4
    #define NT_PLATFORM_NAME "PlayStation 4"
    #define NT_DEVICE_CONSOLE
#elif defined(__PROSPERO__)
    #define NT_PLATFORM_PS5
    #define NT_PLATFORM_NAME "PlayStation 5"
    #define NT_DEVICE_CONSOLE
#elif defined(__NX__)
    #define NT_PLATFORM_SWITCH
    #define NT_PLATFORM_NAME "Nintendo Switch"
    #define NT_DEVICE_CONSOLE
#elif defined(__vita__)
    #define NT_PLATFORM_PS_VITA
    #define NT_PLATFORM_NAME "PlayStation Vita"
    #define NT_DEVICE_CONSOLE
#elif defined(__EMSCRIPTEN__)
    #define NT_PLATFORM_WASM
    #define NT_PLATFORM_NAME "WebAssembly"
    #define NT_DEVICE_WEB
#elif defined(__QNX__)
    #define NT_PLATFORM_QNX
    #define NT_PLATFORM_NAME "QNX Nucleus"
    #define NT_DEVICE_EMBEDDED
#elif defined(__linux__)
    #define NT_PLATFORM_LINUX
    #define NT_PLATFORM_NAME "Linux"
    #define NT_DEVICE_DESKTOP
#elif defined(__FreeBSD__)
    #define NT_PLATFORM_FREEBSD
    #define NT_PLATFORM_NAME "FreeBSD"
    #define NT_DEVICE_DESKTOP
#elif defined(__NetBSD__)
    #define NT_PLATFORM_NETBSD
    #define NT_PLATFORM_NAME "NetBSD"
    #define NT_DEVICE_DESKTOP
#elif defined(__OpenBSD__)
    #define NT_PLATFORM_OPENBSD
    #define NT_PLATFORM_NAME "OpenBSD"
    #define NT_DEVICE_DESKTOP
#elif defined(__DragonFly__)
    #define NT_PLATFORM_DRAGONFLY
    #define NT_PLATFORM_NAME "DragonFly BSD"
    #define NT_DEVICE_DESKTOP
#elif defined(__HAIKU__)
    #define NT_PLATFORM_HAIKU
    #define NT_PLATFORM_NAME "Haiku OS"
    #define NT_DEVICE_DESKTOP
#elif defined(__sun)
    #define NT_PLATFORM_SOLARIS
    #define NT_PLATFORM_NAME "Solaris"
    #define NT_DEVICE_DESKTOP
#else // (NOT) defined(_WIN32), defined(__APPLE__), defined(__ANDROID__), defined(__ORBIS__), defined(__PROSPERO__), defined(__NX__), defined(__vita__), defined(__EMSCRIPTEN__), defined(__QNX__), defined(__linux__), defined(__FreeBSD__), defined(__NetBSD__), defined(__OpenBSD__), defined(__DragonFly__), defined(__HAIKU__), defined(__sun)
    #define NT_PLATFORM_UNKNOWN
    #define NT_PLATFORM_NAME "Unknown"
    #define NT_DEVICE_UNKNOWN
    #error Nautilus Engine does not support this platform!
#endif // defined(_WIN32), defined(__APPLE__), defined(__ANDROID__), defined(__ORBIS__), defined(__PROSPERO__), defined(__NX__), defined(__vita__), defined(__EMSCRIPTEN__), defined(__QNX__), defined(__linux__), defined(__FreeBSD__), defined(__NetBSD__), defined(__OpenBSD__), defined(__DragonFly__), defined(__HAIKU__), defined(__sun)

#if defined(NT_PLATFORM_WINDOWS) || defined(NT_PLATFORM_XBOX_ONE) || defined(NT_PLATFORM_XBOX_SERIES) || defined(NT_PLATFORM_XBOX)
    #define NT_PLATFORM_FAMILY_MICROSOFT
#elif defined(NT_PLATFORM_MACOS) || defined(NT_PLATFORM_IOS) || defined(NT_PLATFORM_WATCHOS) || defined(NT_PLATFORM_TVOS) || defined(NT_PLATFORM_EMBEDDED)
    #define NT_PLATFORM_FAMILY_APPLE
#elif defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_FREEBSD) || defined(NT_PLATFORM_NETBSD) || defined(NT_PLATFORM_OPENBSD) || defined(NT_PLATFORM_DRAGONFLY) || defined(NT_PLATFORM_HAIKU) || defined(NT_PLATFORM_SOLARIS)
    #define NT_PLATFORM_FAMILY_UNIX
    #include <X11/Xlib.h>
    #ifdef None
        #undef None
    #endif // None
    #if __has_include(<wayland-client.h>)
        #include <wayland-client.h>
    #endif // __has_include(<wayland-client.h>)
#else // (NOT) defined(NT_PLATFORM_WINDOWS) || defined(NT_PLATFORM_XBOX_ONE) || defined(NT_PLATFORM_XBOX_SERIES) || defined(NT_PLATFORM_XBOX), defined(NT_PLATFORM_MACOS) || defined(NT_PLATFORM_IOS) || defined(NT_PLATFORM_WATCHOS) || defined(NT_PLATFORM_TVOS) || defined(NT_PLATFORM_EMBEDDED), defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_FREEBSD) || defined(NT_PLATFORM_NETBSD) || defined(NT_PLATFORM_OPENBSD) || defined(NT_PLATFORM_DRAGONFLY) || defined(NT_PLATFORM_HAIKU) || defined(NT_PLATFORM_SOLARIS)
    #define NT_PLATFORM_FAMILY_UNKNOWN
#endif // defined(NT_PLATFORM_WINDOWS) || defined(NT_PLATFORM_XBOX_ONE) || defined(NT_PLATFORM_XBOX_SERIES) || defined(NT_PLATFORM_XBOX), defined(NT_PLATFORM_MACOS) || defined(NT_PLATFORM_IOS) || defined(NT_PLATFORM_WATCHOS) || defined(NT_PLATFORM_TVOS) || defined(NT_PLATFORM_EMBEDDED), defined(NT_PLATFORM_LINUX) || defined(NT_PLATFORM_FREEBSD) || defined(NT_PLATFORM_NETBSD) || defined(NT_PLATFORM_OPENBSD) || defined(NT_PLATFORM_DRAGONFLY) || defined(NT_PLATFORM_HAIKU) || defined(NT_PLATFORM_SOLARIS)

// Endianess check
#if defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN
    #define NT_ENDIAN_BIG
#elif defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN
    #define NT_ENDIAN_LITTLE
#else // (NOT) defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN, defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN
    #define NT_ENDIAN_UNKNOWN
    #error Nautilus Engine does not support this endianess!
#endif // defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN, defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN

// Nautilus API macros
#ifdef NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_EXPORT __declspec(dllexport)
    #define NT_IMPORT __declspec(dllimport)
#else // (NOT) NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_EXPORT __attribute__((__visibility__("default")))
    #define NT_IMPORT __attribute__((__visibility__("default")))
#endif // NT_PLATFORM_FAMILY_MICROSOFT
#ifndef NT_MODULE
    #define NT_API NT_EXPORT
#else // (NOT) NT_MODULE
    #ifdef NT_EXECUTABLE
        #define NT_API NT_IMPORT
    #else // (NOT) NT_EXECUTABLE
        #define NT_API static
    #endif // NT_EXECUTABLE
#endif // NT_MODULE

// Build modes
#if defined(NDEBUG) || defined(_NDEBUG)
    #define NT_RELEASE
#else // (NOT) defined(NDEBUG) || defined(_NDEBUG)
    #define NT_DEBUG
#endif // defined(NDEBUG) || defined(_NDEBUG)

// Class literal operation allowance
#if !defined(NT_COMPILER_MSVC) || _MSC_VER > 1800
    #define NT_ALLOW_LITERALS
#endif // !defined(NT_COMPILER_MSVC) || _MSC_VER > 1800

// Miscellaneous macros
#define NT_EXPAND(x) x
#define __NT_PREFIX__(a, prefix) prefix##a
#define NT_PREFIX(a, prefix) __NT_PREFIX__(a, prefix)
#define __NT_SUFFIX__(a, suffix) a##suffix
#define NT_SUFFIX(a, suffix) __NT_SUFFIX__(a, suffix)
#define __NT_CONCAT__(a, b) a##b
#define NT_CONCAT(a, b) __NT_CONCAT__(a, b)
#define __NT_STRINGIFY__(x) #x
#define NT_STRINGIFY(x) __NT_STRINGIFY__(x)
#define NT_EXPAND(x) x
#define NT_DISCARD(x) (void)x
#define NT_CLEAR(x) memset(&x, 0, sizeof(x))
#define NT_ARRAY_COUNT(x) (sizeof(x) / sizeof(x[0]))
#define NT_SAFE_DELETE(ptr) delete ptr; ptr = nullptr
#define NT_SAFE_DELETE_ARRAY(ptr) delete[] ptr; ptr = nullptr
#define NT_MODULUS(T, a, b) (a - NT_STATIC_CAST(T, NT_STATIC_CAST(Nt::int32, a / b)) * b) >= NT_STATIC_CAST(T, 0) ? (a - static_cast<T>(static_cast<Nt::int32>(a / b)) * b) : (a - static_cast<T>(static_cast<Nt::int32>(a / b) - 1) * b) + b
#define NT_CLAMP(x, min, max) ((x < min) ? min : ((x > max) ? max : x))
#define NT_LERP(a, b, t) (a + ((b - a) * t))
#define NT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define NT_CLASS_DEFAULTS(classname)                  \
    classname(const classname&)            = default; \
    classname(classname&&)                 = default; \
    classname& operator=(const classname&) = default; \
    classname& operator=(classname&&)      = default;
#define NT_STRUCT_DEFAULTS(structure)                 \
    structure(const structure&)            = default; \
    structure(structure&&)                 = default; \
    structure& operator=(const structure&) = default; \
    structure& operator=(structure&&)      = default;
#define BIT(n) (1 << n)

// C++ primitive types
namespace Nt
{
    using int8    = char;
    using int16   = short;
    using int32   = int;
    using int64   = long long int;
    using uint8   = unsigned char;
    using byte    = unsigned char;
    using uint16  = unsigned short;
    using uint32  = unsigned int;
    using opsize  = unsigned int;
    using uint64  = unsigned long long int;
    using float32 = float;
    using float64 = double;
    using float80 = long double;
} // namespace Nt

// Type casting macros
#ifdef NT_CPP_VERSION
    #define NT_STATIC_CAST(type, value) static_cast<type>(value)
    #define NT_REINTERPRET_CAST(type, value) reinterpret_cast<type>(value)
    #define NT_CONST_CAST(type, value) const_cast<type>(value)
    #define NT_DYNAMIC_CAST(type, value) dynamic_cast<type>(value)
#else // (NOT) NT_CPP_VERSION
    #define NT_STATIC_CAST(type, value) (type)(value)
    #define NT_REINTERPRET_CAST(type, value) (type)(value)
    #define NT_CONST_CAST(type, value) (type)(value)
    #define NT_DYNAMIC_CAST(type, value) (type)(value)
#endif // NT_CPP_VERSION

// Discrete GPU reference
#ifdef NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_DISCRETE_GPU_REFERENCE                                             \
        extern "C" NT_EXPORT unsigned int NvOptimusEnablement                  = 1; \
        extern "C" NT_EXPORT unsigned int AmdPowerXpressRequestHighPerformance = 1;
#else // (NOT) NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_DISCRETE_GPU_REFERENCE
#endif // NT_PLATFORM_FAMILY_MICROSOFT

// Math constants
#define NT_PI     3.1415926535897932384626433832795
#define NT_TAU    6.283185307179586476925286766559
#define NT_EULER  2.7182818284590452353602874713527
#define NT_PHI    1.6180339887498948482045868343656
#define NT_SQRT_2 1.4142135623730950488016887242097

// Smart pointers
namespace Nt
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Weak = std::weak_ptr<T>;

    template<typename T, typename... Args>
    Weak<T> CreateWeak(Args&&... args)
    {
        return std::weak_ptr<T>(std::forward<Args>(args)...);
    }
} // namespace Nt

// External library headers
#ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif // _CRT_SECURE_NO_WARNINGS
#include <SDL3/SDL.h>
#include <bx/bx.h>
#include <bimg/bimg.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#ifdef NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_SHADERC_PATH "build/release/Nautilus/Vendor/BGFX/cmake/bgfx/shaderc.exe"
    #define NT_GEOMETRYC_PATH "build/release/Nautilus/Vendor/BGFX/cmake/bgfx/geometryc.exe"
#else // (NOT) NT_PLATFORM_FAMILY_MICROSOFT
    #define NT_SHADERC_PATH "build/debug/Nautilus/Vendor/BGFX/cmake/bgfx/shaderc"
    #define NT_GEOMETRYC_PATH "build/debug/Nautilus/Vendor/BGFX/cmake/bgfx/geometryc"
#endif // NT_PLATFORM_FAMILY_MICROSOFT

// Nautilus library headers
#include "Core/Log.h"

#ifdef NT_DEBUG
    #ifdef NT_PLATFORM_FAMILY_MICROSOFT
        #define NT_ASSERT(x, msg, ...) if (!(x)) { NT_CORE_FATAL(msg, ##__VA_ARGS__); __debugbreak(); }
    #else // (NOT) NT_PLATFORM_FAMILY_MICROSOFT
        #define NT_ASSERT(x, msg, ...) if (!(x)) { NT_CORE_FATAL(msg, ##__VA_ARGS__); abort(); }
    #endif // NT_PLATFORM_FAMILY_MICROSOFT
#else // (NOT) NT_DEBUG
    #define NT_ASSERT(x, ...)
#endif // NT_DEBUG

#endif // _PCH_H_
