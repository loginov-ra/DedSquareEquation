
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "SquareEquation.h"

const int DEFAULT_PRECISION = -1;
const size_t MAX_ANSWER_SIZE = 256;

struct Options
{
    int precision_;
    bool needVerbose_;
};

Options getOptions(int argc, char** argv);
bool needContinuation();

int main(int argc, char** argv)
{
    Options options = getOptions(argc, argv);

    double a = 0, b = 0, c = 0;
    
    printf("Hi! This is a v1.0 of SquareEquationSolver\n");

    do
    {
        printf("Imagine your favourite ax^2 + bx + c = 0 equation and just enter a, b, c!\n"
               "a: ");

        scanf("%lf", &a);

        printf("b: ");
        scanf("%lf", &b);

        printf("c: ");
        scanf("%lf", &c);

        double root1 = 0, root2 = 0;

        int nRoots = solveEquation(a, b, c, &root1, &root2, options.needVerbose_);

        printf("Your equation %gx^2 + %gx + %g = 0 has ", a, b, c);
        
        if (options.precision_ != DEFAULT_PRECISION)
            std::cout << std::setprecision(options.precision_) << std::fixed;

        if (nRoots == INFINITE_ROOTS)
        {
            printf("has infinite number of roots!\n"
                   "Any number will fit the equation!\n");
        }
        else if (nRoots == 1)
        {
            std::cout << " 1 root. It is " << root1 << "\n";
        }
        else if (nRoots == 0)
        {
            printf(" no roots!\n");
        }
        else
        {
            std::cout << " 2 roots. They are " << root1 << " and " << root2 << "\n";
        }
    }
    while (needContinuation());

    printf("See you later!\n");
}

bool needContinuation()
{
    char answer[MAX_ANSWER_SIZE + 2] = "";
    int nAttempts = 0;

    while (strcmp(answer, "y") != 0 and strcmp(answer, "n") != 0)
    {
        if (nAttempts == 0)
            printf("Do you need to try again? [y/n]\n");
        else
            printf("Please enter only 'y' or 'n'\n");
        
        scanf("%s", answer);
        ++nAttempts;
    }

    return strcmp(answer, "y") == 0;
}

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
