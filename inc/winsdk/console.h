#pragma once

#include "base.h"

extern "C"
{
namespace winsdk
{
    // Type Definitions
    using handler_routine = bool_t (__stdcall*)(std::uint32_t ctrlType);

    // Constants
    constexpr std::uint32_t std_input_handle = 0xFFFFFFF6; // -10
    constexpr std::uint32_t std_output_handle = 0xFFFFFFF5; // -11
    constexpr std::uint32_t std_error_handle = 0xFFFFFFF4; // -12

    constexpr std::uint32_t enable_processed_input = 0x0001;
    constexpr std::uint32_t enable_line_input = 0x0002;
    constexpr std::uint32_t enable_echo_input = 0x0004;
    constexpr std::uint32_t enable_window_input = 0x0008;
    constexpr std::uint32_t enable_mouse_input = 0x0010;
    constexpr std::uint32_t enable_insert_mode = 0x0020;
    constexpr std::uint32_t enable_quick_edit_mode = 0x0040;
    constexpr std::uint32_t enable_extended_flags = 0x0080;
    constexpr std::uint32_t enable_auto_position = 0x0100;
    constexpr std::uint32_t enable_virtual_terminal_input = 0x0200;

    constexpr std::uint32_t enable_processed_output = 0x0001;
    constexpr std::uint32_t enable_wrap_at_eol_output = 0x0002;
    constexpr std::uint32_t enable_virtual_terminal_processing = 0x0004;
    constexpr std::uint32_t disable_newline_auto_return = 0x0008;
    constexpr std::uint32_t enable_lvb_grid_worldwide = 0x0010;

    constexpr std::uint32_t ctrl_c_event = 0;
    constexpr std::uint32_t ctrl_break_event = 1;
    constexpr std::uint32_t ctrl_close_event = 2;
    constexpr std::uint32_t ctrl_logoff_event = 5;
    constexpr std::uint32_t ctrl_shutdown_event = 6;

    constexpr std::uint16_t foreground_blue = 0x0001;
    constexpr std::uint16_t foreground_green = 0x0002;
    constexpr std::uint16_t foreground_red = 0x0004;
    constexpr std::uint16_t foreground_intensity = 0x0008;
    constexpr std::uint16_t background_blue = 0x0010;
    constexpr std::uint16_t background_green = 0x0020;
    constexpr std::uint16_t background_red = 0x0040;
    constexpr std::uint16_t background_intensity = 0x0080;
    constexpr std::uint32_t common_lvb_leading_byte = 0x0100;
    constexpr std::uint32_t common_lvb_trailing_byte = 0x0200;
    constexpr std::uint32_t common_lvb_grid_horizontal = 0x0400;
    constexpr std::uint32_t common_lvb_grid_lvertical = 0x0800;
    constexpr std::uint32_t common_lvb_grid_rvertical = 0x1000;
    constexpr std::uint32_t common_lvb_reverse_video = 0x4000;
    constexpr std::uint32_t common_lvb_underscore = 0x8000;

    constexpr std::uint32_t console_no_selection = 0x0000;
    constexpr std::uint32_t console_selection_in_progress = 0x0001;
    constexpr std::uint32_t console_selection_not_empty = 0x0002;
    constexpr std::uint32_t console_mouse_selection = 0x0004;
    constexpr std::uint32_t console_mouse_down = 0x0008;

    constexpr std::uint32_t history_no_dup_flag = 0x01;

    constexpr std::uint32_t console_fullscreen = 1;
    constexpr std::uint32_t console_fullscreen_hardware = 2;

    constexpr std::uint32_t console_fullscreen_mode = 1;
    constexpr std::uint32_t console_windowed_mode = 2;

    constexpr std::uint32_t right_alt_pressed = 0x0001;
    constexpr std::uint32_t left_alt_pressed = 0x0002;
    constexpr std::uint32_t right_ctrl_pressed = 0x0004;
    constexpr std::uint32_t left_ctrl_pressed = 0x0008;
    constexpr std::uint32_t shift_pressed = 0x0010;
    constexpr std::uint32_t numlock_on = 0x0020;
    constexpr std::uint32_t scrolllock_on = 0x0040;
    constexpr std::uint32_t capslock_on = 0x0080;
    constexpr std::uint32_t enhanced_key = 0x0100;
    constexpr std::uint32_t nls_dbcschar = 0x00010000;
    constexpr std::uint32_t nls_alphanumeric = 0x00000000;
    constexpr std::uint32_t nls_katakana = 0x00020000;
    constexpr std::uint32_t nls_hiragana = 0x00040000;
    constexpr std::uint32_t nls_roman = 0x00400000;
    constexpr std::uint32_t nls_ime_conversion = 0x00800000;
    constexpr std::uint32_t altnumpad_bit = 0x04000000;
    constexpr std::uint32_t nls_ime_disable = 0x20000000;

    // Structures
    struct coord
    {
        std::int16_t x;
        std::int16_t y;
    };

    struct small_rect
    {
        std::int16_t left;
        std::int16_t top;
        std::int16_t right;
        std::int16_t bottom;
    };

    struct key_event_record
    {
        bool_t key_down;
        std::uint16_t repeat_count;
        std::uint16_t virtual_key_code;
        std::uint16_t virtual_scan_code;
        union
        {
            wchar_t unicode_char;
            char ascii_char;
        } character;
        std::uint32_t control_key_state;
    };

    struct mouse_event_record
    {
        coord mouse_position;
        std::uint32_t button_state;
        std::uint32_t control_key_state;
        std::uint32_t event_flags;
    };

    struct window_buffer_size_record
    {
        coord size;
    };

    struct menu_event_record
    {
        std::uint32_t command_id;
    };

    struct focus_event_record
    {
        bool_t set_focus;
    };

    struct input_record
    {
        std::uint16_t event_type;
        union
        {
            key_event_record key_event;
            mouse_event_record mouse_event;
            window_buffer_size_record window_buffer_size_event;
            menu_event_record menu_event;
            focus_event_record focus_event;
        } event;
    };

    struct console_readconsole_control
    {
        std::uint32_t length;
        std::uint32_t initial_chars;
        std::uint32_t ctrl_wakeup_mask;
        std::uint32_t control_key_state;
    };

    struct console_cursor_info
    {
        std::uint32_t size;
        bool_t visible;
    };

    struct console_screen_buffer_info
    {
        coord size;
        coord cursorPosition;
        std::uint16_t attributes;
        small_rect window;
        coord maximum_window_size;
    };

    struct console_screen_buffer_infoex
    {
        std::uint32_t bytes;
        coord size;
        coord cursor_position;
        std::uint16_t attributes;
        small_rect window;
        coord maximum_window_size;
        std::uint16_t popup_attributes;
        bool_t fullscreen_supported;
        std::uint32_t color_table[16];
    };

    struct char_info
    {
        union
        {
            wchar_t unicode_char;
            char ascii_char;
        } character;
        std::uint16_t attributes;
    };

    struct console_font_info
    {
        std::uint32_t font;
        coord font_size;
    };

    struct console_font_infoex
    {
        std::uint32_t size;
        std::uint32_t font;
        coord font_size;
        std::uint32_t font_family;
        std::uint32_t font_weight;
        wchar_t face_name[32]; // LF_FACESIZE
    };

    struct console_selection_info
    {
        std::uint32_t flags;
        coord selection_anchor;
        small_rect selection;
    };

    struct console_history_info
    {
        std::uint32_t size;
        std::uint32_t history_buffer_size;
        std::uint32_t number_of_history_buffers;
        std::uint32_t flags;
    };

    // Functions
    __declspec(dllimport)
    bool_t __stdcall AllocConsole();

    __declspec(dllimport)
    bool_t __stdcall FreeConsole();

    __declspec(dllimport)
    handle_t __stdcall GetStdHandle(std::uint32_t stdHandle);

    __declspec(dllimport)
    bool_t __stdcall AttachConsole(std::uint32_t processId);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleCP();

    __declspec(dllimport)
    bool_t __stdcall SetConsoleCP(std::uint32_t codePageID);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleOutputCP();

    __declspec(dllimport)
    bool_t __stdcall SetConsoleOutputCP(std::uint32_t codePageID);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleMode(handle_t consoleHandle, std::uint32_t* mode);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleMode(handle_t consoleHandle, std::uint32_t mode);

    __declspec(dllimport)
    bool_t __stdcall GetNumberOfConsoleInputEvents(handle_t consoleInput, std::uint32_t* count);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleInputA(
        handle_t consoleInput,
        input_record* inputRecord,
        std::uint32_t count,
        std::uint32_t* readCount);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleInputW(
        handle_t consoleInput,
        input_record* inputRecord,
        std::uint32_t count,
        std::uint32_t* readCount);

    __declspec(dllimport)
    bool_t __stdcall PeekConsoleInputA(
        handle_t consoleInput,
        input_record* buffer,
        std::uint32_t bufferCount,
        std::uint32_t* readCount);

    __declspec(dllimport)
    bool_t __stdcall PeekConsoleInputW(
        handle_t consoleInput,
        input_record* buffer,
        std::uint32_t bufferCount,
        std::uint32_t* readCount);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleInputA(
        handle_t consoleInput,
        const input_record* buffer,
        std::uint32_t length,
        std::uint32_t* writeCount);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleInputW(
        handle_t consoleInput,
        const input_record* buffer,
        std::uint32_t length,
        std::uint32_t* writeCount);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleA(
        handle_t consoleInput,
        void* buffer,
        std::uint32_t bufferCharCount,
        std::uint32_t* readCharCount,
        console_readconsole_control* inputControl);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleW(
        handle_t consoleInput,
        void* buffer,
        std::uint32_t bufferCharCount,
        std::uint32_t* readCharCount,
        console_readconsole_control* inputControl);

    __declspec(dllimport)
    bool_t __stdcall FlushConsoleInputBuffer(handle_t consoleInput);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleA(
        handle_t consoleOutput,
        const void* buffer,
        std::uint32_t bufferCharCount,
        std::uint32_t* writeCharCount,
        void* reserved);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleW(
        handle_t consoleOutput,
        const void* buffer,
        std::uint32_t bufferCharCount,
        std::uint32_t* writeCharCount,
        void* reserved);

    __declspec(dllimport)
    bool_t __stdcall FillConsoleOutputCharacterA(
        handle_t consoleOutput,
        char ch,
        std::uint32_t count,
        coord writeCoord,
        std::uint32_t* writeCount);

    __declspec(dllimport)
    bool_t __stdcall FillConsoleOutputCharacterW(
        handle_t consoleOutput,
        wchar_t ch,
        std::uint32_t count,
        coord writeCoord,
        std::uint32_t* writeCount);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleCtrlHandler(handler_routine handlerRoutine, bool_t add);

    __declspec(dllimport)
    bool_t __stdcall FillConsoleOutputAttribute(
        handle_t consoleOutput,
        std::uint16_t attribute,
        std::uint32_t length,
        coord writeCoord,
        std::uint32_t writeCount);

    __declspec(dllimport)
    bool_t __stdcall GenerateConsoleCtrlEvent(std::uint32_t ctrlEvent, std::uint32_t processGroupId);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleTitleA(char* titleBuffer, std::uint32_t bufferSize);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleTitleW(wchar_t* titleBuffer, std::uint32_t bufferSize);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleOriginalTitleA(char* titleBuffer, std::uint32_t bufferSize);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleOriginalTitleW(wchar_t* titleBuffer, std::uint32_t bufferSize);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleTitleA(const char* title);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleTitleW(const wchar_t* title);

    __declspec(dllimport)
    bool_t __stdcall GetNumberOfConsoleMouseButtons(std::uint32_t* count);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleSelectionInfo(console_selection_info* info);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleHistoryInfo(console_history_info* info);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleHistoryInfo(console_history_info* info);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleDisplayMode(std::uint32_t* modeFlags);

    __declspec(dllimport)
    hwnd_t __stdcall GetConsoleWindow();

    __declspec(dllimport)
    bool_t __stdcall AddConsoleAliasA(char* source, char* target, char* exeName);

    __declspec(dllimport)
    bool_t __stdcall AddConsoleAliasW(wchar_t* source, wchar_t* target, wchar_t* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasA(
        char* source,
        char* targetBuffer,
        std::uint32_t targetBufferLength,
        char* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasW(
        wchar_t* source,
        wchar_t* targetBuffer,
        std::uint32_t targetBufferLength,
        wchar_t* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasesLengthA(char* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasesLengthW(wchar_t* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasesA(char* buffer, std::uint32_t bufferLength, char* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasesW(wchar_t buffer, std::uint32_t bufferLength, wchar_t exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasExesLengthA();

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasExesLengthW();

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasExesA(char* buffer, std::uint32_t bufferLength);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleAliasExesW(wchar_t* buffer, std::uint32_t bufferLength);

    __declspec(dllimport)
    void __stdcall ExpungeConsoleCommandHistoryA(char* exeName);

    __declspec(dllimport)
    void __stdcall ExpungeConsoleCommandHistoryW(wchar_t* exeName);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleNumberOfCommandsA(std::uint32_t number, char* exeName);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleNumberOfCommandsW(std::uint32_t number, wchar_t* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleCommandHistoryLengthA(char* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleCommandHistoryLengthW(wchar_t* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleCommandHistoryA(char* buffer, std::uint32_t bufferLength, char* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleCommandHistoryW(wchar_t* buffer, std::uint32_t bufferLength, wchar_t* exeName);

    __declspec(dllimport)
    std::uint32_t __stdcall GetConsoleProcessList(std::uint32_t* processList, std::uint32_t count);

    __declspec(dllimport)
    std::int32_t __stdcall CreatePseudoConsole(
        coord size,
        handle_t input,
        handle_t output,
        std::uint32_t flags,
        handle_t* consoleHandle);

    __declspec(dllimport)
    std::int32_t __stdcall ResizePseudoConsole(handle_t consoleHandle, coord size);

    __declspec(dllimport)
    void __stdcall ClosePseudoConsole(handle_t consoleHandle);

    __declspec(dllimport)
    handle_t __stdcall CreateConsoleScreenBuffer(
        std::uint32_t desiredAccess,
        std::uint32_t shareMode,
        const security_attributes* securityAttributes,
        std::uint32_t flags,
        void* screenBufferData);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleActiveScreenBuffer(handle_t consoleOutput);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleCursorInfo(handle_t consoleOutput, console_cursor_info* info);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleCursorInfo(handle_t consoleOutput,const console_cursor_info* info);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleScreenBufferInfo(handle_t consoleOutput, console_screen_buffer_info* info);

    __declspec(dllimport)
    bool_t __stdcall GetConsoleScreenBufferInfoEx(handle_t consoleOutput, console_screen_buffer_infoex* info);

    __declspec(dllimport)
    coord __stdcall GetLargestConsoleWindowSize(handle_t consoleOutput);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleScreenBufferInfoEx(handle_t consoleOutput, console_screen_buffer_infoex* info);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleScreenBufferSize(handle_t consoleOutput, coord size);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleCursorPosition(handle_t consoleOutput, coord cursorPosition);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleTextAttribute(handle_t consoleOutput, std::uint16_t attributes);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleWindowInfo(handle_t consoleOutput, bool_t absolute, const small_rect* consoleWindow);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleOutputCharacterA(
        handle_t consoleOutput,
        const char* text,
        std::uint32_t length,
        coord writeCoord,
        std::uint32_t* writeLength);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleOutputCharacterW(
        handle_t consoleOutput,
        const wchar_t* text,
        std::uint32_t length,
        coord writeCoord,
        std::uint32_t* writeLength);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleOutputAttribute(
        handle_t consoleOutput,
        const std::uint16_t* attributes,
        std::uint32_t length,
        coord writeCoord,
        std::uint32_t* writeLength);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleOutputA(
        handle_t consoleOutput,
        const char_info* buffer,
        coord bufferSize,
        coord bufferCoord,
        small_rect* writeRegion);

    __declspec(dllimport)
    bool_t __stdcall WriteConsoleOutputW(
        handle_t consoleOutput,
        const char_info* buffer,
        coord bufferSize,
        coord bufferCoord,
        small_rect* writeRegion);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleOutputCharacterA(
        handle_t consoleOutput,
        char* text,
        std::uint32_t length,
        coord readCoord,
        std::uint32_t readLength);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleOutputCharacterW(
        handle_t consoleOutput,
        wchar_t* text,
        std::uint32_t length,
        coord readCoord,
        std::uint32_t readLength);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleOutputAttribute(
        handle_t consoleOutput,
        std::uint16_t* attributes,
        std::uint32_t length,
        coord readCoord,
        std::uint32_t* readLength);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleOutputA(
        handle_t consoleOutput,
        char_info* buffer,
        coord bufferSize,
        coord bufferCoord,
        small_rect* readRegion);

    __declspec(dllimport)
    bool_t __stdcall ReadConsoleOutputW(
        handle_t consoleOutput,
        char_info* buffer,
        coord bufferSize,
        coord bufferCoord,
        small_rect* readRegion);

    __declspec(dllimport)
    bool_t __stdcall ScrollConsoleScreenBufferA(
        handle_t consoleOutput,
        const small_rect* scrollRectangle,
        const small_rect* clipRectangle,
        coord destinationOrigin,
        const char_info* fill);

    __declspec(dllimport)
    bool_t __stdcall ScrollConsoleScreenBufferW(
        handle_t consoleOutput,
        const small_rect* scrollRectangle,
        const small_rect* clipRectangle,
        coord destinationOrigin,
        const char_info* fill);

    __declspec(dllimport)
    coord __stdcall GetConsoleFontSize(handle_t consoleOutput, std::uint32_t fontIndex);

    __declspec(dllimport)
    bool_t __stdcall GetCurrentConsoleFont(handle_t consoleOutput, bool_t maximumWindow, console_font_info* info);

    __declspec(dllimport)
    bool_t __stdcall GetCurrentConsoleFontEx(handle_t consoleOutput, bool_t maximumWindow, console_font_infoex* info);

    __declspec(dllimport)
    bool_t __stdcall SetCurrentConsoleFontEx(handle_t consoleOutput, bool_t maximumWindow, console_font_infoex* info);

    __declspec(dllimport)
    bool_t __stdcall SetConsoleDisplayMode(handle_t consoleOutput, std::uint32_t flags, coord* newDimensions);
}
}
