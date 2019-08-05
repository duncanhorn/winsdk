#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Constants
    constexpr std::uint32_t startf_useshowwindow = 0x00000001;
    constexpr std::uint32_t startf_usesize = 0x00000002;
    constexpr std::uint32_t startf_useposition = 0x00000004;
    constexpr std::uint32_t startf_usecountchars = 0x00000008;
    constexpr std::uint32_t startf_usefillattribute = 0x00000010;
    constexpr std::uint32_t startf_runfullscreen = 0x00000020;
    constexpr std::uint32_t startf_forceonfeedback = 0x00000040;
    constexpr std::uint32_t startf_forceofffeedback = 0x00000080;
    constexpr std::uint32_t startf_usestdhandles = 0x00000100;
    constexpr std::uint32_t startf_usehotkey = 0x00000200;
    constexpr std::uint32_t startf_titleislinkname = 0x00000800;
    constexpr std::uint32_t startf_titleisappid = 0x00001000;
    constexpr std::uint32_t startf_preventpinning = 0x00002000;
    constexpr std::uint32_t startf_untrustedsource = 0x00008000;

    constexpr std::uint32_t std_input_handle = 0xFFFFFFF6; // -10
    constexpr std::uint32_t std_output_handle = 0xFFFFFFF5; // -11
    constexpr std::uint32_t std_error_handle = 0xFFFFFFF4; // -12

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

    __declspec(dllimport)
    handle_t __stdcall GetStdHandle(std::uint32_t stdHandle);
}
}
