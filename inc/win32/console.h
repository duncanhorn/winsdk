#pragma once

#include "../winsdk/console.h"
#include "error.h"
#include "unique_handle.h"

namespace win32
{
    constexpr std::uint16_t foreground_mask = 0x000F;
    constexpr std::uint16_t background_mask = 0x00F0;

    constexpr std::uint16_t foreground_black = 0;
    constexpr std::uint16_t foreground_dark_red = winsdk::foreground_red;
    constexpr std::uint16_t foreground_red = foreground_dark_red | winsdk::foreground_intensity;
    constexpr std::uint16_t foreground_dark_green = winsdk::foreground_green;
    constexpr std::uint16_t foreground_green = foreground_dark_green | winsdk::foreground_intensity;
    constexpr std::uint16_t foreground_dark_blue = winsdk::foreground_blue;
    constexpr std::uint16_t foreground_blue = foreground_dark_blue | winsdk::foreground_intensity;
    constexpr std::uint16_t foreground_dark_magenta = winsdk::foreground_red | winsdk::foreground_blue;
    constexpr std::uint16_t foreground_magenta = foreground_dark_magenta | winsdk::foreground_intensity;
    constexpr std::uint16_t foreground_dark_cyan = winsdk::foreground_green | winsdk::foreground_blue;
    constexpr std::uint16_t foreground_cyan = foreground_dark_cyan | winsdk::foreground_intensity;
    constexpr std::uint16_t foreground_dark_yellow = winsdk::foreground_red | winsdk::foreground_green;
    constexpr std::uint16_t foreground_yellow = foreground_dark_yellow | winsdk::foreground_intensity;
    constexpr std::uint16_t foreground_gray = winsdk::foreground_red | winsdk::foreground_green | winsdk::foreground_blue;
    constexpr std::uint16_t foreground_white = foreground_gray | winsdk::foreground_intensity;

    constexpr std::uint16_t background_black = 0;
    constexpr std::uint16_t background_dark_red = winsdk::background_red;
    constexpr std::uint16_t background_red = background_dark_red | winsdk::background_intensity;
    constexpr std::uint16_t background_dark_green = winsdk::background_green;
    constexpr std::uint16_t background_green = background_dark_green | winsdk::background_intensity;
    constexpr std::uint16_t background_dark_blue = winsdk::background_blue;
    constexpr std::uint16_t background_blue = background_dark_blue | winsdk::background_intensity;
    constexpr std::uint16_t background_dark_magenta = winsdk::background_red | winsdk::background_blue;
    constexpr std::uint16_t background_magenta = background_dark_magenta | winsdk::background_intensity;
    constexpr std::uint16_t background_dark_cyan = winsdk::background_green | winsdk::background_blue;
    constexpr std::uint16_t background_cyan = background_dark_cyan | winsdk::background_intensity;
    constexpr std::uint16_t background_dark_yellow = winsdk::background_red | winsdk::background_green;
    constexpr std::uint16_t background_yellow = background_dark_yellow | winsdk::background_intensity;
    constexpr std::uint16_t background_gray = winsdk::background_red | winsdk::background_green | winsdk::background_blue;
    constexpr std::uint16_t background_white = background_gray | winsdk::background_intensity;

    inline std::uint16_t set_console_attributes(winsdk::handle_t console, std::uint16_t attr, std::uint16_t mask = 0xFFFF)
    {
            winsdk::console_screen_buffer_info info;
            throw_last_error_if(!winsdk::GetConsoleScreenBufferInfo(console, &info));

            auto newAttr = (info.attributes & ~mask) | (attr & mask);
            throw_last_error_if(!winsdk::SetConsoleTextAttribute(console, newAttr));

            return info.attributes;
    }

    struct console_attribute_guard
    {
        winsdk::handle_t console_handle = nullptr;
        std::uint16_t restore_attributes;

        console_attribute_guard(winsdk::handle_t console, std::uint16_t attr, std::uint16_t mask = 0xFFFF)
        {
            restore_attributes = set_console_attributes(console, attr, mask);
            console_handle = console;
        }

        console_attribute_guard(const console_attribute_guard&) = delete;
        console_attribute_guard(console_attribute_guard&& other) noexcept :
            console_handle(std::exchange(other.console_handle, nullptr)),
            restore_attributes(other.restore_attributes)
        {
        }

        ~console_attribute_guard()
        {
            if (null_invalid_handle_traits().valid(console_handle))
            {
                [[maybe_unused]]
                auto result = winsdk::SetConsoleTextAttribute(console_handle, restore_attributes);
                assert(result);
            }
        }

        console_attribute_guard& operator=(const console_attribute_guard&) = delete;
        console_attribute_guard& operator=(console_attribute_guard&& other) noexcept
        {
            std::swap(console_handle, other.console_handle);
            std::swap(restore_attributes, other.restore_attributes);
            return *this;
        }

        void release() noexcept
        {
            console_handle = nullptr;
        }

        void reset()
        {
            if (null_invalid_handle_traits().valid(console_handle))
            {
                auto handle = std::exchange(console_handle, nullptr);
                throw_last_error_if(!winsdk::SetConsoleTextAttribute(handle, restore_attributes));
            }
        }
    };
}
