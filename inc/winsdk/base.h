// Base types/typedefs and functions common across most of the SDK
#pragma once

#include <cstddef>
#include <cstdint>

extern "C"
{
namespace winsdk
{
    // Type definitions
    using bool_t = std::int32_t;
    using handle_t = void*;

    // Constants
    inline const handle_t invalid_handle_value = reinterpret_cast<handle_t>(static_cast<std::intptr_t>(-1));

    // Structures
    struct security_attributes
    {
        std::uint32_t length;
        void* security_descriptor;
        bool_t inherit_handle;
    };

    struct overlapped
    {
        std::uintptr_t internal;
        std::uintptr_t internal_high;
        union
        {
            struct
            {
                std::uint32_t offset;
                std::uint32_t offset_high;
            } position;
            void* pointer;
        } data;

        handle_t event;
    };

    // Functions
    __declspec(dllimport)
    bool_t __stdcall CloseHandle(handle_t handle);

    __declspec(dllimport)
    std::uint32_t __stdcall GetLastError();
}
}
