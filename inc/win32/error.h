#pragma once

#include <system_error>

#include "../winsdk/base.h"

namespace win32
{
    [[noreturn]]
    inline void throw_error(std::uint32_t err, const char* msg = nullptr)
    {
        if (msg) throw std::system_error(static_cast<int>(err), std::system_category(), msg);
        throw std::system_error(static_cast<int>(err), std::system_category());
    }

    [[noreturn]]
    inline void throw_last_error(const char* msg = nullptr)
    {
        throw_error(winsdk::GetLastError(), msg);
    }

    inline void throw_last_error_if(bool cond, const char* msg = nullptr)
    {
        if (cond) throw_last_error(msg);
    }

    inline void check_error(std::uint32_t err)
    {
        if (err) throw_error(err);
    }
}
