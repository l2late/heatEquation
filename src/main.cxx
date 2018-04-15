#include "heatEquation.hxx"

int main(){
    
    Vector<int> a(4);
    Vector<int> b = { 1, 2, 3, 4 };
    Vector<int> c;
    c = a + b;
    Matrix<double> M(2,4);

    b.print();
    //a.print();
    //c.print();
    M.print();
    
    return 0;
};
