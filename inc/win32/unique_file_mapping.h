#pragma once

#include <cassert>

#include "../winsdk/file.h"
#include "unique_resource.h"

namespace win32
{
    struct file_mapping_traits
    {
        using value_type = void*;
        static constexpr value_type default_value = nullptr;

        void destroy(value_type value) const noexcept
        {
            [[maybe_unused]] auto result = winsdk::UnmapViewOfFile(value);
            assert(result);
        }

        constexpr bool valid(value_type value) const noexcept
        {
            return value != nullptr;
        }
    };

    using unique_file_mapping = unique_resource<file_mapping_traits>;
}
