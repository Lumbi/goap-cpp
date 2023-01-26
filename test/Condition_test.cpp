#include "../src/Condition.h"

#include "Assert.h"

int Condition_test(int, char**)
{
    ASSERT_EQUAL(true, false, "Test");
    return 0;
}
