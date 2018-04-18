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
    Vector<double> a(6);
    Vector<double> b = {1, 2};
    Vector<double> c = {1, 2};
    Vector<double> checkMove = {1, 2};
    
    int powCheck = pow(2,3);
    
    std::cout << "2 to the power 3: " << powCheck << std::endl;
    
    Vector<double> t = 6*c;
    t.print();
    
    // See if we can construct the matrix.
    Matrix<double> M(2,2);
    M[{{0,0}}] = 1;
    M[{{0,1}}] = 0;
    M[{{1,0}}] = 0;
    M[{{1,1}}] = 1;
    
    M.print();
    
    //firstMap.insert(std::pair<std::array<int,2>, int> (key1, 5));
    
    // Check if Heat1D is working (attributes are put on public)
    double alpha = 0.3125;
    double dt = 0.1;
    int m = 3;
    
    std::cout << "1D M Matrix with test values: " << std::endl;
    Heat1D MatrixCheck1D(alpha, m, dt);
    MatrixCheck1D.M.print();
    
    std::cout << "2D M Matrix with test values: " << std::endl;
    Heat2D MatrixCheck2D(alpha, m, dt);
    MatrixCheck2D.M.print();
    
    return 0;
    }
