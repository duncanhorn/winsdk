#pragma once

#include "../winsdk/unknown.h"
#include "error.h"

namespace win32
{
    template <typename T>
    struct com_ptr
    {
        T* value = nullptr;

        com_ptr() = default;
        explicit com_ptr(T* value) noexcept : value(value) { if (value) value->AddRef(); }
        com_ptr(const com_ptr& other) noexcept : com_ptr(other.value) {}
        com_ptr(com_ptr&& other) noexcept { swap(other); }

        template <typename U, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
        com_ptr(const com_ptr<U>& other) noexcept : com_ptr(other.value) {}

        template <typename U, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
        com_ptr(com_ptr<U>&& other) noexcept : value(other.value)
        {
            other.value = nullptr;
        }

        ~com_ptr() { if (value) value->Release(); }

        com_ptr& operator=(T* ptr) noexcept
        {
            if (ptr) ptr->AddRef();
            if (value) value->Release();
            value = ptr;
            return *this;
        }

        com_ptr& operator=(const com_ptr& other) noexcept
        {
            return *this = other.value;
        }

        com_ptr& operator=(com_ptr&& other) noexcept
        {
            swap(other);
            return *this;
        }

        template <typename U, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
        com_ptr& operator=(const com_ptr<U>& other) noexcept
        {
            return *this = other.value;
        }

        template <typename U, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
        com_ptr& operator=(com_ptr<U>&& other) noexcept
        {
            if (value) value->Release();
            value = std::exchange(other.value, nullptr);
            return *this;
        }

        explicit operator bool() const noexcept
        {
            return value != nullptr;
        }

        T* operator->() const noexcept
        {
            return value;
        }

        T** operator&() noexcept
        {
            reset();
            return &value;
        }

        void reset() noexcept
        {
            if (value)
            {
                value->Release();
                value = nullptr;
            }
        }

        void reset(std::nullptr_t) noexcept { reset(); }

        void reset(T* ptr) noexcept
        {
            if (ptr) ptr->AddRef();
            if (value) value->Release();
            value = ptr;
        }

        T* release() noexcept
        {
            return std::exchange(value, nullptr);
        }

        void attach(T* ptr) noexcept
        {
            value = ptr;
        }

        void swap(com_ptr& other) noexcept
        {
            std::swap(value, other.value);
        }

        template <typename U>
        void copy_to(U** ptr) const noexcept(std::is_convertible_v<T*, U*>)
        {
            if constexpr (std::is_convertible_v<T*, U*>)
            {
                value->AddRef();
                *ptr = value;
            }
            else
            {
                check_hresult(value->QueryInterface(winsdk::uuid_v<U>, reinterpret_cast<void**>(ptr)));
            }
        }

        template <typename U>
        com_ptr<U> as() const noexcept(std::is_convertible_v<T*, U*>)
        {
            com_ptr<U> result;
            copy_to(&result.value);
            return result;
        }
    };

    template <typename T, typename U>
    com_ptr<T> com_cast(U* ptr) noexcept(std::is_convertible_v<U*, T*>)
    {
        com_ptr<T> result;
        if constexpr (std::is_convertible_v<U*, T*>)
        {
            ptr->AddRef();
            result.value = ptr;
        }
        else
        {
            check_hresult(ptr->QueryInterface(winsdk::uuid_v<T>, reinterpret_cast<void**>(&result.value)));
        }

        return result;
    }
}
