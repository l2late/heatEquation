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
#include <cstdio>

// Home made headers
#include "vector.hxx"
#include "matrix.hxx"
#include "cg.hxx"
#include "heat_lucas.hxx"


int main(){
    
    // See if we can construct vector and matrix.
    Vector<double> x = {2,5};
    Matrix<double> M(2,2);
    M[{{0,0}}] = 1;
    M[{{0,1}}] = 0;
    M[{{1,0}}] = 0;
    M[{{1,1}}] = 1;
    
    std::cout << "Check matrix vector multiplication: " << std::endl;
    std::cout << "Matrix M" << std::endl;
    M.print();
    
    std::cout << "vector x" << std::endl;
    x.print();
    
    // Check result of matrix vector multiplication
    std::cout << "Result: M*x" << std::endl;
    Vector<double> matvecCheck = M.matvec(x);
    matvecCheck.print();

    // Check if Heat1D is working (attributes are put on public)
    double alpha = 0.3125;
    double dt = 0.1;
    int m = 3;

    // 1D
    // 1D specialization
    std::cout << "1D Heat equation: M Matrix with test values: " << std::endl;
    Heat1D MatrixCheck1D(alpha, m, dt);
    MatrixCheck1D.print();
	
    
    // 1D generalization
	std::cout << "ND Heat equation for 1 dimension: M Matrix with test values: " << std::endl;
	Heat<1> MatrixCheckN1D(alpha, m, dt);
	MatrixCheckN1D.print();
    
    // 2D
    // 2D specialization
    std::cout << "2D Heat equation: M Matrix with test values: " << std::endl;
    Heat2D MatrixCheck2D(alpha, m, dt);
    MatrixCheck2D.print();
    
    // 2D generalization
    std::cout << "ND Heat equation for 2 dimension: M Matrix with test values: " << std::endl;
    Heat<2> MatrixCheckN2D(alpha, m, dt);
    MatrixCheckN2D.print();
    
    // 3D
    // 3D generalization
    std::cout << "ND Heat equation for 3 dimension: M Matrix with test values: " << std::endl;
    Heat<3> MatrixCheckN3D(alpha, m, dt);
    MatrixCheckN3D.print();

    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest solvers for 1D: " << std::endl;
    
    // Check if the solve and exact functions return similar values for 1D
    Vector<double> exactCheck1D = MatrixCheck1D.exact(0.1);
    std::cout << "\nSpecialized 1D Matrix with test values, analytic solver at t = 0.1: " << std::endl;
    exactCheck1D.print();
    
    Vector<double> solveCheck1D = MatrixCheck1D.solve(0.1);
    std::cout << "\nSpecialized 1D Matrix with test values, numeric solver at t = 0.1: " << std::endl;
    solveCheck1D.print();
    
    // Check if the solve and exact functions return similar values for 1D
    Vector<double> exactCheckN1D = MatrixCheckN1D.exact(0.1);
    std::cout << "\nGeneralized 1D Matrix with test values, analytic solver at t = 0.1: " << std::endl;
    exactCheckN1D.print();
    
    Vector<double> solveCheckN1D = MatrixCheckN1D.solve(0.1);
    std::cout << "\nGeneralized 1D Matrix with test values, numeric solver at t = 0.1: " << std::endl;
    solveCheckN1D.print();
    

    
//    std::cout << " ------------------------------- " << std::endl;
//    std::cout << "\n2D M Matrix with test values: " << std::endl;
//    std::cout << "\nHeat2D implementation: " << std::endl;
//    Heat2D MatrixCheck2D(alpha, m, dt);
//    MatrixCheck2D.M.print();
//
//    std::cout << "\nHeatND implementation: " << std::endl;
//    Heat<2> MatrixCheckN2D(alpha, m, dt);
//    MatrixCheckN2D.M.print();

    
    // Check if Heat2D is working (attributes are put on public)
    
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest solvers for 2D: " << std::endl;
    // Check if the solve and exact functions return similar values for 2D
    std::cout << "\n2D Matrix with test values, analytic solver at t = 0.5: " << std::endl;
    Vector<double> exactCheck2D = MatrixCheckN2D.exact(0.5);
    exactCheck2D.print();
    
    std::cout << "\n2D Matrix with test values, numeric solver at t = 0.5: " << std::endl;
    Vector<double> solveCheck2D = MatrixCheckN2D.solve(0.5);
    solveCheck2D.print();
    


    
    /*
    std::cout << "\n2D Matrix with test values, exact at t = 1: " << std::endl;
    exactCheck2D.print();
    
    try {
        Vector<double> solveCheck2D = MatrixCheck2D.solve(1);
        std::cout << "\n2D Matrix with test values, solve at t = 1: " << std::endl;
        solveCheck2D.print();
    } catch (const char* msg)
    {
        std::cerr << msg << std::endl;
    }
    */
    std::cout << " ------------------------------- " << std::endl;
	//std::getchar();
    return 0;
}
