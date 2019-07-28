
#include <cstdio>

struct test_guard
{
    const char* name;

    ~test_guard()
    {
        if (name)
        {
            printf("ERROR: Test '%s' failed\n", name);
        }
    }

    int success() noexcept
    {
        name = nullptr;
        return 0;
    }
};
