#include "../src/Action.h"

#include "Assert.h"
#include "../src/Condition.h"

void test__empty_action__is_successor_of__always_tue()
{
    Action empty({}, {});
    ASSERT_EQUAL(empty.is_successor_of(empty), true, "An action without pre/post-condition is always a successor of itself");

    Action other({}, { Condition(1, true) });
    ASSERT_EQUAL(empty.is_successor_of(other), true, "An action without pre/post-condition is always a successor of another action");
}

void test__is_successor_of__matching_conditions()
{
    {
        Action first({}, { Condition(1, true) });
        Action second({ Condition(1, true) }, {});
        ASSERT_EQUAL(second.is_successor_of(first), true, "An action is successor of another if the pre/post-condition match");
    }

    {
        Action first({}, { Condition(1, true), Condition(2, false) });
        Action second({ Condition(2, false), Condition(1, true) }, {});
        ASSERT_EQUAL(second.is_successor_of(first), true, "An action is successor of another if all pre/post-conditions match");
    }
}

void test__is_successor_of__not_matching_conditions()
{
    {
        Action first({}, { Condition(1, true) });
        Action second({ Condition(2, true) }, {});
        ASSERT_EQUAL(second.is_successor_of(first), false, "An action is not a successor of another if the pre/post-condition ID don't match");
    }

    {
        Action first({}, { Condition(1, false) });
        Action second({ Condition(1, true) }, {});
        ASSERT_EQUAL(second.is_successor_of(first), false, "An action is not a successor of another if the pre/post-condition predicates don't match");
    }
}

void test__is_successor_of__superset()
{
    Action first({}, { Condition(1, true), Condition(2, false) });
    Action second({ Condition(2, false) }, {});
    ASSERT_EQUAL(second.is_successor_of(first), true, "An action is a successor of another if more pre-conditions match than necessary");
}

void test__is_successor_of__subset()
{
    Action first({}, { Condition(1, true) });
    Action second({ Condition(2, false), Condition(1, true) }, {});
    ASSERT_EQUAL(second.is_successor_of(first), false, "An action is not a successor of another if not all pre-conditions match");
}

int Action_test(int, char**)
{
    test__empty_action__is_successor_of__always_tue();
    test__is_successor_of__matching_conditions();
    test__is_successor_of__not_matching_conditions();
    test__is_successor_of__superset();
    test__is_successor_of__subset();

    return 0;
}
