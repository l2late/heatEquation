#include <stdio.h>
#include <iostream>
#include <initializer_list>
#include <map>
#include <array>
#include <exception>
# include <memory>
# include <type_traits>

using keytype = const std::array<int,2>;

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
                data[i] = other[i];
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
            delete[] other.data;
        }
        return *this;
    }
    
    Vector operator+(const Vector& other) const
    {
        if(length == other.length)
        {
            Vector<decltype(data[1] + other[1])> v(length);
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
            Vector<decltype(data[1] - other[1])> v(length);
            for(auto i=0; i<length; i++)
                v.data[i] = data[i] - other[i];
            return v;
        }
        else
        {
            throw 0;
        }
    }
    
    T operator[](const int i) const
    {
        return data[i];
    }
    
    T & operator[](const int i)
    {
        return data[i];
    }
    
    // type deduction???
    template<typename S>
    Vector operator*=(const S& scalar) const
    {
            Vector<decltype(data[1]*scalar)> v(length);
            for(auto i=0; i<length; i++)
                v[i] = data[i] * scalar;
            return v;
    }
    
    // right multiplication as member function
    template<typename S>
    Vector operator*(const S& scalar) const
    {
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
auto operator*(const S scalar, const Vector<T> rhs)
{
    Vector<decltype(scalar*rhs[0])> vec;
    return rhs *= scalar;
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
            result += l[i] * r[i];
        
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
                keytype index{{i,j}};
                elem[index] = 0;
            }
        }
    }
    
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
    std::map<keytype, T> elem;
};

int main() {
    
    Vector<int> a(4);
    Vector<int> b = { 1, 2, 3, 4 };
    Vector<int> c;
    c = a + b;
    Matrix<double> M(2,4);
    //M.matvec(b);
    
    
//    for(auto i=0; i<c.length; i++)
//        std::cout << c.data[i] << std::endl;
    
    return 0;
};
