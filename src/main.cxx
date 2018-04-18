#include <initializer_list>
#include <memory>
#include <iostream>
#include <type_traits>
#include <exception>
#include <map>
#include <array>
#include <math.h>
#include <cmath>
#include <stdio.h>

// Home made headers
#include "vector.hxx"
#include "matrix.hxx"
#include "cg.hxx"
#include "heat_lucas.hxx"


int main(){
    
// See if we can construct a matrix.
    Vector<double> x = {2,5};
    Matrix<double> M(2,2);
    M[{{0,0}}] = 1;
    M[{{0,1}}] = 0;
    M[{{1,0}}] = 0;
    M[{{1,1}}] = 1;

    M.print();
    Vector<double> matvecCheck = M.matvec(x);
    matvecCheck.print();

// Check if Heat1D is working (attributes are put on public)
    double alpha = 0.3125;
    double dt = 0.001;
    int m = 10;

    std::cout << "1D M Matrix with test values: " << std::endl;
    Heat1D MatrixCheck1D(alpha, m, dt);
//    MatrixCheck1D.M.print();
    
// Check if the solve and exact functions return the same values for 1D
    Vector<double> exactCheck1D = MatrixCheck1D.exact(0.1);

    std::cout << "\n1D Matrix with test values, exact at t = 1: " << std::endl;
    exactCheck1D.print();
    
    try {
        Vector<double> solveCheck1D = MatrixCheck1D.solve(0.1);
        std::cout << "\n1D Matrix with test values, solve at t = 1: " << std::endl;
        solveCheck1D.print();
    } catch (const char* msg)
    {
        std::cerr << msg << std::endl;
    }
    
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\n2D M Matrix with test values: " << std::endl;
    Heat2D MatrixCheck2D(alpha, m, dt);
    MatrixCheck2D.M.print();

    // Check if the solve and exact functions return the same values for 1D
    Vector<double> exactCheck2D = MatrixCheck2D.exact(1);
    
    std::cout << "\n1D Matrix with test values, exact at t = 1: " << std::endl;
    exactCheck2D.print();
    
    try {
        Vector<double> solveCheck2D = MatrixCheck2D.solve(1);
        std::cout << "\n1D Matrix with test values, solve at t = 1: " << std::endl;
        solveCheck2D.print();
    } catch (const char* msg)
    {
        std::cerr << msg << std::endl;
    }
    
    return 0;
}
