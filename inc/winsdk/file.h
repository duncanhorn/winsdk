﻿#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Constants
    constexpr std::uint32_t generic_read = 0x80000000ul;
    constexpr std::uint32_t generic_write = 0x40000000ul;
    constexpr std::uint32_t generic_execute = 0x20000000ul;
    constexpr std::uint32_t generic_all = 0x10000000ul;

    constexpr std::uint32_t file_share_read = 0x00000001ul;
    constexpr std::uint32_t file_share_write = 0x00000002ul;
    constexpr std::uint32_t file_share_delete = 0x00000004ul;

    constexpr std::uint32_t create_new = 1;
    constexpr std::uint32_t create_always = 2;
    constexpr std::uint32_t open_existing = 3;
    constexpr std::uint32_t open_always = 4;
    constexpr std::uint32_t truncate_existing = 5;

    constexpr std::uint32_t file_attribute_readonly = 0x00000001ul;
    constexpr std::uint32_t file_attribute_hidden = 0x00000002ul;
    constexpr std::uint32_t file_attribute_system = 0x00000004ul;
    constexpr std::uint32_t file_attribute_directory = 0x00000010ul;
    constexpr std::uint32_t file_attribute_archive = 0x00000020ul;
    constexpr std::uint32_t file_attribute_device = 0x00000040ul;
    constexpr std::uint32_t file_attribute_normal = 0x00000080ul;
    constexpr std::uint32_t file_attribute_temporary = 0x00000100ul;
    constexpr std::uint32_t file_attribute_sparse_file = 0x00000200ul;
    constexpr std::uint32_t file_attribute_reparse_point = 0x00000400ul;
    constexpr std::uint32_t file_attribute_compressed = 0x00000800ul;
    constexpr std::uint32_t file_attribute_offline = 0x00001000ul;
    constexpr std::uint32_t file_attribute_not_content_indexed = 0x00002000ul;
    constexpr std::uint32_t file_attribute_encrypted = 0x00004000ul;
    constexpr std::uint32_t file_attribute_integrity_stream = 0x00008000ul;
    constexpr std::uint32_t file_attribute_virtual = 0x00010000ul;
    constexpr std::uint32_t file_attribute_no_scrub_data = 0x00020000ul;
    constexpr std::uint32_t file_attribute_ea = 0x00040000ul;
    constexpr std::uint32_t file_attribute_pinned = 0x00080000ul;
    constexpr std::uint32_t file_attribute_unpinned = 0x00100000ul;
    constexpr std::uint32_t file_attribute_recall_on_open = 0x00040000ul;
    constexpr std::uint32_t file_attribute_recall_on_data_access = 0x00400000ul;
    constexpr std::uint32_t file_attribute_strictly_sequential = 0x20000000ul;

    constexpr std::uint32_t file_flag_write_through = 0x80000000ul;
    constexpr std::uint32_t file_flag_overlapped = 0x40000000ul;
    constexpr std::uint32_t file_flag_no_buffering = 0x20000000ul;
    constexpr std::uint32_t file_flag_random_access = 0x10000000ul;
    constexpr std::uint32_t file_flag_sequential_scan = 0x08000000ul;
    constexpr std::uint32_t file_flag_delete_on_close = 0x04000000ul;
    constexpr std::uint32_t file_flag_backup_semantics = 0x02000000ul;
    constexpr std::uint32_t file_flag_posix_semantics = 0x01000000ul;
    constexpr std::uint32_t file_flag_session_aware = 0x00800000ul;
    constexpr std::uint32_t file_flag_open_reparse_point = 0x00200000ul;
    constexpr std::uint32_t file_flag_open_no_recall = 0x00100000ul;
    constexpr std::uint32_t file_flag_first_pipe_instance = 0x00080000ul;
    constexpr std::uint32_t file_flag_open_requiring_oplock = 0x00040000ul;

    // Functions
    __declspec(dllimport)
    bool_t __stdcall CreateDirectoryA(const char* pathName, security_attributes* securityAttributes);

    __declspec(dllimport)
    bool_t __stdcall CreateDirectoryW(const wchar_t* pathName, security_attributes* securityAttributes);

    __declspec(dllimport)
    handle_t __stdcall CreateFileA(
        const char* fileName,
        std::uint32_t desiredAccess,
        std::uint32_t shareMode,
        security_attributes* securityAttributes,
        std::uint32_t creationDisposition,
        std::uint32_t flagsAndAttributes,
        handle_t templateFile);

    __declspec(dllimport)
    handle_t __stdcall CreateFileW(
        const wchar_t* fileName,
        std::uint32_t desiredAccess,
        std::uint32_t shareMode,
        security_attributes* securityAttributes,
        std::uint32_t creationDisposition,
        std::uint32_t flagsAndAttributes,
        handle_t templateFile);

    __declspec(dllimport)
    bool_t __stdcall DeleteFileA(const char* fileName);

    __declspec(dllimport)
    bool_t __stdcall DeleteFileW(const wchar_t* fileName);

    __declspec(dllimport)
    bool_t __stdcall ReadFile(
        handle_t file,
        void* buffer,
        std::uint32_t bytesToRead,
        std::uint32_t* bytesRead,
        overlapped* overlapped);

    __declspec(dllimport)
    bool_t __stdcall WriteFile(
        handle_t file,
        const void* buffer,
        std::uint32_t bytesToWrite,
        std::uint32_t* bytesWritten,
        overlapped* oOverlapped);

    __declspec(dllimport)
    bool_t __stdcall GetFileSizeEx(handle_t file, std::int64_t* fileSize);
}
}
