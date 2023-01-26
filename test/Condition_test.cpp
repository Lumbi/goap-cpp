#include "../src/Condition.h"

#include "Assert.h"

void test__is_satisfied_by__itself()
{
    Condition a(1, true);
    ASSERT_EQUAL(a.is_satisfied_by(a), true, "A condition should satisfy itself");
}

void test__is_satisfied_by__true()
{
    Condition a(1, true);
    Condition b(1, true);
    ASSERT_EQUAL(a.is_satisfied_by(b), true, "A condition should be satisfied by another condition with the same ID and predicate");
}

void test__is_satisfied_by__false()
{
    Condition a(1, true);
    Condition b(1, false);
    ASSERT_EQUAL(a.is_satisfied_by(b), false, "A condition should not be satisfied by another condition with opposite predicate");
    ASSERT_EQUAL(b.is_satisfied_by(a), false, "A condition should not be satisfied by another condition with opposite predicate");
}

void test__is_satisfied_by__unrelated()
{
    Condition a(1, true);
    Condition b(17, false);
    ASSERT_EQUAL(a.is_satisfied_by(b), false, "A condition should not be satisfied by another condition with unrelated ID");
    ASSERT_EQUAL(b.is_satisfied_by(a), false, "A condition should not be satisfied by another condition with unrelated ID");
}

int Condition_test(int, char**)
{
    test__is_satisfied_by__itself();
    test__is_satisfied_by__true();
    test__is_satisfied_by__false();
    test__is_satisfied_by__unrelated();

    return 0;
}
