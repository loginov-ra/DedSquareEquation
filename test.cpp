
#include "RLTest.h"
#include "SquareEquation.h"
#include <algorithm>

using std::min;
using std::max;

#define SOLVE_EQ(A, B, C)                               \
    double x1 = 0, x2 = 0;                              \
    int nRoots = solveEquation(A, B, C, &x1, &x2);      

DEFINE_TEST(IntegerSolution)
    SOLVE_EQ(1, 2, -3)
    ASSERT_EQUAL(nRoots, 2);
    ASSERT_EQUAL(std::min(x1, x2), -3);
    ASSERT_EQUAL(std::max(x1, x2),  1);
}

DEFINE_TEST(DiscriminantLessZero)
    SOLVE_EQ(1, 2, 2)
    ASSERT_TRUE(nRoots == 0)
}

DEFINE_TEST(LinearEquation)
    SOLVE_EQ(0, 2, 1)
    ASSERT_EQUAL(nRoots, 1);
    ASSERT_TRUE(x1 == -0.5);
}

DEFINE_TEST(ConstInvalid)
    SOLVE_EQ(0, 0, 1)
    ASSERT_EQUAL(nRoots, 0);    
}

DEFINE_TEST(Zeros)
    SOLVE_EQ(0, 0, 0)
    ASSERT_EQUAL(nRoots, INFINITE_ROOTS)
}

DEFINE_TEST(RandomNumbers)
    double a = 12, b = 13.5, c = 0.2;
    SOLVE_EQ(a, b, c)
    ASSERT_CLOSE(a * x1 * x1 + b * x1 + c, 0);
    ASSERT_EQUAL(a * x2 * x2 + b * x2 + c, 0);
}

DEFINE_TEST(Crasher)
    CRASH_TEST("I planned it")
}

int main()
{
    RUN_TEST(IntegerSolution);
    RUN_TEST(DiscriminantLessZero);
    RUN_TEST(LinearEquation);
    RUN_TEST(ConstInvalid);
    RUN_TEST(Zeros);
    RUN_TEST(RandomNumbers);
    RUN_TEST(Crasher);
}
