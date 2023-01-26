#include "../src/Goal.h"

#include "Assert.h"
#include "../src/Action.h"

void test__goal_without_precondition__always_reachable()
{
    Goal goal({});
    Action empty_action({}, {});
    Action some_action({ Condition(1, true) }, { Condition(2, true), Condition(3, false) });

    ASSERT_EQUAL(goal.is_reachable_by(empty_action), true, "Goal without pre-conditions can be reached by action without post-conditions");
    ASSERT_EQUAL(goal.is_reachable_by(some_action), true, "Goal without pre-conditions can be reached by action with post-conditions");
}

void test__goal_with_precondition__is_reachable()
{
    Goal goal({ Condition(1, true), Condition(2, false) });
    Action action({}, { Condition(2, false), Condition(1, true) });
    ASSERT_EQUAL(goal.is_reachable_by(action), true, "Goal is reachable by action with matching pre/post-conditions");
}

void test__goal_with_precondition__is_not_reachable()
{
    Goal goal({ Condition(1, true), Condition(2, false) });
    Action action({}, { Condition(2, true), Condition(3, true) });
    ASSERT_EQUAL(goal.is_reachable_by(action), false, "Goal is not reachable by action with not matching pre/post-conditions");
}

int Goal_test(int, char**)
{
    test__goal_without_precondition__always_reachable();
    test__goal_with_precondition__is_reachable();
    test__goal_with_precondition__is_not_reachable();

    return 0;
}
