#pragma once

#include <atomic>

#include "../winsdk/error.h"
#include "../winsdk/unknown.h"

namespace win32
{
    template <typename MostDerived, typename... BaseTypes>
    struct interface_list : MostDerived
    {
        template <typename IFace, typename... Others, typename T>
        static std::int32_t DoQueryInterface(T* ptr, const winsdk::guid& iid, void** obj) noexcept
        {
            if (iid == winsdk::uuid_v<IFace>)
            {
                *obj = static_cast<MostDerived*>(ptr);
                ptr->AddRef();
                return winsdk::hresult_ok;
            }

            if constexpr (sizeof...(Others) > 0)
            {
                return DoQueryInterface<Others...>(ptr, iid, obj);
            }

            return winsdk::hresult_error_nointerface;
        }

        template <typename T>
        static std::int32_t QueryInterface(T* ptr, const winsdk::guid& iid, void** obj) noexcept
        {
            return DoQueryInterface<MostDerived, BaseTypes...>(ptr, iid, obj);
        }
    };

    template <typename T> struct is_interface_list : std::false_type {};
    template <typename... Types> struct is_interface_list<interface_list<Types...>> : std::true_type {};
    template <typename T> constexpr bool is_interface_list_v = is_interface_list<T>::value;

    template <typename Impl, typename... Interfaces>
    struct IUnknown : Interfaces...
    {
        std::atomic_uint32_t reference_count{ 1 };

        template <typename IFace, typename... Others>
        std::int32_t DoQueryInterface(const winsdk::guid& iid, void** obj) noexcept
        {
            if constexpr (is_interface_list_v<IFace>)
            {
                if (IFace::QueryInterface(this, iid, obj) == winsdk::hresult_ok)
                {
                    return winsdk::hresult_ok;
                }
            }
            else
            {
                if (iid == winsdk::uuid_v<IFace>)
                {
                    *obj = static_cast<IFace*>(this);
                    AddRef();
                    return winsdk::hresult_ok;
                }
            }

            if constexpr (sizeof...(Others) > 0)
            {
                return DoQueryInterface<Others...>(iid, obj);
            }

            return winsdk::hresult_error_nointerface;
        }

        virtual std::int32_t QueryInterface(const winsdk::guid& iid, void** obj) noexcept override
        {
            if (iid == winsdk::uuid_v<winsdk::IUnknown>)
            {
                *obj = this;
                AddRef();
                return winsdk::hresult_ok;
            }

            return DoQueryInterface<Interfaces...>(iid, obj);
        }

        virtual std::uint32_t AddRef() noexcept override
        {
            return ++reference_count;
        }

        virtual std::uint32_t Release() noexcept override
        {
            auto result = --reference_count;
            if (!result)
            {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-non-abstract-non-virtual-dtor"
#endif
                delete static_cast<Impl*>(this);
#ifdef __clang__
#pragma clang diagnostic pop
#endif
            }

            return result;
        }
    };
}
