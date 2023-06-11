#pragma once

#ifdef sn_unix_base
#define sn_api __attribute__((visibility("default")))
#elif sn_winnt
#define sn_api __declspec(dllexport)
#else
#define sn_api
#endif

#ifdef sn_dyn_lib
#ifdef sn_unix_base
#define sn_lib_export __attribute__((visibility("default")))
#define sn_lib_import
#elif sn_winnt
#define sn_lib_export __declspec(dllexport)
#define sn_lib_import __declspec(dllimport)
#endif
#else
#ifdef sn_unix_base
#define sn_lib_export
#define sn_lib_import
#elif sn_winnt
#define sn_lib_export __declspec(dllexport)
#define sn_lib_import __declspec(import)
#endif
#endif

#define CHECK_EMPTY(POINTER, MSG)                           \
    if (POINTER != nullptr)                                 \
    {                                                       \
        CError("A Pointer Is Not NULL, Message: {0}", MSG); \
        throw std::system_error(std::error_code(), MSG);    \
    }
