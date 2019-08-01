// Base types/typedefs and functions common across most of the SDK
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

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

    struct guid
    {
        std::uint32_t data1;
        std::uint16_t data2;
        std::uint16_t data3;
        std::uint8_t data4[8];
    };

    // Functions
    __declspec(dllimport)
    bool_t __stdcall CloseHandle(handle_t handle);

    __declspec(dllimport)
    std::uint32_t __stdcall GetLastError();
}
}

namespace winsdk
{
    inline constexpr std::uint16_t low_word(std::uint32_t value) noexcept
    {
        return static_cast<std::uint16_t>(value & 0x0000FFFF);
    }

    inline constexpr std::uint16_t high_word(std::uint32_t value) noexcept
    {
        return static_cast<std::uint16_t>((value >> 16) & 0x0000FFFF);
    }

    inline constexpr std::uint32_t low_dword(std::uint64_t value) noexcept
    {
        return static_cast<std::uint32_t>(value & 0x00000000FFFFFFFFull);
    }

    inline constexpr std::uint32_t high_dword(std::uint64_t value) noexcept
    {
        return static_cast<std::uint32_t>((value >> 32) & 0x00000000FFFFFFFFull);
    }

    inline bool operator==(const guid& lhs, const guid& rhs) noexcept
    {
        static_assert(sizeof(guid) == 16); // Otherwise memcmp won't work
        return std::memcmp(&lhs, &rhs, sizeof(guid)) == 0;
    }

    inline bool operator!=(const guid& lhs, const guid& rhs) noexcept
    {
        static_assert(sizeof(guid) == 16); // Otherwise memcmp won't work
        return std::memcmp(&lhs, &rhs, sizeof(guid)) != 0;
    }
}
