#include <stdio.h>
#include <iostream>
#include <initializer_list>
#include <map>
#include <array>

template<typename T>
class Vector
{
public:
    //default constructor
    Vector():
    length(0), data(nullptr)
    {}
    
    //constructor
    Vector(int length):
    length(length), data(new T[length])
    {}
    
    //copy constructor
    Vector(const Vector& v):
    Vector(v.length)
    {
        for(auto i=0; i<v.length; i++)
            data[i] = v.data[i];
    }
    
    //list constructor
    Vector(std::initializer_list<T> list):
    Vector((int)list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), data);
    }
    
    //Destructor
    ~Vector()
    {
        delete[] data;
        length = 0;
    }
    
    
    //copy assignment
    Vector& operator=(const Vector& other)
    {
        if(this != &other)
        {
            delete[] data;
            length = other.length;
            data = new T[other.length];
            for (auto i=0; i<other.length; i++)
                data[i] = other.data[i];
        }
        return *this;
    }
    
    //move assignment
    Vector& operator=(Vector&& other)
    {
        if(this != &other)
        {
            delete[] data;
            length = other.length;
            data = other.data;
            other.length = 0;
            other.data = nullptr;
        }
        return *this;
    }
    
    Vector operator+(const Vector& other) const
    {
        if(length == other.length)
        {
            Vector v(length);
            for(auto i=0; i<length; i++)
                v.data[i] = data[i] + other.data[i];
            return v;
        }
        else
        {
            throw 0;
        }
    }
    
    Vector operator-(const Vector& other) const
    {
        if(length == other.length)
        {
            Vector v(length);
            for(auto i=0; i<length; i++)
                v.data[i] = data[i] - other.data[i];
            return v;
        }
        else
        {
            throw 0;
        }
    }
    
    T operator[](int i) const
    {
        return data[i];
    }
    
    
    // type deduction???
    template<typename S>
    Vector operator*=(const S& scalar) const
    {
            Vector v(length);
            for(auto i=0; i<length; i++)
                v.data[i] = data[i] * scalar;
            return v;
    }
    
    // right multiplication as member function
    template<typename S>
    Vector operator*(const S& scalar) const
    {
        // type deduction???
        return this *= scalar;
    }
    
private:
    int length;
    T *data;

};

//Vector left multiplication with scalar as non member function
//The lhs Vector is a copy and not a reference.
//This allows the compiler to make optimizations such as copy elision / move semantics.
template<typename T, typename S>
Vector<T> operator*(Vector<T> lhs, S const& scalar)
{
    return lhs *= scalar;
}

// DOT product
template<typename T>
T dot(const Vector<T>& l, const Vector<T>& r)
{
    if(l.length == r.length)
    {
        T result = 0;
        for(auto i=0; i,l.length; i++)
            // type deduction???
            result += l.data[i] * r.data[i];
        
        return result;
    }
}

template<typename T>
class Matrix
{
public:
    Matrix(int row, int col):
    row(row), col(col)
    {
        for(auto i=0; i<row; i++) {
            for(auto j=0; j<col; j++) {
                std::array<int, 2> index{{i,j}};
                elem[index] = 0;
            }
        }
    }
    
//    std::array<int, 2> elem(int i, int j);
//    {
//        return std::array<int, 2> elem;
//    }
//
//    T operator[](int i, int j)
//    {
//        return elem[{i,j}];
//    }
    
    template<typename V1, typename V2>
    Vector<V1> matvec(const Vector<V2>& rhs) const
    {
        if(rhs.length == col){
            Vector<V1> vec(row);
            for(auto i=0; i<row; i++){
                for(auto j=0; j<col; j++){
                    vec[i] += elem[{i,j}] * rhs[j];
                    }
                }
            return vec;
            }
    }
    
private:
    const int row;
    const int col;
    std::map<const std::array<int,2>, T> elem;
};

int main() {
    
    Vector<int> a(4);
    Vector<int> b = { 1, 2, 3, 4 };
    Vector<int> c;
    c = a + b;
    Matrix<double> M(2,4);
    M.matvec(b);
    
    
//    for(auto i=0; i<c.length; i++)
//        std::cout << c.data[i] << std::endl;
    
    return 0;
};
