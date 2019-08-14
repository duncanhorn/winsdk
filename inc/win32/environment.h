#pragma once

#include <string>
#include <string_view>

#include "../winsdk/environment.h"
#include "error.h"

namespace win32
{
    template <typename CharT>
    bool try_get_env_variable(const CharT* name, std::basic_string<CharT>& result)
    {
        std::uint32_t size;
        if constexpr (std::is_same_v<CharT, char>) size = winsdk::GetEnvironmentVariableA(name, nullptr, 0);
        else size = winsdk::GetEnvironmentVariableW(name, nullptr, 0);

        if (!size)
        {
            auto err = winsdk::GetLastError();
            if (err == winsdk::error_envvar_not_found)
            {
                return false;
            }
            throw_error(err);
        }

        while (true)
        {
            result.resize(size);
            if constexpr (std::is_same_v<CharT, char>) size = winsdk::GetEnvironmentVariableA(name, result.data(), size);
            else size = winsdk::GetEnvironmentVariableW(name, result.data(), size);

            throw_last_error_if(!size);
            if (size <= result.size())
            {
                result.resize(size);
                return true;
            }
        }
    }

    template <typename CharT>
    std::basic_string<CharT> get_env_variable(const CharT* name)
    {
        std::basic_string<CharT> result;
        throw_last_error_if(!try_get_env_variable(name, result));
        return result;
    }

    template <typename CharT>
    void set_env_variable(const CharT* name, const CharT* value)
    {
        if constexpr (std::is_same_v<CharT, char>) throw_last_error_if(!winsdk::SetEnvironmentVariableA(name, value));
        else throw_last_error_if(!winsdk::SetEnvironmentVariableW(name, value));
    }

    namespace details
    {
        template <typename T>
        struct pointer_proxy
        {
            T value;
            constexpr T* operator->() noexcept { return std::addressof(value); }
        };
    }

    template <typename CharT>
    struct basic_environment_strings_iterator
    {
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<std::basic_string_view<CharT>, std::basic_string_view<CharT>>;
        using pointer = details::pointer_proxy<value_type>;
        using reference = const value_type&;
        using iterator_category = std::forward_iterator_tag;

        value_type value;

        basic_environment_strings_iterator() = default;

        basic_environment_strings_iterator(const CharT* value) { set(value); }

        bool operator==(const basic_environment_strings_iterator& other) const noexcept { return value.first.data() == other.value.first.data(); }
        bool operator!=(const basic_environment_strings_iterator& other) const noexcept { return value.first.data() != other.value.first.data(); }

        reference operator*() const noexcept { return value; }
        pointer operator->() const noexcept { return pointer{ value }; }

        basic_environment_strings_iterator& operator++() { advance(); return *this; }
        basic_environment_strings_iterator operator++(int)
        {
            auto copy = *this;
            ++*this;
            return copy;
        }

        void set(const CharT* ptr)
        {
            if (!ptr || !*ptr)
            {
                value = {};
                return;
            }

            std::basic_string_view<CharT> str = ptr;
            auto pos = str.find('=', 1);
            value.first = str.substr(0, pos);
            value.second = str.substr(pos + 1);
        }

        void advance()
        {
            set(value.second.data() + value.second.size() + 1);
        }
    };

    template <typename CharT>
    struct basic_environment_strings
    {
        CharT* value;

        using iterator = basic_environment_strings_iterator<CharT>;
        using const_iterator = basic_environment_strings_iterator<CharT>;

        basic_environment_strings()
        {
            if constexpr (std::is_same_v<CharT, char>) value = winsdk::GetEnvironmentStrings();
            else value = winsdk::GetEnvironmentStringsW();
            throw_last_error_if(!value);
        }

        basic_environment_strings(const basic_environment_strings&) = delete;

        basic_environment_strings(basic_environment_strings&& other) noexcept : value(other.value)
        {
            other.value = nullptr;
        }

        ~basic_environment_strings()
        {
            if (value)
            {
                [[maybe_unused]] winsdk::bool_t success;
                if constexpr (std::is_same_v<CharT, char>) success = winsdk::FreeEnvironmentStringsA(value);
                else success = winsdk::FreeEnvironmentStringsW(value);
                assert(success);
            }
        }

        basic_environment_strings& operator=(const basic_environment_strings&) = delete;

        basic_environment_strings& operator=(basic_environment_strings&& other) noexcept
        {
            std::swap(value, other.value);
            return *this;
        }

        const_iterator begin() const { return const_iterator{ value }; }
        const_iterator cbegin() const { return begin(); }
        const_iterator end() const { return const_iterator(); }
        const_iterator cend() const { return end(); }
    };

    using environment_strings = basic_environment_strings<char>;
    using wenvironment_strings = basic_environment_strings<wchar_t>;
}
