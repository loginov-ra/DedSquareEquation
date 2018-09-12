
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "SquareEquation.h"

const int DEFAULT_PRECISION = -1;

struct Options
{
    int precision_;
    bool needVerbose_;
};

Options getOptions(int argc, char** argv)
{
    opterr = 1;
    const char* possibleOptions = "p:v";
    option longOpt[3] = { {"precision", 1, nullptr, 'p'},
                           {"verbose",   0, nullptr, 'v'},
                           {0,           0,       0,   0} };
    Options optionsGot = {DEFAULT_PRECISION, false}; 

    
    int opt = 0;
    while ((opt = getopt_long(argc, argv, possibleOptions, longOpt, nullptr)) != -1)
    {
        switch (opt)
        {
            case 'p':
                optionsGot.precision_ = atoi(optarg);
                assert(optionsGot.precision_ >= 0);
                break;

            case 'v':
                optionsGot.needVerbose_ = true;
                break;
        }
    }

    return optionsGot;
}

int main(int argc, char** argv)
{
    Options options = getOptions(argc, argv);
    printf("Precision: %d, Verbose: %d\n", options.precision_, options.needVerbose_);

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
