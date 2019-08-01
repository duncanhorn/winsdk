#pragma once

#include "exception.h"
#include "image.h"
#include "unknown.h"

extern "C"
{
namespace winsdk
{
    // Forward declare
    struct IDebugBreakpoint;
    struct IDebugBreakpoint2;
    struct IDebugBreakpoint3;
    struct IDebugClient;
    struct IDebugEventCallbacks;
    struct IDebugEventCallbacksWide;
    struct IDebugEventContextCallbacks;
    struct IDebugInputCallbacks;
    struct IDebugOutputCallbacks;
    struct IDebugOutputCallbacksWide;
    struct IDebugOutputStream;
    struct IDebugSymbolGroup;
    struct IDebugSymbolGroup2;

    struct extstacktrace32;
    struct extstacktrace64;

    // Type definitions
    using windbg_output_routine = void (__cdecl)(const char* format, ...);

    using windbg_get_expression32 = std::uint32_t (__stdcall)(const char* expression);

    using windbg_get_expression64 = std::uint64_t (__stdcall)(const char* expression);

    using windbg_get_symbol32 = void (__stdcall)(std::uint32_t offset, char* buffer, std::uint32_t* displacement);

    using windbg_get_symbol64 = void (__stdcall)(std::uint64_t offset, char* buffer, std::uint64_t* displacement);

    using windbg_disasm32 = std::uint32_t (__stdcall)(
        std::uint32_t* offset,
        const char* buffer,
        std::uint32_t showEffectiveAddress);

    using windbg_disasm64 = std::uint32_t (__stdcall)(
        std::uint64_t* offset,
        const char* buffer,
        std::uint32_t showEffectiveAddress);

    using windbg_check_control_c = std::uint32_t (__stdcall)();

    using windbg_read_process_memory_routine32 = std::uint32_t (__stdcall)(
        std::uint32_t offset,
        void* buffer,
        std::uint32_t bufferSize,
        std::uint32_t* bytesRead);

    using windbg_read_process_memory_routine64 = std::uint32_t (__stdcall)(
        std::uint64_t offset,
        void* buffer,
        std::uint32_t bufferSize,
        std::uint32_t* bytesRead);

    using windbg_write_process_memory_routine32 = std::uint32_t (__stdcall)(
        std::uint32_t offset,
        const void* buffer,
        std::uint32_t bufferSize,
        std::uint32_t* bytesWritten);

    using windbg_write_process_memory_routine64 = std::uint32_t (__stdcall)(
        std::uint64_t offset,
        const void* buffer,
        std::uint32_t bufferSize,
        std::uint32_t* bytesWritten);

    using windbg_get_thread_context_routine = std::uint32_t (__stdcall)(
        std::uint32_t processor,
        context* context,
        std::uint32_t sizeOfContext);

    using windbg_set_thread_context_routine = std::uint32_t (__stdcall)(
        std::uint32_t processor,
        context* context,
        std::uint32_t sizeOfContext);

    using windbg_ioctl_routine = std::uint32_t (__stdcall)(std::uint16_t ioctlType, void* data, std::uint32_t size);

    using windbg_stacktrace_routine32 = std::uint32_t (__stdcall)(
        std::uint32_t framePointer,
        std::uint32_t stackPointer,
        std::uint32_t programCounter,
        extstacktrace32* stackFrames,
        std::uint32_t frames);

    using windbg_stacktrace_routine64 = std::uint32_t (__stdcall)(
        std::uint64_t framePointer,
        std::uint64_t stackPointer,
        std::uint64_t programCounter,
        extstacktrace64* stackFrames,
        std::uint32_t frames);

    // Constants

    // Structures
    struct symbol_info_ex
    {
        std::uint32_t size_of_struct;
        std::uint32_t type_of_info;
        std::uint64_t offset;
        std::uint32_t line;
        std::uint32_t displacement;
        std::uint32_t reserved[4];
    };

    struct debug_breakpoint_parameters
    {
        std::uint64_t offset;
        std::uint32_t id;
        std::uint32_t break_type;
        std::uint32_t proc_type;
        std::uint32_t flags;
        std::uint32_t data_size;
        std::uint32_t data_access_type;
        std::uint32_t pass_count;
        std::uint32_t current_pass_count;
        std::uint32_t match_thread;
        std::uint32_t command_size;
        std::uint32_t offset_expression_size;
    };

    struct debug_stack_frame
    {
        std::uint64_t instruction_offset;
        std::uint64_t return_offset;
        std::uint64_t frame_offset;
        std::uint64_t stack_offset;
        std::uint64_t func_table_entry;
        std::uint64_t params[4];
        std::uint64_t reserved[6];
        bool_t is_virtual;
        std::uint32_t frame_number;
    };

    struct debug_stack_frame_ex
    {
        std::uint64_t instruction_offset;
        std::uint64_t return_offset;
        std::uint64_t frame_offset;
        std::uint64_t stack_offset;
        std::uint64_t func_table_entry;
        std::uint64_t params[4];
        std::uint64_t reserved[6];
        bool_t is_virtual;
        std::uint32_t frame_number;
        std::uint32_t inline_frame_context;
        std::uint32_t reserved1;
    };

    struct debug_value
    {
        union
        {
            std::uint8_t i8;
            std::uint16_t i16;
            std::uint32_t i32;
            struct
            {
                std::uint64_t i64;
                bool_t nat;
            };
            float f32;
            double f64;
            std::uint8_t f80_bytes[10];
            std::uint8_t f82_bytes[11];
            std::uint8_t f128_bytes[16];
            std::uint8_t vi8[16];
            std::uint16_t vi16[8];
            std::uint32_t vi32[4];
            std::uint64_t vi64[2];
            float vf32[4];
            double vf64[2];
            struct
            {
                std::uint32_t low_part;
                std::uint32_t high_part;
            } i64_parts_32;
            struct
            {
                std::uint64_t low_part;
                std::int64_t high_part;
            } f128_parts_64;
            std::uint8_t raw_bytes[24];
        };
        std::uint32_t tail_of_raw_bytes;
        std::uint32_t type;
    };

    struct debug_breakpoint_parameters
    {
        std::uint64_t offset;
        std::uint32_t id;
        std::uint32_t break_type;
        std::uint32_t proc_type;
        std::uint32_t flags;
        std::uint32_t data_size;
        std::uint32_t data_access_type;
        std::uint32_t pass_count;
        std::uint32_t current_pass_count;
        std::uint32_t match_thread;
        std::uint32_t command_size;
        std::uint32_t offset_expression_size;
    };

    struct windbg_extension_apis32
    {
        std::uint32_t size;
        windbg_output_routine* output_routine;
        windbg_get_expression32* get_expression_routine;
        windbg_get_symbol32* get_symbol_routine;
        windbg_disasm32* disasm_routine;
        windbg_check_control_c* check_control_c_routine;
        windbg_read_process_memory_routine32* read_process_memory_routine;
        windbg_write_process_memory_routine32* write_process_memory_routine;
        windbg_get_thread_context_routine* get_thread_context_routine;
        windbg_set_thread_context_routine* set_thread_context_routine;
        windbg_ioctl_routine* ioctl_routine;
        windbg_stacktrace_routine32* stack_trace_routine;
    };

    typedef struct windbg_extension_apis64
    {
        std::uint32_t size;
        windbg_output_routine* output_routine;
        windbg_get_expression64* get_expression_routine;
        windbg_get_symbol64* get_symbol_routine;
        windbg_disasm64* disasm_routine;
        windbg_check_control_c* check_control_c_routine;
        windbg_read_process_memory_routine64* read_process_memory_routine;
        windbg_write_process_memory_routine64* write_process_memory_routine;
        windbg_get_thread_context_routine* get_thread_context_routine;
        windbg_set_thread_context_routine* set_thread_context_routine;
        windbg_ioctl_routine* ioctl_routine;
        windbg_stacktrace_routine64* stack_trace_routine;
    };

    struct extstacktrace32
    {
        std::uint32_t frame_pointer;
        std::uint32_t program_counter;
        std::uint32_t return_address;
        std::uint32_t args[4];
    };

    struct extstacktrace64
    {
        std::uint64_t frame_pointer;
        std::uint64_t program_counter;
        std::uint64_t return_address;
        std::uint64_t args[4];
    };

    struct debug_specific_filter_parameters
    {
        std::uint32_t execution_option;
        std::uint32_t continue_option;
        std::uint32_t text_size;
        std::uint32_t command_size;
        std::uint32_t argument_size;
    };

    struct debug_exception_filter_parameters
    {
        std::uint32_t execution_option;
        std::uint32_t continue_option;
        std::uint32_t text_size;
        std::uint32_t command_size;
        std::uint32_t second_command_size;
        std::uint32_t exception_code;
    };

    struct [[alignas(16)]] memory_basic_information64
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

    struct debug_register_description
    {
        std::uint32_t type;
        std::uint32_t flags;
        std::uint32_t subreg_master;
        std::uint32_t subreg_length;
        std::uint64_t subreg_mask;
        std::uint32_t subreg_shift;
        std::uint32_t reserved0;
    };

    struct debug_symbol_parameters
    {
        std::uint64_t module;
        std::uint32_t type_id;
        std::uint32_t parent_symbol;
        std::uint32_t sub_elements;
        std::uint32_t flags;
        std::uint64_t reserved;
    };

    struct debug_symbol_entry
    {
        std::uint64_t module_base;
        std::uint64_t offset;
        std::uint64_t id;
        std::uint64_t arg64;
        std::uint32_t size;
        std::uint32_t flags;
        std::uint32_t type_id;
        std::uint32_t name_size;
        std::uint32_t token;
        std::uint32_t tag;
        std::uint32_t arg32;
        std::uint32_t reserved;
    };

    struct debug_module_parameters
    {
        std::uint64_t base;
        std::uint32_t size;
        std::uint32_t time_date_stamp;
        std::uint32_t checksum;
        std::uint32_t flags;
        std::uint32_t symbol_type;
        std::uint32_t image_name_size;
        std::uint32_t module_name_size;
        std::uint32_t loaded_image_name_size;
        std::uint32_t symbol_file_name_size;
        std::uint32_t mapped_image_name_size;
        std::uint64_t reserved[2];
    };

    struct debug_module_and_id
    {
        std::uint64_t module_base;
        std::uint64_t id;
    };

    struct debug_offset_region
    {
        std::uint64_t base;
        std::uint64_t size;
    };

    struct debug_symbol_source_entry
    {
        std::uint64_t module_base;
        std::uint64_t offset;
        std::uint64_t file_name_id;
        std::uint64_t engine_internal;
        std::uint32_t size;
        std::uint32_t flags;
        std::uint32_t file_name_size;
        std::uint32_t start_line;
        std::uint32_t end_line;
        std::uint32_t start_column;
        std::uint32_t end_column;
        std::uint32_t reserved;
    };

    // Functions
    __declspec(dllimport)
    std::int32_t __stdcall DebugConnect(const char* remoteOptions, const guid& iid, void** obj);

    __declspec(dllimport)
    std::int32_t __stdcall DebugConnectWide(const wchar_t* remoteOptions, const guid& iid, void** obj);

    __declspec(dllimport)
    std::int32_t __stdcall DebugCreate(const guid& iid, void** obj);

    __declspec(dllimport)
    std::int32_t __stdcall DebugCreateEx(const guid& iid, std::uint32_t dbgEngOptions, void** obj);

    // Interfaces
    struct IDebugAdvanced : IUnknown
    {
        virtual std::int32_t __stdcall GetThreadContext(void* context, std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall SetThreadContext(void* context, std::uint32_t contextSize) noexcept = 0;
    };

    struct IDebugAdvanced2 : IDebugAdvanced
    {
        virtual std::int32_t __stdcall Request(
            std::uint32_t request,
            void* inBuffer,
            std::uint32_t inBufferSize,
            void* outBuffer,
            std::uint32_t outBufferSize,
            std::uint32_t* outSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceFileInformation(
            std::uint32_t which,
            char* sourceFile,
            std::uint64_t arg64,
            std::uint32_t arg32,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize) noexcept = 0;
        virtual std::int32_t __stdcall FindSourceFileAndToken(
            std::uint32_t startElement,
            std::uint64_t modAddr,
            const char* file,
            std::uint32_t flags,
            void* fileToken,
            std::uint32_t fileTokenSize,
            std::uint32_t* foundElement,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* foundSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolInformation(
            std::uint32_t which,
            std::uint64_t arg64,
            std::uint32_t arg32,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize,
            char* stringBuffer,
            std::uint32_t stringBufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemObjectInformation(
            std::uint32_t which,
            std::uint64_t arg64,
            std::uint32_t arg32,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize) noexcept = 0;
    };

    struct IDebugAdvanced3 : IDebugAdvanced2
    {
        virtual std::int32_t __stdcall GetSourceFileInformationWide(
            std::uint32_t which,
            wchar_t* sourceFile,
            std::uint64_t arg64,
            std::uint32_t arg32,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize) noexcept = 0;
        virtual std::int32_t __stdcall FindSourceFileAndTokenWide(
            std::uint32_t startElement,
            std::uint64_t modAddr,
            const wchar_t* file,
            std::uint32_t flags,
            void* fileToken,
            std::uint32_t fileTokenSize,
            std::uint32_t* foundElement,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* foundSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolInformationWide(
            std::uint32_t which,
            std::uint64_t arg64,
            std::uint32_t arg32,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize,
            wchar_t* stringBuffer,
            std::uint32_t stringBufferSize,
            std::uint32_t* stringSize) noexcept = 0;
    };

    struct IDebugAdvanced4 : IDebugAdvanced3
    {
        virtual std::int32_t __stdcall GetSymbolInformationWideEx(
            std::uint32_t which,
            std::uint64_t arg64,
            std::uint32_t arg32,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize,
            wchar_t* stringBuffer,
            std::uint32_t stringBufferSize,
            std::uint32_t* stringSize,
            symbol_info_ex* infoEx) noexcept = 0;
    };

    struct IDebugBreakpoint : IUnknown
    {
        virtual std::int32_t __stdcall GetId(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetType(std::uint32_t* breakType, std::uint32_t* procType) noexcept = 0;
        virtual std::int32_t __stdcall GetAdder(IDebugClient** adder) noexcept = 0;
        virtual std::int32_t __stdcall GetFlags(std::uint32_t* flags) noexcept = 0;
        virtual std::int32_t __stdcall AddFlags(std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall RemoveFlags(std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall SetFlags(std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall SetOffset(std::uint64_t offset) noexcept = 0;
        virtual std::int32_t __stdcall GetDataParameters(std::uint32_t* size, std::uint32_t* accessType) noexcept = 0;
        virtual std::int32_t __stdcall SetDataParameters(std::uint32_t size, std::uint32_t accessType) noexcept = 0;
        virtual std::int32_t __stdcall GetPassCount(std::uint32_t* count) noexcept = 0;
        virtual std::int32_t __stdcall SetPassCount(std::uint32_t count) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentPassCount(std::uint32_t* count) noexcept = 0;
        virtual std::int32_t __stdcall GetMatchThreadId(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall SetMatchThreadId(std::uint32_t thread) noexcept = 0;
        virtual std::int32_t __stdcall GetCommand(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* commandSize) noexcept = 0;
        virtual std::int32_t __stdcall SetCommand(const char* command) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetExpression(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* expressionSize) noexcept = 0;
        virtual std::int32_t __stdcall SetOffsetExpression(const char* expression) noexcept = 0;
        virtual std::int32_t __stdcall GetParameters(debug_breakpoint_parameters* params) noexcept = 0;
    };

    struct IDebugBreakpoint2 : IDebugBreakpoint
    {
        virtual std::int32_t __stdcall GetCommandWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* commandSize) noexcept = 0;
        virtual std::int32_t __stdcall SetCommandWide(const wchar_t* command) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetExpressionWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* expressionSize) noexcept = 0;
        virtual std::int32_t __stdcall SetOffsetExpressionWide(const wchar_t* expression) noexcept = 0;
    };

    struct IDebugBreakpoint3 : IDebugBreakpoint2
    {
        virtual std::int32_t __stdcall GetGuid(guid* guid) noexcept = 0;
    };

    struct IDebugClient : IUnknown
    {
        virtual std::int32_t __stdcall AttachKernel(std::uint32_t flags, const char* connectOptions) noexcept = 0;
        virtual std::int32_t __stdcall GetKernelConnectionOptions(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* optionsSize) noexcept = 0;
        virtual std::int32_t __stdcall SetKernelConnectionOptions(const char* options) noexcept = 0;
        virtual std::int32_t __stdcall StartProcessServer(
            std::uint32_t flags,
            const char* options,
            void* reserved) noexcept = 0;
        virtual std::int32_t __stdcall ConnectProcessServer(
            const char* remoteOptions,
            std::uint64_t* server) noexcept = 0;
        virtual std::int32_t __stdcall DisconnectProcessServer(std::uint64_t server) noexcept = 0;
        virtual std::int32_t __stdcall GetRunningProcessSystemIds(
            std::uint64_t server,
            std::uint32_t* ids,
            std::uint32_t count,
            std::uint32_t* actualCount) noexcept = 0;
        virtual std::int32_t __stdcall GetRunningProcessSystemIdByExecutableName(
            std::uint64_t server,
            const char* exeName,
            std::uint32_t flags,
            std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetRunningProcessDescription(
            std::uint64_t server,
            std::uint32_t systemId,
            std::uint32_t flags,
            char* exeName,
            std::uint32_t exeNameSize,
            std::uint32_t* actualExeNameSize,
            char* description,
            std::uint32_t descriptionSize,
            std::uint32_t* actualDescriptionSize) noexcept = 0;
        virtual std::int32_t __stdcall AttachProcess(
            std::uint64_t server,
            std::uint32_t processId,
            std::uint32_t attachFlags) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcess(
            std::uint64_t server,
            char* commandLine,
            std::uint32_t createFlags) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcessAndAttach(
            std::uint64_t server,
            char* commandLine,
            std::uint32_t createFlags,
            std::uint32_t processId,
            std::uint32_t attachFlags) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessOptions(std::uint32_t* options) noexcept = 0;
        virtual std::int32_t __stdcall AddProcessOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall RemoveProcessOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall SetProcessOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall OpenDumpFile(const char* dumpFile) noexcept = 0;
        virtual std::int32_t __stdcall WriteDumpFile(const char* dumpFile, std::uint32_t qualifier) noexcept = 0;
        virtual std::int32_t __stdcall ConnectSession(std::uint32_t flags, std::uint32_t historyLimit) noexcept = 0;
        virtual std::int32_t __stdcall StartServer(const char* options) noexcept = 0;
        virtual std::int32_t __stdcall OutputServers(
            std::uint32_t outputControl,
            const char* machine,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall TerminateProcesses() noexcept = 0;
        virtual std::int32_t __stdcall DetachProcesses() noexcept = 0;
        virtual std::int32_t __stdcall EndSession(std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetExitCode(std::uint32_t* code) noexcept = 0;
        virtual std::int32_t __stdcall DispatchCallbacks(std::uint32_t timeout) noexcept = 0;
        virtual std::int32_t __stdcall ExitDispatch(IDebugClient* client) noexcept = 0;
        virtual std::int32_t __stdcall CreateClient(IDebugClient** client) noexcept = 0;
        virtual std::int32_t __stdcall GetInputCallbacks(IDebugInputCallbacks** callbacks) noexcept = 0;
        virtual std::int32_t __stdcall SetInputCallbacks(IDebugInputCallbacks* callbacks) noexcept = 0;
        virtual std::int32_t __stdcall GetOutputCallbacks(IDebugOutputCallbacks** callbacks) noexcept = 0;
        virtual std::int32_t __stdcall SetOutputCallbacks(IDebugOutputCallbacks* callbacks) noexcept = 0;
        virtual std::int32_t __stdcall GetOutputMask(std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall SetOutputMask(std::uint32_t mask) noexcept = 0;
        virtual std::int32_t __stdcall GetOtherOutputMask(IDebugClient* client, std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall SetOtherOutputMask(IDebugClient* client, std::uint32_t mask) noexcept = 0;
        virtual std::int32_t __stdcall GetOutputWidth(std::uint32_t* columns) noexcept = 0;
        virtual std::int32_t __stdcall SetOutputWidth(std::uint32_t columns) noexcept = 0;
        virtual std::int32_t __stdcall GetOutputLinePrefix(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* prefixSize) noexcept = 0;
        virtual std::int32_t __stdcall SetOutputLinePrefix(const char* prefix) noexcept = 0;
        virtual std::int32_t __stdcall GetIdentity(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* identitySize) noexcept = 0;
        virtual std::int32_t __stdcall OutputIdentity(
            std::uint32_t outputControl,
            std::uint32_t flags,
            const char* format) noexcept = 0;
        virtual std::int32_t __stdcall GetEventCallbacks(IDebugEventCallbacks** callbacks) noexcept = 0;
        virtual std::int32_t __stdcall SetEventCallbacks(IDebugEventCallbacks* callbacks) noexcept = 0;
        virtual std::int32_t __stdcall FlushCallbacks() noexcept = 0;
    };

    struct IDebugClient2 : IDebugClient
    {
        virtual std::int32_t __stdcall WriteDumpFile2(
            const char* dumpFile,
            std::uint32_t qualifier,
            std::uint32_t formatFlags,
            const char* comment) noexcept = 0;
        virtual std::int32_t __stdcall AddDumpInformationFile(const char* infoFile, std::uint32_t type) noexcept = 0;
        virtual std::int32_t __stdcall EndProcessServer(std::uint64_t server) noexcept = 0;
        virtual std::int32_t __stdcall WaitForProcessServerEnd(std::uint32_t timeout) noexcept = 0;
        virtual std::int32_t __stdcall IsKernelDebuggerEnabled() noexcept = 0;
        virtual std::int32_t __stdcall TerminateCurrentProcess() noexcept = 0;
        virtual std::int32_t __stdcall DetachCurrentProcess() noexcept = 0;
        virtual std::int32_t __stdcall AbandonCurrentProcess() noexcept = 0;
    };

    struct IDebugClient3 : IDebugClient2
    {
        virtual std::int32_t __stdcall GetRunningProcessSystemIdByExecutableNameWide(
            std::uint64_t server,
            const wchar_t* exeName,
            std::uint32_t flags,
            std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetRunningProcessDescriptionWide(
            std::uint64_t server,
            std::uint32_t systemId,
            std::uint32_t flags,
            wchar_t* exeName,
            std::uint32_t exeNameSize,
            std::uint32_t* actualExeNameSize,
            wchar_t* description,
            std::uint32_t descriptionSize,
            std::uint32_t* actualDescriptionSize) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcessWide(
            std::uint64_t server,
            wchar_t* commandLine,
            std::uint32_t createFlags) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcessAndAttachWide(
            std::uint64_t server,
            wchar_t* commandLine,
            std::uint32_t createFlags,
            std::uint32_t processId,
            std::uint32_t attachFlags) noexcept = 0;
    };

    struct IDebugClient4 : IDebugClient3
    {
        virtual std::int32_t __stdcall OpenDumpFileWide(const wchar_t* fileName, std::uint64_t fileHandle) noexcept = 0;
        virtual std::int32_t __stdcall WriteDumpFileWide(
            const wchar_t* fileName,
            std::uint64_t fileHandle,
            std::uint32_t qualifier,
            std::uint32_t formatFlags,
            const wchar_t* comment) noexcept = 0;
        virtual std::int32_t __stdcall AddDumpInformationFileWide(
            const wchar_t* fileName,
            std::uint64_t fileHandle,
            std::uint32_t type) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberDumpFiles(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetDumpFile(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* handle,
            std::uint32_t* type) noexcept = 0;
        virtual std::int32_t __stdcall GetDumpFileWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* handle,
            std::uint32_t* type) noexcept = 0;
    };

    struct IDebugClient5 : IDebugClient4
    {
        virtual std::int32_t __stdcall AttachKernelWide(
            std::uint32_t flags,
            const wchar_t* connectOptions) noexcept = 0;
        virtual std::int32_t __stdcall GetKernelConnectionOptionsWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* optionsSize) noexcept = 0;
        virtual std::int32_t __stdcall SetKernelConnectionOptionsWide(const wchar_t* options) noexcept = 0;
        virtual std::int32_t __stdcall StartProcessServerWide(
            std::uint32_t flags,
            const wchar_t* options,
            void* reserved) noexcept = 0;
        virtual std::int32_t __stdcall ConnectProcessServerWide(
            const wchar_t* remoteOptions,
            std::uint64_t* server) noexcept = 0;
        virtual std::int32_t __stdcall StartServerWide(const wchar_t* options) noexcept = 0;
        virtual std::int32_t __stdcall OutputServersWide(
            std::uint32_t outputControl,
            const wchar_t* machine,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetOutputCallbacksWide(IDebugOutputCallbacksWide** callbacks) noexcept = 0;
        virtual std::int32_t __stdcall SetOutputCallbacksWide(IDebugOutputCallbacksWide* callbacks) noexcept = 0;
        virtual std::int32_t __stdcall GetOutputLinePrefixWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* prefixSize) noexcept = 0;
        virtual std::int32_t __stdcall SetOutputLinePrefixWide(const wchar_t* prefix) noexcept = 0;
        virtual std::int32_t __stdcall GetIdentityWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* identitySize) noexcept = 0;
        virtual std::int32_t __stdcall OutputIdentityWide(
            std::uint32_t outputControl,
            std::uint32_t flags,
            const wchar_t* format) noexcept = 0;
        virtual std::int32_t __stdcall GetEventCallbacksWide(IDebugEventCallbacksWide** callbacks) noexcept = 0;
        virtual std::int32_t __stdcall SetEventCallbacksWide(IDebugEventCallbacksWide* callbacks) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcess2(
            std::uint64_t server,
            char* commandLine,
            void* optionsBuffer,
            std::uint32_t optionsBufferSize,
            const char* initialDirectory,
            const char* environment) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcess2Wide(
            std::uint64_t server,
            wchar_t* commandLine,
            void* optionsBuffer,
            std::uint32_t optionsBufferSize,
            const wchar_t* initialDirectory,
            const wchar_t* environment) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcessAndAttach2(
            std::uint64_t server,
            char* commandLine,
            void* optionsBuffer,
            std::uint32_t optionsBufferSize,
            const char* initialDirectory,
            const char* environment,
            std::uint32_t processId,
            std::uint32_t attachFlags) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcessAndAttach2Wide(
            std::uint64_t server,
            wchar_t* commandLine,
            void* optionsBuffer,
            std::uint32_t optionsBufferSize,
            const wchar_t* initialDirectory,
            const wchar_t* environment,
            std::uint32_t processId,
            std::uint32_t attachFlags) noexcept = 0;
        virtual std::int32_t __stdcall PushOutputLinePrefix(const char* newPrefix, std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall PushOutputLinePrefixWide(
            const wchar_t* newPrefix,
            std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall PopOutputLinePrefix(std::uint64_t handle) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberInputCallbacks(std::uint32_t* count) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberOutputCallbacks(std::uint32_t* count) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberEventCallbacks(
            std::uint32_t eventFlags,
            std::uint32_t* count) noexcept = 0;
        virtual std::int32_t __stdcall GetQuitLockString(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall SetQuitLockString(const char* string) noexcept = 0;
        virtual std::int32_t __stdcall GetQuitLockStringWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall SetQuitLockStringWide(const wchar_t* string) noexcept = 0;
    };

    struct IDebugClient6 : IDebugClient5
    {
        virtual std::int32_t __stdcall SetEventContextCallbacks(IDebugEventContextCallbacks* callbacks) noexcept = 0;
    };

    struct IDebugClient7 : IDebugClient6
    {
        virtual std::int32_t __stdcall SetClientContext(void* context, std::uint32_t contextSize) noexcept = 0;
    };

    struct IDebugPlmClient : IUnknown
    {
        virtual std::int32_t __stdcall LaunchPlmPackageForDebugWide(
            std::uint64_t server,
            std::uint32_t timeout,
            const wchar_t* packageFullName,
            const wchar_t* appName,
            const wchar_t* arguments,
            std::uint32_t* processId,
            std::uint32_t* threadId) noexcept = 0;
    };

    struct IDebugPlmClient2 : IDebugPlmClient
    {
        virtual std::int32_t __stdcall LaunchPlmBgTaskForDebugWide(
            std::uint64_t server,
            std::uint32_t timeout,
            const wchar_t* packageFullName,
            const wchar_t* backgroundTaskId,
            std::uint32_t* processId,
            std::uint32_t* threadId) noexcept = 0;
    };

    struct IDebugPlmClient3 : IDebugPlmClient2
    {
        virtual std::int32_t __stdcall QueryPlmPackageWide(
            std::uint64_t server,
            const wchar_t* packageFullName,
            IDebugOutputStream* stream) noexcept = 0;
        virtual std::int32_t __stdcall QueryPlmPackageList(
            std::uint64_t server,
            IDebugOutputStream* stream) noexcept = 0;
        virtual std::int32_t __stdcall EnablePlmPackageDebugWide(
            std::uint64_t server,
            const wchar_t* packageFullName) noexcept = 0;
        virtual std::int32_t __stdcall DisablePlmPackageDebugWide(
            std::uint64_t server,
            const wchar_t* packageFullName) noexcept = 0;
        virtual std::int32_t __stdcall SuspendPlmPackageWide(
            std::uint64_t server,
            const wchar_t* packageFullName) noexcept = 0;
        virtual std::int32_t __stdcall ResumePlmPackageWide(
            std::uint64_t server,
            const wchar_t* packageFullName) noexcept = 0;
        virtual std::int32_t __stdcall TerminatePlmPackageWide(
            std::uint64_t server,
            const wchar_t* packageFullName) noexcept = 0;
        virtual std::int32_t __stdcall LaunchAndDebugPlmAppWide(
            std::uint64_t server,
            const wchar_t* packageFullName,
            const wchar_t* appName,
            const wchar_t* arguments) noexcept = 0;
        virtual std::int32_t __stdcall ActivateAndDebugPlmBgTaskWide(
            std::uint64_t server,
            const wchar_t* packageFullName,
            const wchar_t* backgroundTaskId) noexcept = 0;
    };

    struct IDebugOutputStream : IUnknown
    {
        virtual std::int32_t __stdcall Write(
            const wchar_t* psz) noexcept = 0;
    };

    struct IDebugControl : IUnknown
    {
        virtual std::int32_t __stdcall GetInterrupt() noexcept = 0;
        virtual std::int32_t __stdcall SetInterrupt(
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetInterruptTimeout(
            std::uint32_t* seconds) noexcept = 0;
        virtual std::int32_t __stdcall SetInterruptTimeout(
            std::uint32_t seconds) noexcept = 0;
        virtual std::int32_t __stdcall GetLogFile(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* fileSize,
            bool_t* append) noexcept = 0;
        virtual std::int32_t __stdcall OpenLogFile(
            const char* file,
            bool_t append) noexcept = 0;
        virtual std::int32_t __stdcall CloseLogFile() noexcept = 0;
        virtual std::int32_t __stdcall GetLogMask(
            std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall SetLogMask(
            std::uint32_t mask) noexcept = 0;
        virtual std::int32_t __stdcall Input(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* inputSize) noexcept = 0;
        virtual std::int32_t __stdcall ReturnInput(
            const char* buffer) noexcept = 0;
        virtual std::int32_t __cdecl Output(
            std::uint32_t mask,
            const char* format,
            ...) noexcept = 0;
        virtual std::int32_t __stdcall OutputVaList(
            std::uint32_t mask,
            const char* format,
            va_list Args) noexcept = 0;
        virtual std::int32_t __cdecl ControlledOutput(
            std::uint32_t outputControl,
            std::uint32_t mask,
            const char* format,
            ...) noexcept = 0;
        virtual std::int32_t __stdcall ControlledOutputVaList(
            std::uint32_t outputControl,
            std::uint32_t mask,
            const char* format,
            va_list Args) noexcept = 0;
        virtual std::int32_t __cdecl OutputPrompt(
            std::uint32_t outputControl,
            const char* format,
            ...) noexcept = 0;
        virtual std::int32_t __stdcall OutputPromptVaList(
            std::uint32_t outputControl,
            const char* format,
            va_list Args) noexcept = 0;
        virtual std::int32_t __stdcall GetPromptText(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* textSize) noexcept = 0;
        virtual std::int32_t __stdcall OutputCurrentState(
            std::uint32_t outputControl,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall OutputVersionInformation(
            std::uint32_t outputControl) noexcept = 0;
        virtual std::int32_t __stdcall GetNotifyEventHandle(
            std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall SetNotifyEventHandle(
            std::uint64_t handle) noexcept = 0;
        virtual std::int32_t __stdcall Assemble(
            std::uint64_t offset,
            const char* instr,
            std::uint64_t* endOffset) noexcept = 0;
        virtual std::int32_t __stdcall Disassemble(
            std::uint64_t offset,
            std::uint32_t flags,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* disassemblySize,
            std::uint64_t* endOffset) noexcept = 0;
        virtual std::int32_t __stdcall GetDisassembleEffectiveOffset(
            std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall OutputDisassembly(
            std::uint32_t outputControl,
            std::uint64_t offset,
            std::uint32_t flags,
            std::uint64_t* endOffset) noexcept = 0;
        virtual std::int32_t __stdcall OutputDisassemblyLines(
            std::uint32_t outputControl,
            std::uint32_t previousLines,
            std::uint32_t totalLines,
            std::uint64_t offset,
            std::uint32_t flags,
            std::uint32_t* offsetLine,
            std::uint64_t* startOffset,
            std::uint64_t* endOffset,
            std::uint64_t* lineOffsets) noexcept = 0;
        virtual std::int32_t __stdcall GetNearInstruction(
            std::uint64_t offset,
            std::int32_t delta,
            std::uint64_t* nearOffset) noexcept = 0;
        virtual std::int32_t __stdcall GetStackTrace(
            std::uint64_t frameOffset,
            std::uint64_t stackOffset,
            std::uint64_t instructionOffset,
            debug_stack_frame* frames,
            std::uint32_t framesSize,
            std::uint32_t* framesFilled) noexcept = 0;
        virtual std::int32_t __stdcall GetReturnOffset(
            std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall OutputStackTrace(
            std::uint32_t outputControl,
            debug_stack_frame* frames,
            std::uint32_t framesSize,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetDebuggeeType(
            std::uint32_t* targetClass,
            std::uint32_t* qualifier) noexcept = 0;
        virtual std::int32_t __stdcall GetActualProcessorType(
            std::uint32_t* type) noexcept = 0;
        virtual std::int32_t __stdcall GetExecutingProcessorType(
            std::uint32_t* type) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberPossibleExecutingProcessorTypes(
            std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetPossibleExecutingProcessorTypes(
            std::uint32_t start,
            std::uint32_t count,
            std::uint32_t* types) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberProcessors(
            std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemVersion(
            std::uint32_t* platformId,
            std::uint32_t* major,
            std::uint32_t* minor,
            char* servicePackString,
            std::uint32_t servicePackStringSize,
            std::uint32_t* servicePackStringUsed,
            std::uint32_t* servicePackNumber,
            char* buildString,
            std::uint32_t buildStringSize,
            std::uint32_t* buildStringUsed) noexcept = 0;
        virtual std::int32_t __stdcall GetPageSize(
            std::uint32_t* size) noexcept = 0;
        virtual std::int32_t __stdcall IsPointer64Bit() noexcept = 0;
        virtual std::int32_t __stdcall ReadBugCheckData(
            std::uint32_t* code,
            std::uint64_t* arg1,
            std::uint64_t* arg2,
            std::uint64_t* arg3,
            std::uint64_t* arg4) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberSupportedProcessorTypes(
            std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetSupportedProcessorTypes(
            std::uint32_t start,
            std::uint32_t count,
            std::uint32_t* types) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessorTypeNames(
            std::uint32_t type,
            char* fullNameBuffer,
            std::uint32_t fullNameBufferSize,
            std::uint32_t* fullNameSize,
            char* abbrevNameBuffer,
            std::uint32_t abbrevNameBufferSize,
            std::uint32_t* abbrevNameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetEffectiveProcessorType(
            std::uint32_t* type) noexcept = 0;
        virtual std::int32_t __stdcall SetEffectiveProcessorType(
            std::uint32_t type) noexcept = 0;
        virtual std::int32_t __stdcall GetExecutionStatus(
            std::uint32_t* status) noexcept = 0;
        virtual std::int32_t __stdcall SetExecutionStatus(
            std::uint32_t status) noexcept = 0;
        virtual std::int32_t __stdcall GetCodeLevel(
            std::uint32_t* level) noexcept = 0;
        virtual std::int32_t __stdcall SetCodeLevel(
            std::uint32_t level) noexcept = 0;
        virtual std::int32_t __stdcall GetEngineOptions(
            std::uint32_t* options) noexcept = 0;
        virtual std::int32_t __stdcall AddEngineOptions(
            std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall RemoveEngineOptions(
            std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall SetEngineOptions(
            std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemErrorControl(
            std::uint32_t* outputLevel,
            std::uint32_t* breakLevel) noexcept = 0;
        virtual std::int32_t __stdcall SetSystemErrorControl(
            std::uint32_t outputLevel,
            std::uint32_t breakLevel) noexcept = 0;
        virtual std::int32_t __stdcall GetTextMacro(
            std::uint32_t slot,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* macroSize) noexcept = 0;
        virtual std::int32_t __stdcall SetTextMacro(
            std::uint32_t slot,
            const char* macro) noexcept = 0;
        virtual std::int32_t __stdcall GetRadix(
            std::uint32_t* radix) noexcept = 0;
        virtual std::int32_t __stdcall SetRadix(
            std::uint32_t radix) noexcept = 0;
        virtual std::int32_t __stdcall Evaluate(
            const char* expression,
            std::uint32_t desiredType,
            debug_value* value,
            std::uint32_t* remainderIndex) noexcept = 0;
        virtual std::int32_t __stdcall CoerceValue(
            debug_value* in,
            std::uint32_t outType,
            debug_value* out) noexcept = 0;
        virtual std::int32_t __stdcall CoerceValues(
            std::uint32_t count,
            debug_value* in,
            std::uint32_t* outTypes,
            debug_value* out) noexcept = 0;
        virtual std::int32_t __stdcall Execute(
            std::uint32_t outputControl,
            const char* command,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall ExecuteCommandFile(
            std::uint32_t outputControl,
            const char* commandFile,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberBreakpoints(
            std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetBreakpointByIndex(
            std::uint32_t index,
            IDebugBreakpoint** bp) noexcept = 0;
        virtual std::int32_t __stdcall GetBreakpointById(
            std::uint32_t id,
            IDebugBreakpoint** bp) noexcept = 0;
        virtual std::int32_t __stdcall GetBreakpointParameters(
            std::uint32_t count,
            std::uint32_t* ids,
            std::uint32_t start,
            debug_breakpoint_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall AddBreakpoint(
            std::uint32_t type,
            std::uint32_t desiredId,
            IDebugBreakpoint** bp) noexcept = 0;
        virtual std::int32_t __stdcall RemoveBreakpoint(
            IDebugBreakpoint* bp) noexcept = 0;
        virtual std::int32_t __stdcall AddExtension(
            const char* path,
            std::uint32_t flags,
            std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall RemoveExtension(
            std::uint64_t handle) noexcept = 0;
        virtual std::int32_t __stdcall GetExtensionByPath(
            const char* path,
            std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall CallExtension(
            std::uint64_t handle,
            const char* function,
            const char* arguments) noexcept = 0;
        virtual std::int32_t __stdcall GetExtensionFunction(
            std::uint64_t handle,
            const char* funcName,
            std::intptr_t(__stdcall* function)()) noexcept = 0;
        virtual std::int32_t __stdcall GetWindbgExtensionApis32(
            windbg_extension_apis32* api) noexcept = 0;
        virtual std::int32_t __stdcall GetWindbgExtensionApis64(
            windbg_extension_apis64* api) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberEventFilters(
            std::uint32_t* specificEvents,
            std::uint32_t* specificExceptions,
            std::uint32_t* arbitraryExceptions) noexcept = 0;
        virtual std::int32_t __stdcall GetEventFilterText(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* textSize) noexcept = 0;
        virtual std::int32_t __stdcall GetEventFilterCommand(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* commandSize) noexcept = 0;
        virtual std::int32_t __stdcall SetEventFilterCommand(
            std::uint32_t index,
            const char* command) noexcept = 0;
        virtual std::int32_t __stdcall GetSpecificFilterParameters(
            std::uint32_t start,
            std::uint32_t count,
            debug_specific_filter_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall SetSpecificFilterParameters(
            std::uint32_t start,
            std::uint32_t count,
            debug_specific_filter_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall GetSpecificFilterArgument(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* argumentSize) noexcept = 0;
        virtual std::int32_t __stdcall SetSpecificFilterArgument(
            std::uint32_t index,
            const char* argument) noexcept = 0;
        virtual std::int32_t __stdcall GetExceptionFilterParameters(
            std::uint32_t count,
            std::uint32_t* codes,
            std::uint32_t start,
            debug_exception_filter_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall SetExceptionFilterParameters(
            std::uint32_t count,
            debug_exception_filter_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall GetExceptionFilterSecondCommand(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* commandSize) noexcept = 0;
        virtual std::int32_t __stdcall SetExceptionFilterSecondCommand(
            std::uint32_t index,
            const char* command) noexcept = 0;
        virtual std::int32_t __stdcall WaitForEvent(
            std::uint32_t flags,
            std::uint32_t timeout) noexcept = 0;
        virtual std::int32_t __stdcall GetLastEventInformation(
            std::uint32_t* type,
            std::uint32_t* processId,
            std::uint32_t* threadId,
            void* extraInformation,
            std::uint32_t extraInformationSize,
            std::uint32_t* extraInformationUsed,
            char* description,
            std::uint32_t descriptionSize,
            std::uint32_t* descriptionUsed) noexcept = 0;
    };

    struct IDebugControl2 : IDebugControl
    {
        virtual std::int32_t __stdcall GetCurrentTimeDate(
            std::uint32_t* timeDate) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentSystemUpTime(
            std::uint32_t* upTime) noexcept = 0;
        virtual std::int32_t __stdcall GetDumpFormatFlags(
            std::uint32_t* formatFlags) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberTextReplacements(
            std::uint32_t* numRepl) noexcept = 0;
        virtual std::int32_t __stdcall GetTextReplacement(
            const char* srcText,
            std::uint32_t index,
            char* srcBuffer,
            std::uint32_t srcBufferSize,
            std::uint32_t* srcSize,
            char* dstBuffer,
            std::uint32_t dstBufferSize,
            std::uint32_t* dstSize) noexcept = 0;
        virtual std::int32_t __stdcall SetTextReplacement(
            const char* srcText,
            const char* dstText) noexcept = 0;
        virtual std::int32_t __stdcall RemoveTextReplacements() noexcept = 0;
        virtual std::int32_t __stdcall OutputTextReplacements(
            std::uint32_t outputControl,
            std::uint32_t flags) noexcept = 0;
    };

    struct IDebugControl3 : IDebugControl2
    {
        virtual std::int32_t __stdcall GetAssemblyOptions(
            std::uint32_t* options) noexcept = 0;
        virtual std::int32_t __stdcall AddAssemblyOptions(
            std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall RemoveAssemblyOptions(
            std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall SetAssemblyOptions(
            std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall GetExpressionSyntax(
            std::uint32_t* flags) noexcept = 0;
        virtual std::int32_t __stdcall SetExpressionSyntax(
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall SetExpressionSyntaxByName(
            const char* abbrevName) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberExpressionSyntaxes(
            std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetExpressionSyntaxNames(
            std::uint32_t index,
            char* fullNameBuffer,
            std::uint32_t fullNameBufferSize,
            std::uint32_t* fullNameSize,
            char* abbrevNameBuffer,
            std::uint32_t abbrevNameBufferSize,
            std::uint32_t* abbrevNameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberEvents(
            std::uint32_t* events) noexcept = 0;
        virtual std::int32_t __stdcall GetEventIndexDescription(
            std::uint32_t index,
            std::uint32_t which,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* descSize) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentEventIndex(
            std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall SetNextEventIndex(
            std::uint32_t relation,
            std::uint32_t value,
            std::uint32_t* nextIndex) noexcept = 0;
    };

    struct IDebugControl4 : IDebugControl3
    {
        virtual std::int32_t __stdcall GetLogFileWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* fileSize,
            bool_t* append) noexcept = 0;
        virtual std::int32_t __stdcall OpenLogFileWide(
            const wchar_t* file,
            bool_t append) noexcept = 0;
        virtual std::int32_t __stdcall InputWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* inputSize) noexcept = 0;
        virtual std::int32_t __stdcall ReturnInputWide(
            const wchar_t* buffer) noexcept = 0;
        virtual std::int32_t __cdecl OutputWide(
            std::uint32_t mask,
            const wchar_t* format,
            ...) noexcept = 0;
        virtual std::int32_t __stdcall OutputVaListWide(
            std::uint32_t mask,
            const wchar_t* format,
            va_list Args) noexcept = 0;
        virtual std::int32_t __cdecl ControlledOutputWide(
            std::uint32_t outputControl,
            std::uint32_t mask,
            const wchar_t* format,
            ...) noexcept = 0;
        virtual std::int32_t __stdcall ControlledOutputVaListWide(
            std::uint32_t outputControl,
            std::uint32_t mask,
            const wchar_t* format,
            va_list Args) noexcept = 0;
        virtual std::int32_t __cdecl OutputPromptWide(
            std::uint32_t outputControl,
            const wchar_t* format,
            ...) noexcept = 0;
        virtual std::int32_t __stdcall OutputPromptVaListWide(
            std::uint32_t outputControl,
            const wchar_t* format,
            va_list Args) noexcept = 0;
        virtual std::int32_t __stdcall GetPromptTextWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* textSize) noexcept = 0;
        virtual std::int32_t __stdcall AssembleWide(
            std::uint64_t offset,
            const wchar_t* instr,
            std::uint64_t* endOffset) noexcept = 0;
        virtual std::int32_t __stdcall DisassembleWide(
            std::uint64_t offset,
            std::uint32_t flags,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* disassemblySize,
            std::uint64_t* endOffset) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessorTypeNamesWide(
            std::uint32_t type,
            wchar_t* fullNameBuffer,
            std::uint32_t fullNameBufferSize,
            std::uint32_t* fullNameSize,
            wchar_t* abbrevNameBuffer,
            std::uint32_t abbrevNameBufferSize,
            std::uint32_t* abbrevNameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetTextMacroWide(
            std::uint32_t slot,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* macroSize) noexcept = 0;
        virtual std::int32_t __stdcall SetTextMacroWide(
            std::uint32_t slot,
            const wchar_t* macro) noexcept = 0;
        virtual std::int32_t __stdcall EvaluateWide(
            const wchar_t* expression,
            std::uint32_t desiredType,
            debug_value* value,
            std::uint32_t* remainderIndex) noexcept = 0;
        virtual std::int32_t __stdcall ExecuteWide(
            std::uint32_t outputControl,
            const wchar_t* command,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall ExecuteCommandFileWide(
            std::uint32_t outputControl,
            const wchar_t* commandFile,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetBreakpointByIndex2(
            std::uint32_t index,
            IDebugBreakpoint2** bp) noexcept = 0;
        virtual std::int32_t __stdcall GetBreakpointById2(
            std::uint32_t id,
            IDebugBreakpoint2** bp) noexcept = 0;
        virtual std::int32_t __stdcall AddBreakpoint2(
            std::uint32_t type,
            std::uint32_t desiredId,
            IDebugBreakpoint2** bp) noexcept = 0;
        virtual std::int32_t __stdcall RemoveBreakpoint2(
            IDebugBreakpoint2* bp) noexcept = 0;
        virtual std::int32_t __stdcall AddExtensionWide(
            const wchar_t* path,
            std::uint32_t flags,
            std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall GetExtensionByPathWide(
            const wchar_t* path,
            std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall CallExtensionWide(
            std::uint64_t handle,
            const wchar_t* function,
            const wchar_t* arguments) noexcept = 0;
        virtual std::int32_t __stdcall GetExtensionFunctionWide(
            std::uint64_t handle,
            const wchar_t* funcName,
            std::intptr_t (__stdcall* function)()) noexcept = 0;
        virtual std::int32_t __stdcall GetEventFilterTextWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* textSize) noexcept = 0;
        virtual std::int32_t __stdcall GetEventFilterCommandWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* commandSize) noexcept = 0;
        virtual std::int32_t __stdcall SetEventFilterCommandWide(
            std::uint32_t index,
            const wchar_t* command) noexcept = 0;
        virtual std::int32_t __stdcall GetSpecificFilterArgumentWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* argumentSize) noexcept = 0;
        virtual std::int32_t __stdcall SetSpecificFilterArgumentWide(
            std::uint32_t index,
            const wchar_t* argument) noexcept = 0;
        virtual std::int32_t __stdcall GetExceptionFilterSecondCommandWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* commandSize) noexcept = 0;
        virtual std::int32_t __stdcall SetExceptionFilterSecondCommandWide(
            std::uint32_t index,
            const wchar_t* command) noexcept = 0;
        virtual std::int32_t __stdcall GetLastEventInformationWide(
            std::uint32_t* type,
            std::uint32_t* processId,
            std::uint32_t* threadId,
            void* extraInformation,
            std::uint32_t extraInformationSize,
            std::uint32_t* extraInformationUsed,
            wchar_t* description,
            std::uint32_t descriptionSize,
            std::uint32_t* descriptionUsed) noexcept = 0;
        virtual std::int32_t __stdcall GetTextReplacementWide(
            const wchar_t* srcText,
            std::uint32_t index,
            wchar_t* srcBuffer,
            std::uint32_t srcBufferSize,
            std::uint32_t* srcSize,
            wchar_t* dstBuffer,
            std::uint32_t dstBufferSize,
            std::uint32_t* dstSize) noexcept = 0;
        virtual std::int32_t __stdcall SetTextReplacementWide(
            const wchar_t* srcText,
            const wchar_t* dstText) noexcept = 0;
        virtual std::int32_t __stdcall SetExpressionSyntaxByNameWide(
            const wchar_t* abbrevName) noexcept = 0;
        virtual std::int32_t __stdcall GetExpressionSyntaxNamesWide(
            std::uint32_t index,
            wchar_t* fullNameBuffer,
            std::uint32_t fullNameBufferSize,
            std::uint32_t* fullNameSize,
            wchar_t* abbrevNameBuffer,
            std::uint32_t abbrevNameBufferSize,
            std::uint32_t* abbrevNameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetEventIndexDescriptionWide(
            std::uint32_t index,
            std::uint32_t which,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* descSize) noexcept = 0;
        virtual std::int32_t __stdcall GetLogFile2(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* fileSize,
            std::uint32_t* flags) noexcept = 0;
        virtual std::int32_t __stdcall OpenLogFile2(
            const char* file,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetLogFile2Wide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* fileSize,
            std::uint32_t* flags) noexcept = 0;
        virtual std::int32_t __stdcall OpenLogFile2Wide(
            const wchar_t* file,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemVersionValues(
            std::uint32_t* platformId,
            std::uint32_t* win32Major,
            std::uint32_t* win32Minor,
            std::uint32_t* kdMajor,
            std::uint32_t* kdMinor) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemVersionString(
            std::uint32_t which,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemVersionStringWide(
            std::uint32_t which,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetContextStackTrace(
            void* startContext,
            std::uint32_t startContextSize,
            debug_stack_frame* frames,
            std::uint32_t framesSize,
            void* frameContexts,
            std::uint32_t frameContextsSize,
            std::uint32_t frameContextsEntrySize,
            std::uint32_t* framesFilled) noexcept = 0;
        virtual std::int32_t __stdcall OutputContextStackTrace(
            std::uint32_t outputControl,
            debug_stack_frame* frames,
            std::uint32_t framesSize,
            void* frameContexts,
            std::uint32_t frameContextsSize,
            std::uint32_t frameContextsEntrySize,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetStoredEventInformation(
            std::uint32_t* type,
            std::uint32_t* processId,
            std::uint32_t* threadId,
            void* context,
            std::uint32_t contextSize,
            std::uint32_t* contextUsed,
            void* extraInformation,
            std::uint32_t extraInformationSize,
            std::uint32_t* extraInformationUsed) noexcept = 0;
        virtual std::int32_t __stdcall GetManagedStatus(
            std::uint32_t* flags,
            std::uint32_t whichString,
            char* string,
            std::uint32_t stringSize,
            std::uint32_t* stringNeeded) noexcept = 0;
        virtual std::int32_t __stdcall GetManagedStatusWide(
            std::uint32_t* flags,
            std::uint32_t whichString,
            wchar_t* string,
            std::uint32_t stringSize,
            std::uint32_t* stringNeeded) noexcept = 0;
        virtual std::int32_t __stdcall ResetManagedStatus(
            std::uint32_t flags) noexcept = 0;
    };

    struct IDebugControl5 : IDebugControl4
    {
        virtual std::int32_t __stdcall GetStackTraceEx(
            std::uint64_t frameOffset,
            std::uint64_t stackOffset,
            std::uint64_t instructionOffset,
            debug_stack_frame_ex* frames,
            std::uint32_t framesSize,
            std::uint32_t* framesFilled) noexcept = 0;
        virtual std::int32_t __stdcall OutputStackTraceEx(
            std::uint32_t outputControl,
            debug_stack_frame_ex* frames,
            std::uint32_t framesSize,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetContextStackTraceEx(
            void* startContext,
            std::uint32_t startContextSize,
            debug_stack_frame_ex* frames,
            std::uint32_t framesSize,
            void* frameContexts,
            std::uint32_t frameContextsSize,
            std::uint32_t frameContextsEntrySize,
            std::uint32_t* framesFilled) noexcept = 0;
        virtual std::int32_t __stdcall OutputContextStackTraceEx(
            std::uint32_t outputControl,
            debug_stack_frame_ex* frames,
            std::uint32_t framesSize,
            void* frameContexts,
            std::uint32_t frameContextsSize,
            std::uint32_t frameContextsEntrySize,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetBreakpointByGuid(
            guid* guid,
            IDebugBreakpoint3** bp) noexcept = 0;
    };

    struct IDebugControl6 : IDebugControl5
    {
        virtual std::int32_t __stdcall GetExecutionStatusEx(
            std::uint32_t* status) noexcept = 0;
        virtual std::int32_t __stdcall GetSynchronizationStatus(
            std::uint32_t* sendsAttempted,
            std::uint32_t* secondsSinceLastResponse) noexcept = 0;
    };

    struct IDebugControl7 : IDebugControl6
    {
        virtual std::int32_t __stdcall GetDebuggeeType2(
            std::uint32_t flags,
            std::uint32_t* targetClass,
            std::uint32_t* qualifier) noexcept = 0;
    };

    struct IDebugDataSpaces : IUnknown
    {
        virtual std::int32_t __stdcall ReadVirtual(
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteVirtual(
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall SearchVirtual(
            std::uint64_t offset,
            std::uint64_t length,
            void* pattern,
            std::uint32_t patternSize,
            std::uint32_t patternGranularity,
            std::uint64_t* matchOffset) noexcept = 0;
        virtual std::int32_t __stdcall ReadVirtualUncached(
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteVirtualUncached(
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall ReadPointersVirtual(
            std::uint32_t count,
            std::uint64_t offset,
            std::uint64_t* ptrs) noexcept = 0;
        virtual std::int32_t __stdcall WritePointersVirtual(
            std::uint32_t count,
            std::uint64_t offset,
            std::uint64_t* ptrs) noexcept = 0;
        virtual std::int32_t __stdcall ReadPhysical(
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WritePhysical(
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall ReadControl(
            std::uint32_t processor,
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteControl(
            std::uint32_t processor,
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall ReadIo(
            std::uint32_t interfaceType,
            std::uint32_t busNumber,
            std::uint32_t addressSpace,
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteIo(
            std::uint32_t interfaceType,
            std::uint32_t busNumber,
            std::uint32_t addressSpace,
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall ReadMsr(std::uint32_t msr, std::uint64_t* value) noexcept = 0;
        virtual std::int32_t __stdcall WriteMsr(std::uint32_t msr, std::uint64_t value) noexcept = 0;
        virtual std::int32_t __stdcall ReadBusData(
            std::uint32_t busDataType,
            std::uint32_t busNumber,
            std::uint32_t slotNumber,
            std::uint32_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteBusData(
            std::uint32_t busDataType,
            std::uint32_t busNumber,
            std::uint32_t slotNumber,
            std::uint32_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall CheckLowMemory() noexcept = 0;
        virtual std::int32_t __stdcall ReadDebuggerData(
            std::uint32_t index,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* dataSize) noexcept = 0;
        virtual std::int32_t __stdcall ReadProcessorSystemData(
            std::uint32_t processor,
            std::uint32_t index,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* dataSize) noexcept = 0;
    };

    struct IDebugDataSpaces2 : IDebugDataSpaces
    {
        virtual std::int32_t __stdcall VirtualToPhysical(
            std::uint64_t virtualAddress,
            std::uint64_t* physicalAddress) noexcept = 0;
        virtual std::int32_t __stdcall GetVirtualTranslationPhysicalOffsets(
            std::uint64_t virtualAddress,
            std::uint64_t* offsets,
            std::uint32_t offsetsSize,
            std::uint32_t* levels) noexcept = 0;
        virtual std::int32_t __stdcall ReadHandleData(
            std::uint64_t handle,
            std::uint32_t dataType,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* dataSize) noexcept = 0;
        virtual std::int32_t __stdcall FillVirtual(
            std::uint64_t start,
            std::uint32_t size,
            void* pattern,
            std::uint32_t patternSize,
            std::uint32_t* filled) noexcept = 0;
        virtual std::int32_t __stdcall FillPhysical(
            std::uint64_t start,
            std::uint32_t size,
            void* pattern,
            std::uint32_t patternSize,
            std::uint32_t* filled) noexcept = 0;
        virtual std::int32_t __stdcall QueryVirtual(std::uint64_t offset, memory_basic_information64* info) noexcept = 0;
    };

    struct IDebugDataSpaces3 : IDebugDataSpaces2
    {
        virtual std::int32_t __stdcall ReadImageNtHeaders(
            std::uint64_t imageBase,
            image_nt_headers64* headers) noexcept = 0;
        virtual std::int32_t __stdcall ReadTagged(
            guid* tag,
            std::uint32_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* totalSize) noexcept = 0;
        virtual std::int32_t __stdcall StartEnumTagged(std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall GetNextTagged(std::uint64_t handle, guid* tag, std::uint32_t* size) noexcept = 0;
        virtual std::int32_t __stdcall EndEnumTagged(std::uint64_t handle) noexcept = 0;
    };

    struct IDebugDataSpaces4 : IDebugDataSpaces3
    {
        virtual std::int32_t __stdcall GetOffsetInformation(
            std::uint32_t space,
            std::uint32_t which,
            std::uint64_t offset,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* infoSize) noexcept = 0;
        virtual std::int32_t __stdcall GetNextDifferentlyValidOffsetVirtual(
            std::uint64_t offset,
            std::uint64_t* nextOffset) noexcept = 0;
        virtual std::int32_t __stdcall GetValidRegionVirtual(
            std::uint64_t base,
            std::uint32_t size,
            std::uint64_t* validBase,
            std::uint32_t* validSize) noexcept = 0;
        virtual std::int32_t __stdcall SearchVirtual2(
            std::uint64_t offset,
            std::uint64_t length,
            std::uint32_t flags,
            void* pattern,
            std::uint32_t patternSize,
            std::uint32_t patternGranularity,
            std::uint64_t* matchOffset) noexcept = 0;
        virtual std::int32_t __stdcall ReadMultiByteStringVirtual(
            std::uint64_t offset,
            std::uint32_t maxBytes,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringBytes) noexcept = 0;
        virtual std::int32_t __stdcall ReadMultiByteStringVirtualWide(
            std::uint64_t offset,
            std::uint32_t maxBytes,
            std::uint32_t codePage,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringBytes) noexcept = 0;
        virtual std::int32_t __stdcall ReadUnicodeStringVirtual(
            std::uint64_t offset,
            std::uint32_t maxBytes,
            std::uint32_t codePage,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringBytes) noexcept = 0;
        virtual std::int32_t __stdcall ReadUnicodeStringVirtualWide(
            std::uint64_t offset,
            std::uint32_t maxBytes,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringBytes) noexcept = 0;
        virtual std::int32_t __stdcall ReadPhysical2(
            std::uint64_t offset,
            std::uint32_t flags,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WritePhysical2(
            std::uint64_t offset,
            std::uint32_t flags,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
    };

    struct IDebugEventCallbacks : IUnknown
    {
        virtual std::int32_t __stdcall GetInterestMask(std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall Breakpoint(IDebugBreakpoint* bp) noexcept = 0;
        virtual std::int32_t __stdcall Exception(exception_record64* exception, std::uint32_t firstChance) noexcept = 0;
        virtual std::int32_t __stdcall CreateThread(
            std::uint64_t handle,
            std::uint64_t dataOffset,
            std::uint64_t startOffset) noexcept = 0;
        virtual std::int32_t __stdcall ExitThread(std::uint32_t exitCode) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcess(
            std::uint64_t imageFileHandle,
            std::uint64_t handle,
            std::uint64_t baseOffset,
            std::uint32_t moduleSize,
            const char* moduleName,
            const char* imageName,
            std::uint32_t checkSum,
            std::uint32_t timeDateStamp,
            std::uint64_t initialThreadHandle,
            std::uint64_t threadDataOffset,
            std::uint64_t startOffset) noexcept = 0;
        virtual std::int32_t __stdcall ExitProcess(std::uint32_t exitCode) noexcept = 0;
        virtual std::int32_t __stdcall LoadModule(
            std::uint64_t imageFileHandle,
            std::uint64_t baseOffset,
            std::uint32_t moduleSize,
            const char* moduleName,
            const char* imageName,
            std::uint32_t checkSum,
            std::uint32_t timeDateStamp) noexcept = 0;
        virtual std::int32_t __stdcall UnloadModule(const char* imageBaseName, std::uint64_t baseOffset) noexcept = 0;
        virtual std::int32_t __stdcall SystemError(std::uint32_t error, std::uint32_t level) noexcept = 0;
        virtual std::int32_t __stdcall SessionStatus(std::uint32_t status) noexcept = 0;
        virtual std::int32_t __stdcall ChangeDebuggeeState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
        virtual std::int32_t __stdcall ChangeEngineState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
        virtual std::int32_t __stdcall ChangeSymbolState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
    };

    struct IDebugEventCallbacksWide : IUnknown
    {
        virtual std::int32_t __stdcall GetInterestMask(std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall Breakpoint(IDebugBreakpoint2* bp) noexcept = 0;
        virtual std::int32_t __stdcall Exception(exception_record64* exception, std::uint32_t firstChance) noexcept = 0;
        virtual std::int32_t __stdcall CreateThread(
            std::uint64_t handle,
            std::uint64_t dataOffset,
            std::uint64_t startOffset) noexcept = 0;
        virtual std::int32_t __stdcall ExitThread(std::uint32_t exitCode) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcess(
            std::uint64_t imageFileHandle,
            std::uint64_t handle,
            std::uint64_t baseOffset,
            std::uint32_t moduleSize,
            const wchar_t* moduleName,
            const wchar_t* imageName,
            std::uint32_t checkSum,
            std::uint32_t timeDateStamp,
            std::uint64_t initialThreadHandle,
            std::uint64_t threadDataOffset,
            std::uint64_t startOffset) noexcept = 0;
        virtual std::int32_t __stdcall ExitProcess(std::uint32_t exitCode) noexcept = 0;
        virtual std::int32_t __stdcall LoadModule(
            std::uint64_t imageFileHandle,
            std::uint64_t baseOffset,
            std::uint32_t moduleSize,
            const wchar_t* moduleName,
            const wchar_t* imageName,
            std::uint32_t checkSum,
            std::uint32_t timeDateStamp) noexcept = 0;
        virtual std::int32_t __stdcall UnloadModule(const wchar_t* imageBaseName, std::uint64_t baseOffset) noexcept = 0;
        virtual std::int32_t __stdcall SystemError(std::uint32_t error, std::uint32_t level) noexcept = 0;
        virtual std::int32_t __stdcall SessionStatus(std::uint32_t status) noexcept = 0;
        virtual std::int32_t __stdcall ChangeDebuggeeState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
        virtual std::int32_t __stdcall ChangeEngineState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
        virtual std::int32_t __stdcall ChangeSymbolState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
    };

    struct IDebugEventContextCallbacks : IUnknown
    {
        virtual std::int32_t __stdcall GetInterestMask(std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall Breakpoint(
            IDebugBreakpoint2* bp,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall Exception(
            exception_record64* exception,
            std::uint32_t firstChance,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall CreateThread(
            std::uint64_t handle,
            std::uint64_t dataOffset,
            std::uint64_t startOffset,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall ExitThread(
            std::uint32_t exitCode,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall CreateProcess(
            std::uint64_t imageFileHandle,
            std::uint64_t handle,
            std::uint64_t baseOffset,
            std::uint32_t moduleSize,
            const wchar_t* moduleName,
            const wchar_t* imageName,
            std::uint32_t checkSum,
            std::uint32_t timeDateStamp,
            std::uint64_t initialThreadHandle,
            std::uint64_t threadDataOffset,
            std::uint64_t startOffset,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall ExitProcess(
            std::uint32_t exitCode,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall LoadModule(
            std::uint64_t imageFileHandle,
            std::uint64_t baseOffset,
            std::uint32_t moduleSize,
            const wchar_t* moduleName,
            const wchar_t* imageName,
            std::uint32_t checkSum,
            std::uint32_t timeDateStamp,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall UnloadModule(
            const wchar_t* imageBaseName,
            std::uint64_t baseOffset,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall SystemError(
            std::uint32_t error,
            std::uint32_t level,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall SessionStatus(std::uint32_t status) noexcept = 0;
        virtual std::int32_t __stdcall ChangeDebuggeeState(
            std::uint32_t flags,
            std::uint64_t argument,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall ChangeEngineState(
            std::uint32_t flags,
            std::uint64_t argument,
            void* context,
            std::uint32_t contextSize) noexcept = 0;
        virtual std::int32_t __stdcall ChangeSymbolState(std::uint32_t flags, std::uint64_t argument) noexcept = 0;
    };

    struct IDebugInputCallbacks : IUnknown
    {
        virtual std::int32_t __stdcall StartInput(std::uint32_t bufferSize) noexcept = 0;
        virtual std::int32_t __stdcall EndInput() noexcept = 0;
    };

    struct IDebugOutputCallbacks : IUnknown
    {
        virtual std::int32_t __stdcall Output(std::uint32_t mask, const char* text) noexcept = 0;
    };

    struct IDebugOutputCallbacks2 : IDebugOutputCallbacks
    {
        virtual std::int32_t __stdcall GetInterestMask(std::uint32_t* mask) noexcept = 0;
        virtual std::int32_t __stdcall Output2(
            std::uint32_t which,
            std::uint32_t flags,
            std::uint64_t arg,
            const wchar_t* text) noexcept = 0;
    };

    struct IDebugOutputCallbacksWide : IUnknown
    {
        virtual std::int32_t __stdcall Output(std::uint32_t mask, const wchar_t* text) noexcept = 0;
    };

    struct IDebugRegisters : IUnknown
    {
        virtual std::int32_t __stdcall GetNumberRegisters(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetDescription(
            std::uint32_t register,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            debug_register_description* desc) noexcept = 0;
        virtual std::int32_t __stdcall GetIndexByName(const char* name, std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall GetValue(std::uint32_t register, debug_value* value) noexcept = 0;
        virtual std::int32_t __stdcall SetValue(std::uint32_t register, debug_value* value) noexcept = 0;
        virtual std::int32_t __stdcall GetValues(
            std::uint32_t count,
            std::uint32_t* indices,
            std::uint32_t start,
            debug_value* values) noexcept = 0;
        virtual std::int32_t __stdcall SetValues(
            std::uint32_t count,
            std::uint32_t* indices,
            std::uint32_t start,
            debug_value* values) noexcept = 0;
        virtual std::int32_t __stdcall OutputRegisters(std::uint32_t outputControl, std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetInstructionOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetStackOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetFrameOffset(std::uint64_t* offset) noexcept = 0;
    };

    struct IDebugRegisters2 : IDebugRegisters
    {
        virtual std::int32_t __stdcall GetDescriptionWide(
            std::uint32_t register,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            debug_register_description* desc) noexcept = 0;
        virtual std::int32_t __stdcall GetIndexByNameWide(const wchar_t* name, std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberPseudoRegisters(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetPseudoDescription(
            std::uint32_t register,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* typeModule,
            std::uint32_t* typeId) noexcept = 0;
        virtual std::int32_t __stdcall GetPseudoDescriptionWide(
            std::uint32_t register,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* typeModule,
            std::uint32_t* typeId) noexcept = 0;
        virtual std::int32_t __stdcall GetPseudoIndexByName(const char* name, std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall GetPseudoIndexByNameWide(const wchar_t* name, std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall GetPseudoValues(
            std::uint32_t source,
            std::uint32_t count,
            std::uint32_t* indices,
            std::uint32_t start,
            debug_value* values) noexcept = 0;
        virtual std::int32_t __stdcall SetPseudoValues(
            std::uint32_t source,
            std::uint32_t count,
            std::uint32_t* indices,
            std::uint32_t start,
            debug_value* values) noexcept = 0;
        virtual std::int32_t __stdcall GetValues2(
            std::uint32_t source,
            std::uint32_t count,
            std::uint32_t* indices,
            std::uint32_t start,
            debug_value* values) noexcept = 0;
        virtual std::int32_t __stdcall SetValues2(
            std::uint32_t source,
            std::uint32_t count,
            std::uint32_t* indices,
            std::uint32_t start,
            debug_value* values) noexcept = 0;
        virtual std::int32_t __stdcall OutputRegisters2(
            std::uint32_t outputControl,
            std::uint32_t source,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetInstructionOffset2(std::uint32_t source, std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetStackOffset2(std::uint32_t source, std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetFrameOffset2(std::uint32_t source, std::uint64_t* offset) noexcept = 0;
    };

    struct IDebugSymbolGroup : IUnknown
    {
        virtual std::int32_t __stdcall GetNumberSymbols(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall AddSymbol(const char* name, std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall RemoveSymbolByName(const char* name) noexcept = 0;
        virtual std::int32_t __stdcall RemoveSymbolByIndex(std::uint32_t index) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolName(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolParameters(
            std::uint32_t start,
            std::uint32_t count,
            debug_symbol_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall ExpandSymbol(std::uint32_t index, bool_t expand) noexcept = 0;
        virtual std::int32_t __stdcall OutputSymbols(
            std::uint32_t outputControl,
            std::uint32_t flags,
            std::uint32_t start,
            std::uint32_t count) noexcept = 0;
        virtual std::int32_t __stdcall WriteSymbol(std::uint32_t index, const char* value) noexcept = 0;
        virtual std::int32_t __stdcall OutputAsType(std::uint32_t index, const char* type) noexcept = 0;
    };

    struct IDebugSymbolGroup2 : IDebugSymbolGroup
    {
        virtual std::int32_t __stdcall AddSymbolWide(const wchar_t* name, std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall RemoveSymbolByNameWide(const wchar_t* name) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolNameWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall WriteSymbolWide(std::uint32_t index, const wchar_t* value) noexcept = 0;
        virtual std::int32_t __stdcall OutputAsTypeWide(std::uint32_t index, const wchar_t* type) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolTypeName(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolTypeNameWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolSize(std::uint32_t index, std::uint32_t* size) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolOffset(std::uint32_t index, std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolRegister(std::uint32_t index, std::uint32_t* registerIndex) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolValueText(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolValueTextWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryInformation(
            std::uint32_t index,
            debug_symbol_entry* entry) noexcept = 0;
    };

    struct IDebugSymbols : IUnknown
    {
        virtual std::int32_t __stdcall GetSymbolOptions(std::uint32_t* options) noexcept = 0;
        virtual std::int32_t __stdcall AddSymbolOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall RemoveSymbolOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall SetSymbolOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall GetNameByOffset(
            std::uint64_t offset,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetByName(const char* symbol, std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetNearNameByOffset(
            std::uint64_t offset,
            std::int32_t delta,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetLineByOffset(
            std::uint64_t offset,
            std::uint32_t* line,
            char* fileBuffer,
            std::uint32_t fileBufferSize,
            std::uint32_t* fileSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetByLine(
            std::uint32_t line,
            const char* file,
            std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberModules(std::uint32_t* loaded, std::uint32_t* unloaded) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByIndex(std::uint32_t index, std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByModuleName(
            const char* name,
            std::uint32_t startIndex,
            std::uint32_t* index,
            std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByOffset(
            std::uint64_t offset,
            std::uint32_t startIndex,
            std::uint32_t* index,
            std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleNames(
            std::uint32_t index,
            std::uint64_t base,
            char* imageNameBuffer,
            std::uint32_t imageNameBufferSize,
            std::uint32_t* imageNameSize,
            char* moduleNameBuffer,
            std::uint32_t moduleNameBufferSize,
            std::uint32_t* moduleNameSize,
            char* loadedImageNameBuffer,
            std::uint32_t loadedImageNameBufferSize,
            std::uint32_t* loadedImageNameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleParameters(
            std::uint32_t count,
            std::uint64_t* bases,
            std::uint32_t start,
            debug_module_parameters* params) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolModule(const char* symbol, std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetTypeName(
            std::uint64_t module,
            std::uint32_t typeId,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetTypeId(
            std::uint64_t module,
            const char* name,
            std::uint32_t* typeId) noexcept = 0;
        virtual std::int32_t __stdcall GetTypeSize(
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint32_t* size) noexcept = 0;
        virtual std::int32_t __stdcall GetFieldOffset(
            std::uint64_t module,
            std::uint32_t typeId,
            const char* field,
            std::uint32_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolTypeId(
            const char* symbol,
            std::uint32_t* typeId,
            std::uint64_t* module) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetTypeId(
            std::uint64_t offset,
            std::uint32_t* typeId,
            std::uint64_t* module) noexcept = 0;
        virtual std::int32_t __stdcall ReadTypedDataVirtual(
            std::uint64_t offset,
            std::uint64_t module,
            std::uint32_t typeId,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteTypedDataVirtual(
            std::uint64_t offset,
            std::uint64_t module,
            std::uint32_t typeId,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall OutputTypedDataVirtual(
            std::uint32_t outputControl,
            std::uint64_t offset,
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall ReadTypedDataPhysical(
            std::uint64_t offset,
            std::uint64_t module,
            std::uint32_t typeId,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesRead) noexcept = 0;
        virtual std::int32_t __stdcall WriteTypedDataPhysical(
            std::uint64_t offset,
            std::uint64_t module,
            std::uint32_t typeId,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bytesWritten) noexcept = 0;
        virtual std::int32_t __stdcall OutputTypedDataPhysical(
            std::uint32_t outputControl,
            std::uint64_t offset,
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall GetScope(
            std::uint64_t* instructionOffset,
            debug_stack_frame* scopeFrame,
            void* scopeContext,
            std::uint32_t scopeContextSize) noexcept = 0;
        virtual std::int32_t __stdcall SetScope(
            std::uint64_t instructionOffset,
            debug_stack_frame* scopeFrame,
            void* scopeContext,
            std::uint32_t scopeContextSize) noexcept = 0;
        virtual std::int32_t __stdcall ResetScope() noexcept = 0;
        virtual std::int32_t __stdcall GetScopeSymbolGroup(
            std::uint32_t flags,
            IDebugSymbolGroup* update,
            IDebugSymbolGroup** symbols) noexcept = 0;
        virtual std::int32_t __stdcall CreateSymbolGroup(IDebugSymbolGroup** group) noexcept = 0;
        virtual std::int32_t __stdcall StartSymbolMatch(const char* pattern, std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall GetNextSymbolMatch(
            std::uint64_t handle,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* matchSize,
            std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall EndSymbolMatch(std::uint64_t handle) noexcept = 0;
        virtual std::int32_t __stdcall Reload(const char* module) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolPath(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* pathSize) noexcept = 0;
        virtual std::int32_t __stdcall SetSymbolPath(const char* path) noexcept = 0;
        virtual std::int32_t __stdcall AppendSymbolPath(const char* addition) noexcept = 0;
        virtual std::int32_t __stdcall GetImagePath(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* pathSize) noexcept = 0;
        virtual std::int32_t __stdcall SetImagePath(const char* path) noexcept = 0;
        virtual std::int32_t __stdcall AppendImagePath(const char* addition) noexcept = 0;
        virtual std::int32_t __stdcall GetSourcePath(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* pathSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourcePathElement(
            std::uint32_t index,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* elementSize) noexcept = 0;
        virtual std::int32_t __stdcall SetSourcePath(const char* path) noexcept = 0;
        virtual std::int32_t __stdcall AppendSourcePath(const char* addition) noexcept = 0;
        virtual std::int32_t __stdcall FindSourceFile(
            std::uint32_t startElement,
            const char* file,
            std::uint32_t flags,
            std::uint32_t* foundElement,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* foundSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceFileLineOffsets(
            const char* file,
            std::uint64_t* buffer,
            std::uint32_t bufferLines,
            std::uint32_t* fileLines) noexcept = 0;
    };

    struct IDebugSymbols2 : IDebugSymbols
    {
        virtual std::int32_t __stdcall GetModuleVersionInformation(
            std::uint32_t index,
            std::uint64_t base,
            const char* item,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* verInfoSize) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleNameString(
            std::uint32_t which,
            std::uint32_t index,
            std::uint64_t base,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetConstantName(
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint64_t value,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetFieldName(
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint32_t fieldIndex,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetTypeOptions(std::uint32_t* options) noexcept = 0;
        virtual std::int32_t __stdcall AddTypeOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall RemoveTypeOptions(std::uint32_t options) noexcept = 0;
        virtual std::int32_t __stdcall SetTypeOptions(std::uint32_t options) noexcept = 0;
    };

    struct IDebugSymbols3 : IDebugSymbols2
    {
        virtual std::int32_t __stdcall GetNameByOffsetWide(
            std::uint64_t offset,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetByNameWide(const wchar_t* symbol, std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetNearNameByOffsetWide(
            std::uint64_t offset,
            std::int32_t delta,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetLineByOffsetWide(
            std::uint64_t offset,
            std::uint32_t* line,
            wchar_t* fileBuffer,
            std::uint32_t fileBufferSize,
            std::uint32_t* fileSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetOffsetByLineWide(
            std::uint32_t line,
            const wchar_t* file,
            std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByModuleNameWide(
            const wchar_t* name,
            std::uint32_t startIndex,
            std::uint32_t* index,
            std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolModuleWide(const wchar_t* symbol, std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetTypeNameWide(
            std::uint64_t module,
            std::uint32_t typeId,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetTypeIdWide(
            std::uint64_t module,
            const wchar_t* name,
            std::uint32_t* typeId) noexcept = 0;
        virtual std::int32_t __stdcall GetFieldOffsetWide(
            std::uint64_t module,
            std::uint32_t typeId,
            const wchar_t* field,
            std::uint32_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolTypeIdWide(
            const wchar_t* symbol,
            std::uint32_t* typeId,
            std::uint64_t* module) noexcept = 0;
        virtual std::int32_t __stdcall GetScopeSymbolGroup2(
            std::uint32_t flags,
            IDebugSymbolGroup2* update,
            IDebugSymbolGroup2** symbols) noexcept = 0;
        virtual std::int32_t __stdcall CreateSymbolGroup2(IDebugSymbolGroup2** group) noexcept = 0;
        virtual std::int32_t __stdcall StartSymbolMatchWide(const wchar_t* pattern, std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall GetNextSymbolMatchWide(
            std::uint64_t handle,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* matchSize,
            std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall ReloadWide(const wchar_t* module) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolPathWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* pathSize) noexcept = 0;
        virtual std::int32_t __stdcall SetSymbolPathWide(const wchar_t* path) noexcept = 0;
        virtual std::int32_t __stdcall AppendSymbolPathWide(const wchar_t* addition) noexcept = 0;
        virtual std::int32_t __stdcall GetImagePathWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* pathSize) noexcept = 0;
        virtual std::int32_t __stdcall SetImagePathWide(const wchar_t* path) noexcept = 0;
        virtual std::int32_t __stdcall AppendImagePathWide(const wchar_t* addition) noexcept = 0;
        virtual std::int32_t __stdcall GetSourcePathWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* pathSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourcePathElementWide(
            std::uint32_t index,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* elementSize) noexcept = 0;
        virtual std::int32_t __stdcall SetSourcePathWide(const wchar_t* path) noexcept = 0;
        virtual std::int32_t __stdcall AppendSourcePathWide(const wchar_t* addition) noexcept = 0;
        virtual std::int32_t __stdcall FindSourceFileWide(
            std::uint32_t startElement,
            const wchar_t* file,
            std::uint32_t flags,
            std::uint32_t* foundElement,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* foundSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceFileLineOffsetsWide(
            const wchar_t* file,
            std::uint64_t* buffer,
            std::uint32_t bufferLines,
            std::uint32_t* fileLines) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleVersionInformationWide(
            std::uint32_t index,
            std::uint64_t base,
            const wchar_t* item,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* verInfoSize) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleNameStringWide(
            std::uint32_t which,
            std::uint32_t index,
            std::uint64_t base,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetConstantNameWide(
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint64_t value,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall GetFieldNameWide(
            std::uint64_t module,
            std::uint32_t typeId,
            std::uint32_t fieldIndex,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize) noexcept = 0;
        virtual std::int32_t __stdcall IsManagedModule(std::uint32_t index, std::uint64_t base) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByModuleName2(
            const char* name,
            std::uint32_t startIndex,
            std::uint32_t flags,
            std::uint32_t* index,
            std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByModuleName2Wide(
            const wchar_t* name,
            std::uint32_t startIndex,
            std::uint32_t flags,
            std::uint32_t* index,
            std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall GetModuleByOffset2(
            std::uint64_t offset,
            std::uint32_t startIndex,
            std::uint32_t flags,
            std::uint32_t* index,
            std::uint64_t* base) noexcept = 0;
        virtual std::int32_t __stdcall AddSyntheticModule(
            std::uint64_t base,
            std::uint32_t size,
            const char* imagePath,
            const char* moduleName,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall AddSyntheticModuleWide(
            std::uint64_t base,
            std::uint32_t size,
            const wchar_t* imagePath,
            const wchar_t* moduleName,
            std::uint32_t flags) noexcept = 0;
        virtual std::int32_t __stdcall RemoveSyntheticModule(std::uint64_t base) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentScopeFrameIndex(std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall SetScopeFrameByIndex(std::uint32_t index) noexcept = 0;
        virtual std::int32_t __stdcall SetScopeFromJitDebugInfo(
            std::uint32_t outputControl,
            std::uint64_t infoOffset) noexcept = 0;
        virtual std::int32_t __stdcall SetScopeFromStoredEvent() noexcept = 0;
        virtual std::int32_t __stdcall OutputSymbolByOffset(
            std::uint32_t outputControl,
            std::uint32_t flags,
            std::uint64_t offset) noexcept = 0;
        virtual std::int32_t __stdcall GetFunctionEntryByOffset(
            std::uint64_t offset,
            std::uint32_t flags,
            void* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* bufferNeeded) noexcept = 0;
        virtual std::int32_t __stdcall GetFieldTypeAndOffset(
            std::uint64_t module,
            std::uint32_t containerTypeId,
            const char* field,
            std::uint32_t* fieldTypeId,
            std::uint32_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetFieldTypeAndOffsetWide(
            std::uint64_t module,
            std::uint32_t containerTypeId,
            const wchar_t* field,
            std::uint32_t* fieldTypeId,
            std::uint32_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall AddSyntheticSymbol(
            std::uint64_t offset,
            std::uint32_t size,
            const char* name,
            std::uint32_t flags,
            debug_module_and_id* id) noexcept = 0;
        virtual std::int32_t __stdcall AddSyntheticSymbolWide(
            std::uint64_t offset,
            std::uint32_t size,
            const wchar_t* name,
            std::uint32_t flags,
            debug_module_and_id* id) noexcept = 0;
        virtual std::int32_t __stdcall RemoveSyntheticSymbol(debug_module_and_id* id) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntriesByOffset(
            std::uint64_t offset,
            std::uint32_t flags,
            debug_module_and_id* ids,
            std::uint64_t* displacements,
            std::uint32_t idsCount,
            std::uint32_t* entries) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntriesByName(
            const char* symbol,
            std::uint32_t flags,
            debug_module_and_id* ids,
            std::uint32_t idsCount,
            std::uint32_t* entries) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntriesByNameWide(
            const wchar_t* symbol,
            std::uint32_t flags,
            debug_module_and_id* ids,
            std::uint32_t idsCount,
            std::uint32_t* entries) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryByToken(
            std::uint64_t moduleBase,
            std::uint32_t token,
            debug_module_and_id* id) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryInformation(
            debug_module_and_id* id,
            debug_symbol_entry* info) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryString(
            debug_module_and_id* id,
            std::uint32_t which,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryStringWide(
            debug_module_and_id* id,
            std::uint32_t which,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryOffsetRegions(
            debug_module_and_id* id,
            std::uint32_t flags,
            debug_offset_region* regions,
            std::uint32_t regionsCount,
            std::uint32_t* regionsAvail) noexcept = 0;
        virtual std::int32_t __stdcall GetSymbolEntryBySymbolEntry(
            debug_module_and_id* fromId,
            std::uint32_t flags,
            debug_module_and_id* toId) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntriesByOffset(
            std::uint64_t offset,
            std::uint32_t flags,
            debug_symbol_source_entry* entries,
            std::uint32_t entriesCount,
            std::uint32_t* entriesAvail) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntriesByLine(
            std::uint32_t line,
            const char* file,
            std::uint32_t flags,
            debug_symbol_source_entry* entries,
            std::uint32_t entriesCount,
            std::uint32_t* entriesAvail) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntriesByLineWide(
            std::uint32_t line,
            const wchar_t* file,
            std::uint32_t flags,
            debug_symbol_source_entry* entries,
            std::uint32_t entriesCount,
            std::uint32_t* entriesAvail) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntryString(
            debug_symbol_source_entry* entry,
            std::uint32_t which,
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntryStringWide(
            debug_symbol_source_entry* entry,
            std::uint32_t which,
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* stringSize) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntryOffsetRegions(
            debug_symbol_source_entry* entry,
            std::uint32_t flags,
            debug_offset_region* regions,
            std::uint32_t regionsCount,
            std::uint32_t* regionsAvail) noexcept = 0;
        virtual std::int32_t __stdcall GetSourceEntryBySourceEntry(
            debug_symbol_source_entry* fromEntry,
            std::uint32_t flags,
            debug_symbol_source_entry* toEntry) noexcept = 0;
    };

    struct IDebugSymbols4 : IDebugSymbols3
    {
        virtual std::int32_t __stdcall GetScopeEx(
            std::uint64_t* instructionOffset,
            debug_stack_frame_ex* scopeFrame,
            void* scopeContext,
            std::uint32_t scopeContextSize) noexcept = 0;
        virtual std::int32_t __stdcall SetScopeEx(
            std::uint64_t instructionOffset,
            debug_stack_frame_ex* scopeFrame,
            void* scopeContext,
            std::uint32_t scopeContextSize) noexcept = 0;
        virtual std::int32_t __stdcall GetNameByInlineContext(
            std::uint64_t offset,
            std::uint32_t inlineContext,
            char* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetNameByInlineContextWide(
            std::uint64_t offset,
            std::uint32_t inlineContext,
            wchar_t* nameBuffer,
            std::uint32_t nameBufferSize,
            std::uint32_t* nameSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetLineByInlineContext(
            std::uint64_t offset,
            std::uint32_t inlineContext,
            std::uint32_t* line,
            char* fileBuffer,
            std::uint32_t fileBufferSize,
            std::uint32_t* fileSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall GetLineByInlineContextWide(
            std::uint64_t offset,
            std::uint32_t inlineContext,
            std::uint32_t* line,
            wchar_t* fileBuffer,
            std::uint32_t fileBufferSize,
            std::uint32_t* fileSize,
            std::uint64_t* displacement) noexcept = 0;
        virtual std::int32_t __stdcall OutputSymbolByInlineContext(
            std::uint32_t outputControl,
            std::uint32_t flags,
            std::uint64_t offset,
            std::uint32_t inlineContext) noexcept = 0;
    };

    struct IDebugSymbols5 : IDebugSymbols4
    {
        virtual std::int32_t __stdcall GetCurrentScopeFrameIndexEx(
            std::uint32_t flags,
            std::uint32_t* index) noexcept = 0;
        virtual std::int32_t __stdcall SetScopeFrameByIndexEx(std::uint32_t flags, std::uint32_t index) noexcept = 0;
    };

    struct IDebugSystemObjects : IUnknown
    {
        virtual std::int32_t __stdcall GetEventThread(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetEventProcess(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentThreadId(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall SetCurrentThreadId(std::uint32_t id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentProcessId(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall SetCurrentProcessId(std::uint32_t id) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberThreads(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetTotalNumberThreads(
            std::uint32_t* total,
            std::uint32_t* largestProcess) noexcept = 0;
        virtual std::int32_t __stdcall GetThreadIdsByIndex(
            std::uint32_t start,
            std::uint32_t count,
            std::uint32_t* ids,
            std::uint32_t* sysIds) noexcept = 0;
        virtual std::int32_t __stdcall GetThreadIdByProcessor(std::uint32_t processor, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentThreadDataOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetThreadIdByDataOffset(std::uint64_t offset, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentThreadTeb(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetThreadIdByTeb(std::uint64_t offset, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentThreadSystemId(std::uint32_t* sysId) noexcept = 0;
        virtual std::int32_t __stdcall GetThreadIdBySystemId(std::uint32_t sysId, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentThreadHandle(std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall GetThreadIdByHandle(std::uint64_t handle, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberProcesses(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessIdsByIndex(
            std::uint32_t start,
            std::uint32_t count,
            std::uint32_t* ids,
            std::uint32_t* sysIds) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentProcessDataOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessIdByDataOffset(std::uint64_t offset, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentProcessPeb(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessIdByPeb(std::uint64_t offset, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentProcessSystemId(std::uint32_t* sysId) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessIdBySystemId(std::uint32_t sysId, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentProcessHandle(std::uint64_t* handle) noexcept = 0;
        virtual std::int32_t __stdcall GetProcessIdByHandle(std::uint64_t handle, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentProcessExecutableName(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* exeSize) noexcept = 0;
    };

    struct IDebugSystemObjects2 : IDebugSystemObjects
    {
        virtual std::int32_t __stdcall GetCurrentProcessUpTime(std::uint32_t* upTime) noexcept = 0;
        virtual std::int32_t __stdcall GetImplicitThreadDataOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall SetImplicitThreadDataOffset(std::uint64_t offset) noexcept = 0;
        virtual std::int32_t __stdcall GetImplicitProcessDataOffset(std::uint64_t* offset) noexcept = 0;
        virtual std::int32_t __stdcall SetImplicitProcessDataOffset(std::uint64_t offset) noexcept = 0;
    };

    struct IDebugSystemObjects3 : IDebugSystemObjects2
    {
        virtual std::int32_t __stdcall GetEventSystem(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentSystemId(std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall SetCurrentSystemId(std::uint32_t id) noexcept = 0;
        virtual std::int32_t __stdcall GetNumberSystems(std::uint32_t* number) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemIdsByIndex(
            std::uint32_t start,
            std::uint32_t count,
            std::uint32_t* ids) noexcept = 0;
        virtual std::int32_t __stdcall GetTotalNumberThreadsAndProcesses(
            std::uint32_t* totalThreads,
            std::uint32_t* totalProcesses,
            std::uint32_t* largestProcessThreads,
            std::uint32_t* largestSystemThreads,
            std::uint32_t* largestSystemProcesses) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentSystemServer(std::uint64_t* server) noexcept = 0;
        virtual std::int32_t __stdcall GetSystemByServer(std::uint64_t server, std::uint32_t* id) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentSystemServerName(
            char* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
    };

    struct IDebugSystemObjects4 : IDebugSystemObjects3
    {
        virtual std::int32_t __stdcall GetCurrentProcessExecutableNameWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* exeSize) noexcept = 0;
        virtual std::int32_t __stdcall GetCurrentSystemServerNameWide(
            wchar_t* buffer,
            std::uint32_t bufferSize,
            std::uint32_t* nameSize) noexcept = 0;
    };
}
}
