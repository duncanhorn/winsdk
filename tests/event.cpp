
#include <win32/event.h>

#include "test_guard.h"

using namespace std::literals;

static int manual_reset_event_test()
{
    test_guard guard{ "manual_reset_event_test" };
    win32::event evt(true);
    if (evt.wait(0ms)) return 1;
    evt.set();
    if (!evt.wait(0ms)) return 1;
    if (!evt.wait(0ms)) return 1;
    evt.reset();
    if (evt.wait(0ms)) return 1;

    return guard.success();
}

static int auto_reset_event_test()
{
    test_guard guard{ "auto_reset_event_test" };
    win32::event evt;
    if (evt.wait(0ms)) return 1;
    evt.set();
    if (!evt.wait(0ms)) return 1;
    if (evt.wait(0ms)) return 1;

    return guard.success();
}

static int named_event_test()
{
    test_guard guard{ "named_event_test" };
    win32::event first(false, false, "foo");
    win32::event second(false, false, "foo");
    if (second.wait(0ms)) return 1;
    first.set();
    if (!second.wait(0ms)) return 1;

    return guard.success();
}

int event_tests()
{
    int result = 0;
    result += manual_reset_event_test();
    result += auto_reset_event_test();
    result += named_event_test();
    return result;
}
