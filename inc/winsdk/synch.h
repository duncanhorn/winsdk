#pragma once

#include "base.h"

extern "C"
{
namespace win32
{
    // Functions
    __declspec(dllimport)
    std::uint32_t __stdcall WaitForSingleObject(handle_t handle, std::uint32_t milliseconds);

    __declspec(dllimport)
    std::uint32_t __stdcall WaitForMultipleObjects(
        std::uint32_t count,
        const handle_t* handles,
        bool_t waitAll,
        std::uint32_t milliseconds);

    __declspec(dllimport)
    handle_t __stdcall CreateEventA(
        security_attributes* eventAttributes,
        bool_t manualReset,
        bool_t initialState,
        const char* name);

    __declspec(dllimport)
    handle_t __stdcall CreateEventW(
        security_attributes* eventAttributes,
        bool_t manualReset,
        bool_t initialState,
        const wchar_t* name);

    __declspec(dllimport)
    bool_t __stdcall SetEvent(handle_t event);

    __declspec(dllimport)
    bool_t __stdcall ResetEvent(handle_t event);

    __declspec(dllimport)
    void __stdcall Sleep(std::uint32_t milliseconds);
}
}
