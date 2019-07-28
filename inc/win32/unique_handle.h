#pragma once

#include "../winsdk/base.h"
#include "unique_resource.h"

namespace win32
{
    namespace details
    {
        struct handle_traits_base
        {
            using value_type = winsdk::handle_t;

            void destroy(value_type value) const noexcept
            {
                winsdk::CloseHandle(value);
            }
        };
    }

    struct null_handle_traits : details::handle_traits_base
    {
        static constexpr value_type default_value = nullptr;

        bool valid(value_type value) const noexcept
        {
            return value != nullptr;
        }
    };

    struct invalid_handle_traits : details::handle_traits_base
    {
        static inline const value_type default_value = winsdk::invalid_handle_value;

        bool valid(value_type value) const noexcept
        {
            return value != winsdk::invalid_handle_value;
        }
    };

    struct null_invalid_handle_traits : details::handle_traits_base
    {
        static constexpr value_type default_value = nullptr;

        bool valid(value_type value) const noexcept
        {
            return (value != nullptr) && (value != winsdk::invalid_handle_value);
        }
    };

    using unique_handle = unique_resource<null_invalid_handle_traits>;
    using unique_null_handle = unique_resource<null_handle_traits>;
    using unique_invalid_handle = unique_resource<invalid_handle_traits>;
}
