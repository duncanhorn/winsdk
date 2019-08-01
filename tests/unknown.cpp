
#include <win32/com_ptr.h>
#include <win32/unknown.h>

#include "test_guard.h"

struct TestInterface : winsdk::IUnknown
{
    static constexpr winsdk::guid uuid = { 0x33fea9cd, 0x4ea1, 0x48fe, { 0x85, 0xdb, 0x67, 0xcb, 0x8a, 0x58, 0x90, 0xc7 }};
    virtual int Doit() noexcept = 0;
};

struct TestInterface2 : TestInterface
{
    static constexpr winsdk::guid uuid = { 0xc871888f, 0x47ba, 0x487a, { 0xaf, 0xd3, 0x6d, 0x45, 0xbe, 0x30, 0x68, 0x45 }};

    virtual int Doit2() noexcept = 0;
};

struct TestStruct : win32::IUnknown<TestStruct, win32::interface_list<TestInterface2, TestInterface>>
{
    // All functions should be implemented for us
    inline static bool destructor_ran = false;
    ~TestStruct() { destructor_ran = true; }

    virtual int Doit() noexcept override
    {
        return 42;
    }

    virtual int Doit2() noexcept override
    {
        return 8;
    }
};

static int basic_ref_counting_test()
{
    test_guard guard{ "basic_ref_counting_test" };

    TestStruct::destructor_ran = false;
    {
        win32::com_ptr<TestStruct> ptr;
        ptr.value = new TestStruct();
        if (ptr->reference_count.load() != 1) return 1;

        {
            win32::com_ptr<TestStruct> ptr2 = ptr;
            if (ptr->reference_count.load() != 2) return 1;
        }
        if (ptr->reference_count.load() != 1) return 1;

        if (ptr->Doit() != 42) return 1;
    }
    if (!TestStruct::destructor_ran) return 1;

    return guard.success();
}

static int basic_query_test()
{
    test_guard guard{ "basic_query_test" };

    TestStruct::destructor_ran = false;
    {
        win32::com_ptr<TestStruct> ptr;
        ptr.attach(new TestStruct());

        win32::com_ptr<TestInterface2> iface2;
        iface2 = ptr; // No QI needed

        win32::com_ptr<TestInterface> iface;
        iface = iface2; // No QI needed

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
#endif
        iface2 = iface2; // Self assignment handled okay
#ifdef __clang
#pragma clang diagnostic pop
#endif

        iface = iface2.as<TestInterface>();
        iface2 = iface.as<TestInterface2>();
        iface.copy_to(&iface2);
        iface2.copy_to(&iface);
        iface = win32::com_cast<TestInterface>(iface2.value);
        iface2 = win32::com_cast<TestInterface2>(iface.value);

        if (ptr->reference_count.load() != 3) return 1;
    }
    if (!TestStruct::destructor_ran) return 1;

    return guard.success();
}

int unknown_tests()
{
    int result = 0;
    result += basic_ref_counting_test();
    result += basic_query_test();
    return result;
}
