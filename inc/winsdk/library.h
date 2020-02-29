#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Type definitions
    using hmodule_t = handle_t;

    // Functions
    __declspec(dllimport)
    hmodule_t LoadLibraryA(const char* fileName);

    __declspec(dllimport)
    hmodule_t LoadLibraryW(const wchar_t* fileName);

    __declspec(dllimport)
    bool_t FreeLibrary(hmodule_t module);

    __declspec(dllimport)
    winsdk::farproc GetProcAddress(hmodule_t module, const char* procName);

    __declspec(dllimport)
    std::uint32_t GetModuleFileNameA(hmodule_t module, char* fileName, std::uint32_t size);

    __declspec(dllimport)
    std::uint32_t GetModuleFileNameW(hmodule_t module, wchar_t* fileName, std::uint32_t size);
}
}
