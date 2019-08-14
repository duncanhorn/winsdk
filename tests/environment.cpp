
#include <win32/environment.h>

#include "test_guard.h"

using namespace std::literals;

static int get_env_variable_test() try
{
    test_guard guard{ "get_env_variable_test" };

    std::string value;
    if (win32::try_get_env_variable("ThisShouldNotExist", value)) return 1;
    if (!win32::try_get_env_variable("PATH", value)) return 1;
    if (value.empty()) return 1;

    return guard.success();
}
CATCH_RETURN_ERROR();

static int set_env_variable_test() try
{
    test_guard guard{ "set_env_variable_test" };

    win32::set_env_variable("TestVariable", "TestValue");
    if (win32::get_env_variable("TestVariable") != "TestValue") return 1;

    return guard.success();
}
CATCH_RETURN_ERROR();

static int enumerate_env_variables() try
{
    test_guard guard{ "enumerate_env_variables" };

    bool found = false;
    for (auto& pair : win32::environment_strings())
    {
        if (pair.first == "TEMP"sv)
        {
            found = true;
        }
    }
    if (!found) return false;

    return guard.success();
}
CATCH_RETURN_ERROR();

int environment_tests()
{
    int result = 0;
    result += get_env_variable_test();
    result += set_env_variable_test();
    result += enumerate_env_variables();
    return result;
}
