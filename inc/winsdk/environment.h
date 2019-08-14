#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Constants
    constexpr std::uint32_t error_envvar_not_found = 203;

    // Functions
    __declspec(dllimport)
    char* __stdcall GetEnvironmentStrings();

    __declspec(dllimport)
    wchar_t* __stdcall GetEnvironmentStringsW();

    __declspec(dllimport)
    bool_t __stdcall FreeEnvironmentStringsA(char* env);

    __declspec(dllimport)
    bool_t __stdcall FreeEnvironmentStringsW(wchar_t* env);

    __declspec(dllimport)
    bool_t __stdcall SetEnvironmentStringsW(wchar_t* newEnv);

    __declspec(dllimport)
    std::uint32_t __stdcall GetEnvironmentVariableA(const char* name, char* buffer, std::uint32_t size);

    __declspec(dllimport)
    std::uint32_t __stdcall GetEnvironmentVariableW(const wchar_t* name, wchar_t* buffer, std::uint32_t size);

    __declspec(dllimport)
    bool_t __stdcall SetEnvironmentVariableA(const char* name, const char* value);

    __declspec(dllimport)
    bool_t __stdcall SetEnvironmentVariableW(const wchar_t* name, const wchar_t* value);

    __declspec(dllimport)
    std::uint32_t __stdcall ExpandEnvironmentStringsA(const char* src, char* dest, std::uint32_t size);

    __declspec(dllimport)
    std::uint32_t __stdcall ExpandEnvironmentStringsW(const wchar_t* src, wchar_t* dest, std::uint32_t size);
}
}
