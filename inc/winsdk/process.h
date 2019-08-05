#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Structures
    struct startupinfoa
    {
        std::uint32_t size;
        char* reserved;
        char* desktop;
        char* title;
        std::uint32_t x;
        std::uint32_t y;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t dwXCountChars;
        std::uint32_t dwYCountChars;
        std::uint32_t fill_attribute;
        std::uint32_t flags;
        std::uint16_t show_window;
        std::uint16_t reserved2;
        std::uint8_t* reserved3;
        handle_t std_input;
        handle_t std_output;
        handle_t std_error;
    };

    struct startupinfoexa
    {
        startupinfoa startup_info;
        void* attribute_list;
    };

    struct startupinfow
    {
        std::uint32_t size;
        wchar_t* reserved;
        wchar_t* desktop;
        wchar_t* title;
        std::uint32_t x;
        std::uint32_t y;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t dwXCountChars;
        std::uint32_t dwYCountChars;
        std::uint32_t fill_attribute;
        std::uint32_t flags;
        std::uint16_t show_window;
        std::uint16_t reserved2;
        std::uint8_t* reserved3;
        handle_t std_input;
        handle_t std_output;
        handle_t std_error;
    };

    struct startupinfoexw
    {
        startupinfow startup_info;
        void* attribute_list;
    };

    struct process_information
    {
        handle_t process;
        handle_t thread;
        std::uint32_t process_id;
        std::uint32_t thread_id;
    };

    // Functions
    __declspec(dllimport)
    bool_t __stdcall CreateProcessA(
        const char* applicationName,
        char* commandLine,
        security_attributes* processAttributes,
        security_attributes* threadAttributes,
        bool_t inheritHandles,
        std::uint32_t creationFlags,
        void* environment,
        const char* currentDirectory,
        startupinfoa* startupInfo,
        process_information* processInformation);

    __declspec(dllimport)
    bool_t __stdcall CreateProcessW(
        const wchar_t* applicationName,
        wchar_t* commandLine,
        security_attributes* processAttributes,
        security_attributes* threadAttributes,
        bool_t inheritHandles,
        std::uint32_t creationFlags,
        void* environment,
        const wchar_t* currentDirectory,
        startupinfow* startupInfo,
        process_information* processInformation);

    __declspec(dllimport)
    bool_t __stdcall GetExitCodeProcess(
        handle_t process,
        std::uint32_t* exitCode);
}
}
