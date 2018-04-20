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
static const double pi = 3.14159265358979323846;
#include "vector.hpp"
#include "matrix.hpp"
#include "cg.hpp"
#include "heat.hpp"
#include "heat_general.hpp"


int main(){
    
    // TEST vector and matrix class implementations
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest vector and matrix class implementations:" << std::endl;
    
    std::cout << "Check vector default constructor: Vector<double> a" << std::endl;
    Vector<double> a1;
    a1.print();
    
    std::cout << "Check vector constructor: Vector<double> a(5)" << std::endl;
    Vector<double> a(5);
    a.print();
    
    std::cout << "Check vector constructor from list: Vector<double> b = { 1, 2, 3, 4 }" << std::endl;
    Vector<double> b = { 1, 2, 3, 4 };
    b.print();
    
    std::cout << "Check vector change upon assignment: a = b" << std::endl;
    a = b;
    a.print();
    
    std::cout << "Check vector copy constructor: Vector<double> c = b" << std::endl;
    Vector<double> c = b;
    c.print();
    
    //Vector addition
    std::cout << "Check vector addition: Vector<double> cPlus = b + c;" << std::endl;
    Vector<double> cPlus = b + c;
    cPlus.print();
    
    //Vector substraction
    std::cout << "Check vector substraction: Vector<double> cMin = b - c;" << std::endl;
    Vector<double> cMin = b - c;
    cMin.print();
    
    // Vector left and right multipliction
    std::cout << "Check vector right multiplication with scalar : c*2 =" << std::endl;
    Vector<double> cRight = c*2;
    cRight.print();
    
    std::cout << "Check vector left multiplication with scalar : 2*c =" << std::endl;
    Vector<double> cLeft = 2*c;
    cLeft.print();
    
    // DOT PRODUCT
    std::cout << "Check vector dot product same length: double d = dot(c, b)" << std::endl;
    double d = dot(c, b);
    std::cout << d << "\n" << std::endl;
    
//    std::cout << "Check vector dot product different lengths: double d = dot(c, b)" << std::endl;
//    Vector<double> q = { 1, 2, 3, 4, 7};
//    double r = dot(q, b);
//    std::cout << r << "\n" << std::endl;
    
    //Matrix default constructor
    std::cout << "Check matrix constructor: Matrix<double> M(2,2)" << std::endl;
    Matrix<double> M(2,2);
    M.print();
    
    std::cout << "Check matrix element entry:" << std::endl;
    std::cout << "M[{{0,0}}] = 1;" << std::endl;
    std::cout << "M[{{0,1}}] = 0;" << std::endl;
    std::cout << "M[{{1,0}}] = 0;" << std::endl;
    std::cout << "M[{{1,1}}] = 1;" << std::endl;
    
    // entry assignment
    M[{{0,0}}] = 1;
    M[{{0,1}}] = 0;
    M[{{1,0}}] = 0;
    M[{{1,1}}] = 1;
    M.print();
    
    std::cout << "Check matrix vector multiplication: Vector<double> matvecCheck = M.matvec(x)" << std::endl;
    std::cout << "vector x" << std::endl;
    Vector<double> x = {2,5};
    x.print();
    
    // Check result of matrix vector multiplication
    std::cout << "Result M*x =" << std::endl;
    Vector<double> matvecCheck = M.matvec(x);
    matvecCheck.print();

    // Initialize solver parameters
    double alpha = 0.3125;
    double dt = 0.001;
    int m = 3;

    // TEST generation of M matrix
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest generation of M Matrix:\n" << std::endl;
    
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
    std::cout << "ND Heat equation for 3 dimension: " << std::endl;
    Heat<3> MatrixCheckN3D(alpha, m, dt);
    MatrixCheckN3D.print();
    
    
    // TEST 1D SOLVERS
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest solvers for 1D: " << std::endl;
    
    // Check if the solve and exact functions return similar values for 1D
    Vector<double> exactCheck1D = MatrixCheck1D.exact(0.1);
    std::cout << "\nSpecialized 1D Heat solver: M Matrix with test values, analytic solver at t = 0.1: " << std::endl;
    exactCheck1D.print();
    
    Vector<double> solveCheck1D = MatrixCheck1D.solve(0.1);
    std::cout << "\nSpecialized 1D Heat solver: M Matrix with test values, numeric solver at t = 0.1: " << std::endl;
    solveCheck1D.print();
    
    // Check if the solve and exact functions return similar values for 1D
    Vector<double> exactCheckN1D = MatrixCheckN1D.exact(0.1);
    std::cout << "\nGeneralized 1D Heat solver: M Matrix with test values, analytic solver at t = 0.1: " << std::endl;
    exactCheckN1D.print();
    
    Vector<double> solveCheckN1D = MatrixCheckN1D.solve(0.1);
    std::cout << "\nGeneralized 1D Heat solver: M Matrix with test values, numeric solver at t = 0.1: " << std::endl;
    solveCheckN1D.print();

    
    // TEST 2D SOLVERS
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest solvers for 2D: " << std::endl;
    
    // Check if the solve and exact functions return similar values for 2D
    Vector<double> exactCheck2D = MatrixCheck2D.exact(0.5);
    std::cout << "\nSpecialized 2D Heat solver: M Matrix with test values, analytic solver at t = 0.5: " << std::endl;
    exactCheck2D.print();
    
    Vector<double> solveCheck2D = MatrixCheck2D.solve(0.5);
    std::cout << "\nSpecialized 2D Heat solver: M Matrix with test values, numeric solver at t = 0.5: " << std::endl;
    solveCheck2D.print();
    
    // Check if the solve and exact functions return similar values for 2D
    Vector<double> exactCheckN2D = MatrixCheckN2D.exact(0.5);
    std::cout << "\nGeneralized 2D Heat solver: M Matrix with test values, analytic solver at t = 0.5: " << std::endl;
    exactCheckN2D.print();
    
    Vector<double> solveCheckN2D = MatrixCheckN2D.solve(0.5);
    std::cout << "\nGeneralized 2D Heat solver: M Matrix with test values, numeric solver at t = 0.5: " << std::endl;
    solveCheckN2D.print();
    

    // TEST 3D SOLVERS
    std::cout << " ------------------------------- " << std::endl;
    std::cout << "\nTest solvers for 3D: " << std::endl;
    
    // Check if the solve and exact functions return similar values for 3D
    Vector<double> exactCheckN3D = MatrixCheckN3D.exact(0.5);
    std::cout << "\nSpecialized 3D Heat solver: analytic solver at t = 0.5: " << std::endl;
    exactCheckN3D.print();
    
    Vector<double> solveCheckN3D = MatrixCheckN3D.solve(0.5);
    std::cout << "\nSpecialized 3D Heat solver: numeric solver at t = 0.5: " << std::endl;
    solveCheckN3D.print();
    
    std::cout << " ------------------------------- " << std::endl;
    return 0;
}
