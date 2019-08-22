
#include <cstdio>

int unique_handle_tests();
int event_tests();
int unknown_tests();
int environment_tests();
int console_tests();

int main() try
{
    int result = 0;
    result += unique_handle_tests();
    result += event_tests();
    result += unknown_tests();
    result += environment_tests();
    result += console_tests();
    return result;
}
catch (...)
{
    std::printf("ERROR: Unhandled exception running tests\n");
    return -1;
}
