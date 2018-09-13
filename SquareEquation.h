
/*!
 * \file
 * \brief Square equation solver library
 * \details Provides interface to solve square equations of different types. Linear are also supported.
 * \author Roman Loginov
 * \version 1.0
 */

/*! \mainpage Square Equation Solver
 * \section Description
 * Sometimes we are needed to solve equations, and they can be different<br>
 * When we do it during the exam, numbers are fit to make us happier<br>
 * And what if not? What if numbers are kind of random? <br>
 * That's why meet <b>SquareEquationSolver</b><br>
 * Read further documentation and go on!
 */

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

/*!
 * Constant to indicate infinite number of roots.
 */
const int INFINITE_ROOTS = -1;

/*!
 * Allows to make debug output more concise
 */
#define COUT if (needVerbose) std::cout

int solveNontrivialSquareEquation(double a, double b, double c, double* root1, double* root2, bool needVerbose);
int solveLinearEquation(double a, double b, double* root, bool needVerbose);

/*!
 * Main solver function.<br>
 * Implements common method of solution by discriminant.<br>
 * Equation view is: \f$ax^2 + bx + c = 0\f$.<br>
 * If less than two roots found, the last remain the same.
 * @param a Coefficient before x^2
 * @param b Coefficient before x
 * @param c Free coefficient
 * @param root1 Pointer to the first root
 * @param root2 Pointer to the second root
 * @param needVerbose - Is huge output provided
 * @return Number of roots found
 */
int solveEquation(double a, double b, double c, double* root1, double* root2, bool needVerbose = false)
{
    assert(root1);
    assert(root2);
    assert(root1 != root2);
    
    COUT << "I am square equation with coeffs: [" << a << ", " << b << ", " << c << "]\n";
    if (a != 0)
    {
        COUT << "A is not 0, that's why I am not trivial\n";
        return solveNontrivialSquareEquation(a, b, c, root1, root2, needVerbose);
    }
    else
    {
        COUT << "A is 0, so equation is in fact linear\n";
        return solveLinearEquation(b, c, root1, needVerbose);
    }
}

/*!
 * Nontrivial solver.<br>
 * Finds roots if the degree of equation is <i>strictly</i> 2.<br>
 * Parameters and return value are similar with solveEquation()
 * @see solveEquation()
 */
int solveNontrivialSquareEquation(double a, double b, double c, double* root1, double* root2, bool needVerbose = false)
{
    assert(root1);
    assert(root2);
    assert(root1 != root2);
    assert(a != 0);
    COUT << "Nontrivial equation solver called\n";

    double discriminant = b * b - 4 * a * c;
    COUT << "Discriminant counted as D = " << discriminant << "\n";

    if (discriminant < 0)
    {
        COUT << "Zero roots cause D < 0.\nThe end.\n";
        return 0;
    }
    
    *root1 = (-b + sqrt(discriminant)) / (2 * a);
    COUT << "D >= 0. First root calculated: " << *root1 << "\n";

    if (discriminant > 0)
    {
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
        COUT << "Moreover, D > 0, so second root calculated " << *root2 << "\n";
    }
    
    COUT << "Finally, number of roots is " << 1 + (discriminant > 0);
    return 1 + (discriminant > 0);
}

/*!
 * Linear equation solver.<br>
 * Simply solves \f$ax + b = 0\f$ equation.<br>
 * @param a, b - coefficients of the equation
 * @param needVerbose - Is huge ouput provided
 * @return Number of roots found. If it is infinite, returns #INFINITE_ROOTS
 */
int solveLinearEquation(double a, double b, double* root, bool needVerbose)
{
    assert(root);
    COUT << "Linear equation solver called!\n";

    if (a == 0)
    {
        COUT << "But that's not linear. It is c = 0\n";
        if (b == 0)
        {
            COUT << "0 = 0 is always true. Infinite number of roots!\n";
            return INFINITE_ROOTS; //Any value in root fits
        }
        else
        {
            COUT << "When c is not 0, no roots can be found\n";
            return 0;
        }
    }
    
    *root = -b / a;
    COUT << "Single root " << *root << "\n";
    return 1;
}
