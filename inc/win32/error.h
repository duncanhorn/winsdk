#pragma once

#include <cassert>
#include <system_error>

#include "../winsdk/error.h"

namespace win32
{
    [[noreturn]]
    inline void throw_error(std::uint32_t err, const char* msg = nullptr)
    {
        assert(err != 0);
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

    const std::error_category& hresult_category() noexcept;

    namespace details
    {
        struct hresult_category : std::error_category
        {
            virtual const char* name() const noexcept override
            {
                return "hresult";
            }

            virtual std::error_condition default_error_condition(int err) const noexcept override
            {
                if (winsdk::hresult_facility(err) == winsdk::facility_win32)
                {
                    return std::system_category().default_error_condition(winsdk::hresult_code(err));
                }

                // TODO: Other mappings?
                return std::error_condition(err, win32::hresult_category());
            }

            virtual std::string message(int err) const override
            {
                // NOTE: 'system_category' uses the same 'FormatMessage' function that we would, so just re-use
                return std::system_category().message(err);
            }
        };
    }

    const std::error_category& hresult_category() noexcept
    {
        static const details::hresult_category result;
        return result;
    }

    [[noreturn]]
    inline void throw_hresult(std::int32_t hr, const char* msg = nullptr)
    {
        assert(hr < 0);
        if (msg) throw std::system_error(hr, hresult_category(), msg);
        throw std::system_error(hr, hresult_category());
    }

    inline void check_hresult(std::int32_t hr, const char* msg = nullptr)
    {
        if (hr < 0) throw_hresult(hr, msg);
    }
}
