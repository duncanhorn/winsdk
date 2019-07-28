
#include <win32/unique_handle.h>
#include <winsdk/synch.h>

#include "test_guard.h"

static int unique_handle_test()
{
    test_guard guard{ "unique_handle_test" };
    win32::unique_handle h;
    h.reset(winsdk::CreateEventA(nullptr, false, false, nullptr));
    if (!h) return 1;

    if (!winsdk::SetEvent(h.get())) return 1;
    if (winsdk::WaitForSingleObject(h.get(), 0) != 0) return 1;
    if (!winsdk::ResetEvent(h.get())) return 1;

    return guard.success();
}

int unique_handle_tests()
{
    int result = 0;
    result += unique_handle_test();
    return result;
}
