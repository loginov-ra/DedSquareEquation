
/*!
 * \file
 * \brief Square equation solver library
 * \details Provides interface to solve square equations of different types. Linear are also supported.
 * \author Roman Loginov
 * \version 1.0
 */

#include <vector>
#include <cassert>
#include <cmath>

/*!
 * Constant to indicate infinite number of roots.
 */
const int INFINITE_ROOTS = -1;

int solveNontrivialSquareEquation(double a, double b, double c, double* root1, double* root2);
int solveLinearEquation(double a, double b, double* root);

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
 * @return Number of roots found
 */
int solveEquation(double a, double b, double c, double* root1, double* root2)
{
    assert(root1);
    assert(root2);
    assert(root1 != root2);

    if (a != 0)
        return solveNontrivialSquareEquation(a, b, c, root1, root2);
    else
        return solveLinearEquation(b, c, root1);
}

/*!
 * Nontrivial solver.<br>
 * Finds roots if the degree of equation is <i>strictly</i> 2.<br>
 * Parameters and return value are similar with solveEquation()
 * @see solveEquation()
 */
int solveNontrivialSquareEquation(double a, double b, double c, double* root1, double* root2)
{
    assert(root1);
    assert(root2);
    assert(root1 != root2);
    assert(a != 0);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return 0;
    }
    
    *root1 = (-b + sqrt(discriminant)) / (2 * a);

    if (discriminant > 0)
        *root2 = (-b - sqrt(discriminant)) / (2 * a);

    return 1 + (discriminant > 0);
}

/*!
 * Linear equation solver.<br>
 * Simply solves \f$ax + b = 0\f$ equation.<br>
 * @param a, b - coefficients of the equation
 * @return Number of roots found. If it is infinite, returns #INFINITE_ROOTS
 */
int solveLinearEquation(double a, double b, double* root)
{
    assert(root);

    if (a == 0)
    {
        if (b == 0)
            return INFINITE_ROOTS; //Any value in root fits
        else
            return 0;
    }
    
    *root = -b / a;
    return 1;
}
