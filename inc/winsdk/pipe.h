#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Functions
    __declspec(dllimport)
    bool_t __stdcall CreatePipe(
        handle_t* readPipe,
        handle_t* writePipe,
        security_attributes* pipeAttributes,
        std::uint32_t size);

    __declspec(dllimport)
    handle_t __stdcall CreateNamedPipeA(
        const char* name,
        std::uint32_t openMode,
        std::uint32_t pipeMode,
        std::uint32_t maxInstances,
        std::uint32_t outBufferSize,
        std::uint32_t inBufferSize,
        std::uint32_t defaultTimeOut,
        security_attributes* securityAttributes);

    __declspec(dllimport)
    handle_t __stdcall CreateNamedPipeW(
        const wchar_t* name,
        std::uint32_t openMode,
        std::uint32_t pipeMode,
        std::uint32_t maxInstances,
        std::uint32_t outBufferSize,
        std::uint32_t inBufferSize,
        std::uint32_t defaultTimeOut,
        security_attributes* securityAttributes);

    __declspec(dllimport)
    bool_t __stdcall ConnectNamedPipe(handle_t namedPipe, overlapped* overlapped);

    __declspec(dllimport)
    bool_t __stdcall WaitNamedPipeA(const char* namedPipeName, std::uint32_t timeOut);

    __declspec(dllimport)
    bool_t __stdcall DisconnectNamedPipe(handle_t namedPipe);

    __declspec(dllimport)
    bool_t __stdcall CallNamedPipeA(
        const char* namedPipeName,
        void* inBuffer,
        std::uint32_t inBufferSize,
        void* outBuffer,
        std::uint32_t outBufferSize,
        std::uint32_t* bytesRead,
        std::uint32_t timeOut);
}
}
