
#include <win32/console.h>

int console_tests()
{
#if 0
    auto stdoutHandle = winsdk::GetStdHandle(winsdk::std_output_handle);
    {
        win32::console_attribute_guard guard(stdoutHandle, win32::foreground_red | 0xFFF0, win32::foreground_mask);
        std::printf("Red text on current background\n");
        std::fflush(stdout);
    }
    {
        win32::console_attribute_guard guard(stdoutHandle,
            win32::foreground_black | win32::background_white,
            win32::foreground_mask | win32::background_mask);
        std::printf("Black text on white background\n");
        std::fflush(stdout);
    }
    std::printf("Normal text on normal background\n");
#endif
    return 0;
}
