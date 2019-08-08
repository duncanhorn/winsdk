#pragma once

#include "../winsdk/sockets.h"
#include "error.h"

namespace win32
{
    [[noreturn]]
    inline void wsa_throw_error(std::int32_t err, const char* msg = nullptr)
    {
        assert(err != winsdk::socket_error);
        if (msg) throw std::system_error(err, std::generic_category(), msg);
        throw std::system_error(err, std::generic_category());
    }

    [[noreturn]]
    inline void wsa_throw_last_error(const char* msg = nullptr)
    {
        wsa_throw_error(winsdk::WSAGetLastError(), msg);
    }

    inline void wsa_throw_last_error_if(bool cond, const char* msg = nullptr)
    {
        if (cond) wsa_throw_last_error(msg);
    }

    inline void wsa_check_result(std::int32_t err, const char* msg = nullptr)
    {
        wsa_throw_last_error_if(err == winsdk::socket_error, msg);
    }

    inline winsdk::wsa_data wsa_initialize()
    {
        winsdk::wsa_data data;
        wsa_check_result(winsdk::WSAStartup(0x0202, &data));
        return data;
    }
}
