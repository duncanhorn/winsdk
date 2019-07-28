#pragma once

#include <utility>

namespace win32
{
    namespace details
    {
        template <typename Traits>
        struct traits_pair : Traits
        {
            using value_type = typename Traits::value_type;
            value_type data = Traits::default_value;

            traits_pair() = default;
            traits_pair(value_type value) noexcept : data(std::move(value)) {}
            traits_pair(Traits traits) noexcept : Traits(std::move(traits)) {}
            traits_pair(value_type value, Traits traits) : Traits(std::move(traits)), data(std::move(value)) {}

            constexpr Traits& traits() noexcept { return *this; }
            constexpr const Traits& traits() const noexcept { return *this; }
            constexpr value_type& value() noexcept { return data; };
            constexpr const value_type& value() const noexcept { return data; };
        };
    }

    template <typename Traits>
    struct unique_resource
    {
        using value_type = typename Traits::value_type;

        unique_resource() = default;
        explicit unique_resource(value_type value) noexcept : data(std::move(value)) {}
        unique_resource(value_type value, Traits traits) noexcept : data(std::move(value), std::move(traits)) {}
        unique_resource(const unique_resource&) = delete;
        unique_resource(unique_resource&& other) noexcept { swap(other); }

        ~unique_resource() { if (*this) data.traits().destroy(data.value()); }

        unique_resource& operator=(const unique_resource&) = delete;
        unique_resource& operator=(unique_resource&& other) noexcept { swap(other); }

        explicit operator bool() const noexcept { return data.traits().valid(data.value()); }

        const value_type& get() const noexcept { return data.value(); }
        value_type& get() noexcept { return data.value(); }

        void swap(unique_resource& other) noexcept
        {
            std::swap(data, other.data);
        }

        void reset() noexcept
        {
            if (*this)
            {
                data.traits().destroy(data.value());
                data.value() = Traits::default_value;
            }
        }

        void reset(std::nullptr_t) noexcept
        {
            reset();
        }

        void reset(const value_type& value) noexcept
        {
            if (*this) data.traits().destroy(data.value());
            data.value() = value;
        }

        value_type detach() noexcept
        {
            auto result = std::move(data.value());
            data.value() = Traits::default_value;
            return result;
        }

        details::traits_pair<Traits> data;
    };
}
