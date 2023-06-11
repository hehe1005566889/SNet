#pragma once

#include "SBase.h"

#include <iostream>
#include <string>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wreorder-ctor"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wignored-pragma-optimize"
#pragma clang diagnostic ignored "-Wmissing-braces"
#pragma clang diagnostic ignored "-Wchar-subscripts"
#endif

namespace snet
{

    template <typename T>
    using ref = std::shared_ptr<T>;
    template <typename T>
    using unique = std::unique_ptr<T>;

    template <typename T, typename... Args>
    constexpr ref<T> create_ref(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    template <typename T, typename... Args>
    constexpr unique<T> create_unique(Args &&...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    using i8 = char;
    using u8 = unsigned char;
    using i16 = short;
    using u16 = unsigned short;
    using i32 = int;
    using u32 = unsigned int;
#ifdef sn_winnt
    using i64 = long long;
    using u64 = unsigned long long;
#else
    using i64 = long;
    using u64 = unsigned long;
#endif
    using uintptr = u64;

    typedef unsigned char snyte;

#ifdef sn_winnt
#define sn_debug_break() __debugbreak()
#define sn_inline __forceinline
#define sn_restrict __restrict
#else
#define sn_debug_break() raise(SIGTRAP)
#define sn_inline __attribute__((always_inline)) inline
#define sn_restrict __restrict__
#endif

#define ASSERT(x)                                  \
    do                                             \
    {                                              \
        const volatile bool _assert_result = !(x); \
        if (_assert_result)                        \
            sn_debug_break();                      \
    } while (false)

#ifdef sn_debug

#define sn_ASSERT(x)          \
    {                         \
        if (!(x))             \
        {                     \
            CError("Failed"); \
            throw "awa";      \
        }                     \
    }

#define sn_CORE_ASSERT(x, ...)                \
    {                                         \
        if (!(x))                             \
        {                                     \
            CError("Faild {0}", __VA_ARGS__); \
            throw __VA_ARGS__;                \
        }                                     \
    }

#else
#define sn_ASSERT(...)
#define sn_CORE_ASSERT(...)
#endif
}