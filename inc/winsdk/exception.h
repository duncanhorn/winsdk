#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Forward declarations
    struct exception_pointers;

    // Type Definitions
    using vectored_exception_handler = std::int32_t __stdcall(exception_pointers* exceptionInfo);
    using top_level_exception_filter = std::int32_t __stdcall(exception_pointers* exceptionInfo);

    // Constants
    constexpr std::uint32_t exception_noncontinuable = 0x1;
    constexpr std::uint32_t exception_unwinding = 0x2;
    constexpr std::uint32_t exception_exit_unwind = 0x4;
    constexpr std::uint32_t exception_stack_invalid = 0x8;
    constexpr std::uint32_t exception_nested_call = 0x10;
    constexpr std::uint32_t exception_target_unwind = 0x20;
    constexpr std::uint32_t exception_collided_unwind = 0x40;
    constexpr std::uint32_t exception_unwind = exception_unwinding | exception_exit_unwind | exception_target_unwind | exception_collided_unwind;

    constexpr std::size_t exception_maximum_parameters = 15;

#if defined(_M_ARM)
    constexpr std::size_t arm_max_breakpoints = 8;
    constexpr std::size_t arm_max_watchpoints = 1;
#elif defined(_M_IX86)
    constexpr std::size_t size_of_80387_registers = 80;
    constexpr std::size_t maximum_supported_extension = 512;
#endif

    // Structures
    struct exception_record
    {
        std::uint32_t exception_code;
        std::uint32_t exception_flags;
        exception_record* exception_record;
        void* exception_address;
        std::uint32_t number_of_parameters;
        std::uintptr_t exception_information[exception_maximum_parameters];
    };

    struct exception_record32
    {
        std::uint32_t exception_code;
        std::uint32_t exception_flags;
        std::uint32_t exception_record;
        std::uint32_t exception_address;
        std::uint32_t number_of_parameters;
        std::uint32_t exception_information[exception_maximum_parameters];
    };

    struct exception_record64
    {
        std::uint32_t exception_code;
        std::uint32_t exception_flags;
        std::uint64_t exception_record;
        std::uint64_t exception_address;
        std::uint32_t number_of_parameters;
        std::uint32_t unused_alignment;
        std::uint64_t exception_information[exception_maximum_parameters];
    };

    struct [[alignas(16)]] m128_aligned
    {
        std::uint64_t low;
        std::int64_t high;
    };

    struct [[alignas(16)]] xsave_format
    {
        std::uint16_t control_word;
        std::uint16_t status_word;
        std::uint8_t tag_word;
        std::uint8_t reserved1;
        std::uint16_t error_opcode;
        std::uint32_t error_offset;
        std::uint16_t error_selector;
        std::uint16_t reserved2;
        std::uint32_t data_offset;
        std::uint16_t data_selector;
        std::uint16_t reserved3;
        std::uint32_t mx_csr;
        std::uint32_t mx_csr_mask;
        m128_aligned float_registers[8];

#if defined(_WIN64)
        m128_aligned xmm_registers[16];
        std::uint8_t reserved4[96];
#else
        m128_aligned xmm_registers[8];
        std::uint8_t reserved4[224];
#endif
    };

#if defined(_M_AMD64)
    struct [[alignas(16)]] context
    {
        std::uint64_t p1_home;
        std::uint64_t p2_home;
        std::uint64_t p3_home;
        std::uint64_t p4_home;
        std::uint64_t p5_home;
        std::uint64_t p6_home;

        std::uint32_t context_flags;
        std::uint32_t mx_csr;

        std::uint16_t seg_cs;
        std::uint16_t seg_ds;
        std::uint16_t seg_es;
        std::uint16_t seg_fs;
        std::uint16_t seg_gs;
        std::uint16_t seg_ss;
        std::uint32_t e_flags;

        std::uint64_t dr0;
        std::uint64_t dr1;
        std::uint64_t dr2;
        std::uint64_t dr3;
        std::uint64_t dr6;
        std::uint64_t dr7;

        std::uint64_t rax;
        std::uint64_t rcx;
        std::uint64_t rdx;
        std::uint64_t rbx;
        std::uint64_t rsp;
        std::uint64_t rbp;
        std::uint64_t rsi;
        std::uint64_t rdi;
        std::uint64_t r8;
        std::uint64_t r9;
        std::uint64_t r10;
        std::uint64_t r11;
        std::uint64_t r12;
        std::uint64_t r13;
        std::uint64_t r14;
        std::uint64_t r15;

        std::uint64_t rip;

        union
        {
            xsave_format flt_save;
            struct
            {
                m128_aligned header[2];
                m128_aligned legacy[8];
                m128_aligned xmm0;
                m128_aligned xmm1;
                m128_aligned xmm2;
                m128_aligned xmm3;
                m128_aligned xmm4;
                m128_aligned xmm5;
                m128_aligned xmm6;
                m128_aligned xmm7;
                m128_aligned xmm8;
                m128_aligned xmm9;
                m128_aligned xmm10;
                m128_aligned xmm11;
                m128_aligned xmm12;
                m128_aligned xmm13;
                m128_aligned xmm14;
                m128_aligned xmm15;
            } registers;
        } fp_state;

        m128_aligned vector_register[26];
        std::uint64_t vector_control;

        std::uint64_t debug_control;
        std::uint64_t last_branch_to_rip;
        std::uint64_t last_branch_from_rip;
        std::uint64_t last_exception_to_rip;
        std::uint64_t last_exception_from_rip;
    };
#elif defined(_M_ARM)
    typedef struct neon128
    {
        std::uint64_t low;
        std::int64_t high;
    };

    struct [[alignas(8)]] context
    {
        std::uint32_t context_flags;

        std::uint32_t r0;
        std::uint32_t r1;
        std::uint32_t r2;
        std::uint32_t r3;
        std::uint32_t r4;
        std::uint32_t r5;
        std::uint32_t r6;
        std::uint32_t r7;
        std::uint32_t r8;
        std::uint32_t r9;
        std::uint32_t r10;
        std::uint32_t r11;
        std::uint32_t r12;

        std::uint32_t sp;
        std::uint32_t lr;
        std::uint32_t pc;
        std::uint32_t cpsr;

        std::uint32_t fpscr;
        std::uint32_t padding;
        union
        {
            neon128 q[16];
            std::uint64_t d[32];
            std::uint32_t s[32];
        } fp;

        std::uint32_t bvr[arm_max_breakpoints];
        std::uint32_t bcr[arm_max_breakpoints];
        std::uint32_t wvr[arm_max_watchpoints];
        std::uint32_t wcr[arm_max_watchpoints];

        std::uint32_t padding2[2];
    };
#elif defined(_M_IX86)
    struct floating_save_area
    {
        std::uint32_t control_word;
        std::uint32_t status_word;
        std::uint32_t tag_word;
        std::uint32_t error_offset;
        std::uint32_t error_selector;
        std::uint32_t data_offset;
        std::uint32_t data_selector;
        std::uint8_t register_area[size_of_80387_registers];
        std::uint32_t spare0;
    };

    struct context
    {
        std::uint32_t context_flags;

        std::uint32_t dr0;
        std::uint32_t dr1;
        std::uint32_t dr2;
        std::uint32_t dr3;
        std::uint32_t dr6;
        std::uint32_t dr7;

        floating_save_area float_save;

        std::uint32_t seg_gs;
        std::uint32_t seg_fs;
        std::uint32_t seg_es;
        std::uint32_t seg_ds;

        std::uint32_t edi;
        std::uint32_t esi;
        std::uint32_t ebx;
        std::uint32_t edx;
        std::uint32_t ecx;
        std::uint32_t eax;

        std::uint32_t ebp;
        std::uint32_t eip;
        std::uint32_t seg_cs;
        std::uint32_t e_flags;
        std::uint32_t esp;
        std::uint32_t seg_ss;

        std::uint8_t extended_registers[maximum_supported_extension];
    };
#else
#error Unknown Architecture
#endif

    struct exception_pointers
    {
        exception_record* exception_record;
        context* context_record;
    };

    // Functions
    __declspec(dllimport)
    [[noreturn]] void __stdcall RtlRaiseException(exception_record* exceptionRecord);

    __declspec(dllimport)
    [[noreturn]] void __stdcall RaiseException(
        std::uint32_t exceptionCode,
        std::uint32_t exceptionFlags,
        std::uint32_t numberOfArguments,
        const std::uintptr_t* arguments);

    __declspec(dllimport)
    [[noreturn]] void __stdcall RaiseFailFastException(
        exception_record* exceptionRecord,
        context* contextRecord,
        std::uint32_t flags);

    __declspec(dllimport)
    void* __stdcall AddVectoredExceptionHandler(std::uint32_t first, vectored_exception_handler* handler);

    __declspec(dllimport)
    std::uint32_t __stdcall RemoveVectoredExceptionHandler(void* handle);

    __declspec(dllimport)
    top_level_exception_filter* __stdcall SetUnhandledExceptionFilter(top_level_exception_filter* topLevelExceptionFilter);

    __declspec(dllimport)
    std::int32_t __stdcall UnhandledExceptionFilter(exception_pointers* exceptionInfo);
}
}
