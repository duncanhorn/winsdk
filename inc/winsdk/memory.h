#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Constants
    constexpr std::uint32_t mem_commit = 0x00001000;
    constexpr std::uint32_t mem_reserve = 0x00002000;
    constexpr std::uint32_t mem_replace_placeholder = 0x00004000;
    constexpr std::uint32_t mem_reserve_placeholder = 0x00040000;
    constexpr std::uint32_t mem_reset = 0x00080000;
    constexpr std::uint32_t mem_top_down = 0x00100000;
    constexpr std::uint32_t mem_write_watch = 0x00200000;
    constexpr std::uint32_t mem_physical = 0x00400000;
    constexpr std::uint32_t mem_rotate = 0x00800000;
    constexpr std::uint32_t mem_different_image_base_ok = 0x00800000;
    constexpr std::uint32_t mem_reset_undo = 0x01000000;
    constexpr std::uint32_t mem_large_pages = 0x20000000;
    constexpr std::uint32_t mem_4mb_pages = 0x80000000;
    constexpr std::uint32_t mem_64k_pages = mem_large_pages | mem_physical;
    constexpr std::uint32_t mem_unmap_with_transient_boost = 0x00000001;
    constexpr std::uint32_t mem_coalesce_placeholders = 0x00000001;
    constexpr std::uint32_t mem_preserve_placeholder = 0x00000002;
    constexpr std::uint32_t mem_decommit = 0x00004000;
    constexpr std::uint32_t mem_release = 0x00008000;
    constexpr std::uint32_t mem_free = 0x00010000;

    constexpr std::uint32_t page_noaccess = 0x01;
    constexpr std::uint32_t page_readonly = 0x02;
    constexpr std::uint32_t page_readwrite = 0x04;
    constexpr std::uint32_t page_writecopy = 0x08;
    constexpr std::uint32_t page_execute = 0x10;
    constexpr std::uint32_t page_execute_read = 0x20;
    constexpr std::uint32_t page_execute_readwrite = 0x40;
    constexpr std::uint32_t page_execute_writecopy = 0x80;
    constexpr std::uint32_t page_guard = 0x100;
    constexpr std::uint32_t page_nocache = 0x200;
    constexpr std::uint32_t page_writecombine = 0x400;
    constexpr std::uint32_t page_graphics_noaccess = 0x0800;
    constexpr std::uint32_t page_graphics_readonly = 0x1000;
    constexpr std::uint32_t page_graphics_readwrite = 0x2000;
    constexpr std::uint32_t page_graphics_execute = 0x4000;
    constexpr std::uint32_t page_graphics_execute_read = 0x8000;
    constexpr std::uint32_t page_graphics_execute_readwrite = 0x10000;
    constexpr std::uint32_t page_graphics_coherent = 0x20000;
    constexpr std::uint32_t page_enclave_thread_control = 0x80000000;
    constexpr std::uint32_t page_revert_to_file_map = 0x80000000;
    constexpr std::uint32_t page_targets_no_update = 0x40000000;
    constexpr std::uint32_t page_targets_invalid = 0x40000000;
    constexpr std::uint32_t page_enclave_unvalidated = 0x20000000;
    constexpr std::uint32_t page_enclave_decommit = 0x10000000;

    constexpr std::uint32_t file_map_write = 0x00000002ul;
    constexpr std::uint32_t file_map_read = 0x00000004ul;
    constexpr std::uint32_t file_map_all_access = 0x000f001ful;
    constexpr std::uint32_t file_map_execute = 0x00000020ul;
    constexpr std::uint32_t file_map_copy = 0x00000001ul;
    constexpr std::uint32_t file_map_reserve = 0x80000000ul;
    constexpr std::uint32_t file_map_targets_invalid = 0x40000000ul;
    constexpr std::uint32_t file_map_large_pages = 0x20000000ul;

    // Structures
    struct memory_basic_information
    {
        void* base_address;
        void* allocation_base;
        std::uint32_t allocation_protect;
        std::size_t region_size;
        std::uint32_t state;
        std::uint32_t protect;
        std::uint32_t type;
    };

    struct memory_basic_information32
    {
        std::uint32_t base_address;
        std::uint32_t allocation_base;
        std::uint32_t allocation_protect;
        std::uint32_t region_size;
        std::uint32_t state;
        std::uint32_t protect;
        std::uint32_t type;
    };

    struct alignas(16) memory_basic_information64
    {
        std::uint64_t base_address;
        std::uint64_t allocation_base;
        std::uint32_t allocation_protect;
        std::uint32_t __alignment1;
        std::uint64_t region_size;
        std::uint32_t state;
        std::uint32_t protect;
        std::uint32_t type;
        std::uint32_t __alignment2;
    };

    // Functions
    __declspec(dllimport)
    void* __stdcall VirtualAlloc(void* address, std::size_t size, std::uint32_t allocationType, std::uint32_t protect);

    __declspec(dllimport)
    void* __stdcall VirtualAllocEx(
        handle_t process,
        void* address,
        std::size_t size,
        std::uint32_t allocationType,
        std::uint32_t protect);

    __declspec(dllimport)
    bool_t __stdcall VirtualProtect(void* address, std::size_t size, std::uint32_t newProtect, std::uint32_t* oldProtect);

    __declspec(dllimport)
    _Success_(return != FALSE)
    bool_t __stdcall VirtualProtectEx(
        handle_t process,
        void* address,
        std::size_t size,
        std::uint32_t newProtect,
        std::uint32_t* oldProtect);

    __declspec(dllimport)
    bool_t __stdcall VirtualFreeEx(handle_t process, void* address, std::size_t size, std::uint32_t freeType);

    __declspec(dllimport)
    bool_t __stdcall VirtualFree(void* address, std::size_t size, std::uint32_t freeType);

    __declspec(dllimport)
    std::size_t __stdcall VirtualQuery(const void* address, memory_basic_information* buffer, std::size_t bufferLength);

    __declspec(dllimport)
    std::size_t __stdcall VirtualQueryEx(
        handle_t process,
        const void* address,
        memory_basic_information* buffer,
        std::size_t bufferLength);

    __declspec(dllimport)
    bool_t __stdcall VirtualLock(void* address, std::size_t size);

    __declspec(dllimport)
    bool_t __stdcall VirtualUnlock(void* address, std::size_t size);

    __declspec(dllimport)
    bool_t __stdcall ReadProcessMemory(
        handle_t process,
        const void* baseAddress,
        void* buffer,
        std::size_t bufferSize,
        std::size_t* bytesRead);

    __declspec(dllimport)
    bool_t __stdcall WriteProcessMemory(
        handle_t process,
        void* baseAddress,
        const void* buffer,
        std::size_t bufferSize,
        std::size_t* bytesWritten);

    __declspec(dllimport)
    handle_t __stdcall CreateFileMappingA(
        handle_t file,
        security_attributes* fileMappingAttributes,
        std::uint32_t protect,
        std::uint32_t maximumSizeHigh,
        std::uint32_t maximumSizeLow,
        const char* name);

    __declspec(dllimport)
    handle_t __stdcall CreateFileMappingW(
        handle_t file,
        security_attributes* fileMappingAttributes,
        std::uint32_t protect,
        std::uint32_t maximumSizeHigh,
        std::uint32_t maximumSizeLow,
        const wchar_t* name);

    __declspec(dllimport)
    void* __stdcall MapViewOfFile(
        handle_t fileMappingObject,
        std::uint32_t dwDesiredAccess,
        std::uint32_t fileOffsetHigh,
        std::uint32_t fileOffsetLow,
        std::size_t numberOfBytesToMap);

    __declspec(dllimport)
    bool_t __stdcall UnmapViewOfFile(const void* baseAddress);

    __declspec(dllimport)
    bool_t __stdcall FlushViewOfFile(const void* baseAddress, std::size_t numberOfBytesToFlush);
}
}
