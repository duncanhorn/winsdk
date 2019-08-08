#pragma once

#include <cassert>
#include <winsdk/sockets.h>

#include "unique_resource.h"

namespace win32
{
    struct unique_socket_traits
    {
        using value_type = winsdk::socket_t;
        static constexpr value_type default_value = winsdk::invalid_socket;

        void destroy(value_type socket) const noexcept
        {
            [[maybe_unused]] auto result = winsdk::closesocket(socket);
            assert(result != winsdk::socket_error);
        }

        constexpr bool valid(value_type value) const noexcept
        {
            return value != default_value;
        }
    };

    using unique_socket = unique_resource<unique_socket_traits>;
}
