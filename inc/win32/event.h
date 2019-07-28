#pragma once

#include <cassert>
#include <chrono>

#include "../winsdk/synch.h"
#include "error.h"
#include "unique_handle.h"

namespace win32
{
    struct event
    {
        unique_handle value;

        event(
            bool manualReset = false,
            bool initialState = false,
            const char* name = nullptr,
            winsdk::security_attributes* eventAttributes = nullptr)
        {
            value.reset(winsdk::CreateEventA(eventAttributes, manualReset, initialState, name));
            throw_last_error_if(!value);
        }

        winsdk::handle_t get() const noexcept
        {
            return value.get();
        }

        winsdk::handle_t detach() noexcept
        {
            return value.detach();
        }

        void set()
        {
            throw_last_error_if(!winsdk::SetEvent(value.get()));
        }

        void reset()
        {
            throw_last_error_if(!winsdk::ResetEvent(value.get()));
        }

        bool wait(std::chrono::milliseconds ms)
        {
            auto result = winsdk::WaitForSingleObject(value.get(), static_cast<std::uint32_t>(ms.count()));
            switch (result)
            {
            case winsdk::wait_object_0: return true;
            case winsdk::wait_timeout: return false;
            case winsdk::wait_failed: throw_last_error();
            default: throw std::runtime_error("Unknown wait failure");
            }
        }

        void wait()
        {
            [[maybe_unused]] auto result = wait(std::chrono::milliseconds(winsdk::infinite));
            assert(result);
        }
    };
}
