
#include <vector>
#include <cassert>
#include <cmath>

const int INFINITE_ROOTS = -1;

int solveNontrivialSquareEquation(double a, double b, double c, double* root1, double* root2);
int solveLinearEquation(double a, double b, double* root);

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
