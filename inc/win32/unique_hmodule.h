#pragma once

#include <cassert>

#include "../winsdk/library.h"
#include "unique_resource.h"

namespace win32
{
    struct hmodule_traits
    {
        using value_type = winsdk::hmodule_t;
        static constexpr value_type default_value = nullptr;

        void destroy(value_type value) const noexcept
        {
            [[maybe_unused]] auto result = winsdk::FreeLibrary(value);
            assert(result);
        }

        constexpr bool valid(value_type value) const noexcept
        {
            return value != nullptr;
        }
    };

    using unique_file_mapping = unique_resource<hmodule_traits>;
}
