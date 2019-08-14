
#include <cstdio>

struct test_guard
{
    const char* name;

    ~test_guard()
    {
        if (name)
        {
            std::printf("ERROR: Test '%s' failed\n", name);
        }
    }

    int success() noexcept
    {
        name = nullptr;
        return 0;
    }
};

#define CATCH_RETURN_ERROR() \
    catch (std::exception& e) { \
        std::printf("ERROR: Unhandled exception\nERROR: %s\n", e.what()); \
        return 1; \
    } catch (...) { \
        std::printf("ERROR: Unhandled exception\n"); \
        return 1; \
    }
