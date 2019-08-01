#pragma once

#include "base.h"

namespace winsdk
{
    struct __declspec(novtable) IUnknown
    {
        static constexpr guid uuid = { 0x00000000, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

        virtual std::int32_t __stdcall QueryInterface(const guid& iid, void** obj) noexcept = 0;
        virtual std::uint32_t __stdcall AddRef() noexcept = 0;
        virtual std::uint32_t __stdcall Release() noexcept = 0;
    };

    template <typename T>
    struct uuid
    {
        // Assume static member; can be specialized to provide different lookup
        static constexpr guid value = T::uuid;
    };

    template <typename T>
    constexpr const guid& uuid_v = uuid<T>::value;
}
