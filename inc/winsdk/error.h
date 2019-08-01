#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Constants
    constexpr std::int32_t facility_rpc = 1;
    constexpr std::int32_t facility_win32 = 7;

    constexpr std::uint32_t error_success = 0;
    constexpr std::uint32_t error_file_not_found = 2;
    constexpr std::uint32_t error_path_not_found = 3;
    constexpr std::uint32_t error_access_denied = 5;
    constexpr std::uint32_t error_invalid_handle = 6;
    constexpr std::uint32_t error_not_enough_memory = 8;
    constexpr std::uint32_t error_outofmemory = 14;
    constexpr std::uint32_t error_no_more_files = 18;
    constexpr std::uint32_t error_bad_length = 24;
    constexpr std::uint32_t error_file_exists = 80;
    constexpr std::uint32_t error_invalid_parameter = 87;
    constexpr std::uint32_t error_broken_pipe = 109;
    constexpr std::uint32_t error_buffer_overflow = 111;
    constexpr std::uint32_t error_insufficient_buffer = 122;
    constexpr std::uint32_t error_mod_not_found = 126;
    constexpr std::uint32_t error_proc_not_found = 127;
    constexpr std::uint32_t error_already_exists = 183;
    constexpr std::uint32_t error_bad_pipe = 230;
    constexpr std::uint32_t error_pipe_busy = 231;
    constexpr std::uint32_t error_no_data = 232;
    constexpr std::uint32_t error_pipe_not_connected = 233;
    constexpr std::uint32_t error_more_data = 234;
    constexpr std::uint32_t error_invalid_token = 315;
    constexpr std::uint32_t error_time_sensitive_thread = 422;
    constexpr std::uint32_t error_no_task_queue = 427;
    constexpr std::uint32_t error_not_found = 1168;
    constexpr std::uint32_t error_invalid_state = 5023;

    constexpr std::int32_t hresult_ok = 0;
    constexpr std::int32_t hresult_error_not_set = 0x80070490; // hresult_from_win32(error_not_found)
    constexpr std::int32_t hresult_error_not_valid_state = 0x8007139F; // hresult_from_win32(error_invalid_state)
    constexpr std::int32_t hresult_error_not_sufficient_buffer = 0x80070122; // hresult_from_win32(error_insufficient_buffer)
    constexpr std::int32_t hresult_error_time_sensitive_thread = 0x800701A6; // hresult_from_win32(error_time_sensitive_thread)
    constexpr std::int32_t hresult_error_no_task_queue = 0x800701AB; // hresult_from_win32(error_no_task_queue)
    constexpr std::int32_t hresult_error_unexpected = 0x8000FFFF;
    constexpr std::int32_t hresult_error_notimpl = 0x80004001;
    constexpr std::int32_t hresult_error_outofmemory = 0x8007000E;
    constexpr std::int32_t hresult_error_invalidarg = 0x80070057;
    constexpr std::int32_t hresult_error_nointerface = 0x80004002;
    constexpr std::int32_t hresult_error_pointer = 0x80004003;
    constexpr std::int32_t hresult_error_handle = 0x80070006;
    constexpr std::int32_t hresult_error_abort = 0x80004004;
    constexpr std::int32_t hresult_error_fail = 0x80004005;
    constexpr std::int32_t hresult_error_accessdenied = 0x80070005;
    constexpr std::int32_t hresult_error_pending = 0x8000000A;
    constexpr std::int32_t hresult_error_bounds = 0x8000000B;
    constexpr std::int32_t hresult_error_changed_state = 0x8000000C;
    constexpr std::int32_t hresult_error_illegal_state_change = 0x8000000D;
    constexpr std::int32_t hresult_error_illegal_method_call = 0x8000000E;
}
}

namespace winsdk
{
    inline constexpr std::int32_t hresult_facility(std::int32_t hr) noexcept
    {
        return (hr >> 16) & 0x1FFF;
    }

    inline constexpr std::int32_t hresult_code(std::int32_t hr) noexcept
    {
        return hr & 0xFFFF;
    }

    inline constexpr std::int32_t make_hresult(std::int32_t facility, std::int32_t code) noexcept
    {
        return (facility << 16) | static_cast<std::int32_t>(code) | 0x80000000;
    }

    inline constexpr std::int32_t hresult_from_nt(std::uint32_t err) noexcept
    {
        return static_cast<std::int32_t>(err | 0x10000000);
    }

    inline constexpr std::int32_t hresult_from_win32(std::uint32_t err) noexcept
    {
        return make_hresult(facility_win32, err & 0x0000FFFF);
    }

    inline constexpr bool succeeded(std::int32_t hr) noexcept
    {
        return hr >= 0;
    }

    inline constexpr bool failed(std::int32_t hr) noexcept
    {
        return hr < 0;
    }
}
