
#include <cstdio>
#include "SquareEquation.h"

int main()
{
    double a = 0, b = 0, c = 0;
    
    printf("Hi! This is a v1.0 of SquareEquationSolver\n"
           "Imagine your favourite ax^2 + bx + c = 0 equation and just enter a, b, c!\n"
           "a: ");

    scanf("%lf", &a);

    printf("b: ");
    scanf("%lf", &b);

    printf("c: ");
    scanf("%lf", &c);

    double root1 = 0, root2 = 0;

    int nRoots = solveEquation(a, b, c, &root1, &root2);

    printf("Your equation %gx^2 + %gx + %g = 0 has ", a, b, c);

    if (nRoots == INFINITE_ROOTS)
    {
        printf("has infinite number of roots!\n"
               "Any number will fit the equation!\n");
    }
    else if (nRoots == 1)
    {
        printf(" 1 root. It is %g\n", root1);
    }
    else
    {
        printf(" 2 roots. They are %g and %g\n", root1, root2);
    }

    printf("See you later!\n");
}
