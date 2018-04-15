# include <initializer_list>
# include <memory>
# include <iostream>
# include <type_traits>
# include <exception>
# include <map>
# include <array>

using keytype = const std::array<int,2>; //

template<typename T>
class Vector {
public:
    Vector()
    : data(nullptr), length(0) {}
    
    Vector(int length)
    : data(new T[length]), length(length) {}
    
    Vector(const Vector<T>& vector)
    : Vector(vector.length)
    {
        for(int i = 0; i<length; i++)
            data[i] = vector.data[i];
    }
    
    Vector(std::initializer_list<T> list)
    : Vector(list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), data);
    }
    
    ~Vector()
    {
        length = 0;
        data = nullptr;
        delete[] data;
    }
    
    auto operator[](const int i) const
    {
        return data[i];
    }
    
    auto & operator[](const int i)
    {
        return data[i];
    }
    
    Vector<T> & operator=(const Vector<T>& other)
    {
        delete[] data;
        length = other.size();
        data = new T[other.length];
        for(auto i = 0; i < other.length; i++)
            data[i] = other[i];
        return* this;
    }
    
    Vector<T> operator=(Vector<T>&& other)
    {
        delete[] data;
        length = other.size();
        data = new T[other.size()];
        for(auto i = 0; i < other.length; i++)
            data[i] = other[i];
        other.data = nullptr;
        delete[] other.data;
        other.length = 0;
        return *this;
    }
    
    // Not completely sure on the throw in this operation
    template<typename U>
    auto operator+(const Vector<U> &other) const
    {
        if(length != other.length)
            throw "Vectors are of different size";
        else {
            Vector<decltype(data[1] + other[1])> newVector(length);
            for(auto i=0; i<length; i++)
                newVector[i] = data[i]+other[i];
            return newVector;
        }
        
    }
    
    template<typename U>
    auto operator-(const Vector<U> other) const
    {
        Vector<decltype(data[1] - other[1])> newVector(length);
        for(auto i=0; i<length; i++)
            newVector[i] = data[i]-other[i];
        return newVector;
    }
    
    template<typename S>
    auto operator*(const S scalar) const
    {
        Vector<decltype(scalar*data[1])> newVector(length);
        for(auto i=0; i<length; i++)
            newVector[i] = scalar*data[i];
        return newVector;
    }
    
    
    int size() const
    {
        return length;
    }
    
    // Methods
    void print()
    {
        std::cout << "Vector content: ";
        for (auto i=0; i<length; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    
private:
    
    T* data;
    int length;
    
};

// Specialisation of the left multiplication with a scalar
template<typename T, typename S>
auto operator*(const S scalar, const Vector<T> vector)
{
    Vector<decltype(scalar*vector.data[1])> newVector(vector.length);
    for(auto i=0; i<vector.length; i++)
        newVector.data[i] = scalar*vector.data[i];
    return newVector;
}

template<typename T>
class Matrix
{
public:
    Matrix(int rows, int columns)
    : rows(rows), columns(columns)
    {
        for(auto i=0; i<rows; i++)
        {
            for(auto j=0; j<columns; j++)
            {
                dataMap[{{i,j}}] = 0;
            }
        }
    };
    
    ~Matrix()
    {
        
    }
    
    auto & operator [](const keytype key)
    {
        return dataMap[key];
    }
    
    // methods
    auto matvec(const Vector<T> & vector)
    {
        if(columns != vector.size())
            throw "Matrix and vector are not in the same space";
        else
        {
            Vector<T> newVector(vector.size());
            for(auto i=0; i<rows; i++)
            {
                newVector[i] = 0;
                for(auto j=0; j<columns; j++)
                {
                    newVector[i] += dataMap[{{i,j}}]*vector[j];
                }
            }
            return newVector;
        }
    }
    
private:
    int const rows;
    int const columns;
    std::map<keytype, T> dataMap;
};

class Heat1D
{
    Heat1D(const double alpha, const int m, const double dt)
    : M(m,1)
    {
        
    }
    
private:
    Matrix<double> M;
};

// Functions

// Why not return a common type?
template<typename T>
T dot(const Vector<T>& l, const Vector<T>& r)
{
    T dotproduct(0);
    for(auto i=0; i<l.size(); i++)
        dotproduct += l[i]*r[i];
    return dotproduct;
}

// Conjugate Gradient Function
template<typename T>
int cg(const Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxiter)
{
    Vector<T> p_k(b - A.matvec(x)), p_kP1, r_k(p_k), r_kP1, x_k(x), x_kP1; // Add a const before x? IDEA: maybe x is not put as a constant in the interface on purpose. Maybe we can change the value of x for each iteration. That way, we don't have to return x, as it just modifies the 'x_0' given to the function.
    T alpha_k, beta_k;
    int k(0);
    
    while(dot(r_k, r_k)>tol*tol && k < maxiter - 1)
    {
        alpha_k = dot(r_k, r_k) / dot(A.matvec(p_k), p_k);
        x_kP1 = x_k + alpha_k * p_k;
        r_kP1 = r_k - alpha_k * A.matvec(p_k);
        beta_k = dot(r_kP1, r_kP1) / dot(r_k, r_k);
        p_kP1 = r_kP1 + beta_k * p_k;

        // And now... the mess
        x_k = x_kP1;
        r_k = r_kP1;
        p_k = p_kP1;
        
        // Would be possible to eliminate x_k, p_kP1
//        alpha = dot(r_k, r_k) / dot(A.matvec(p_k), p_k);
//        x = x + alpha * p;
//        r_kP1 = r_k - alpha * A.matvec(p);
//        beta = dot(r_kP1, r_kP1) / dot(r_k, r_k);
//        p = r_kP1 + beta * p;
//        r_k = r_kP1;
        
        k++;
    }
    
    return (k < maxiter-1) ? k+1 : -1;
    
}


int main()
{
    Vector<double> a(6);
    Vector<double> b = {1, 2};
    Vector<double> c = {1, 2};
    Vector<double> checkMove = {1, 2};
    
    b = std::move(checkMove);
    int dotCheck = dot(b,c);
    
    std::cout << dotCheck << std::endl;
    
    // See if we can construct the matrix.
    Matrix<double> M(2,2);
    M[{{0,0}}] = 1;
    M[{{0,1}}] = 0;
    M[{{1,0}}] = 0;
    M[{{1,1}}] = 1;
    
    std::cout << M.matvec(b)[1] << std::endl;
    
    // Add entries as:
    // M[{0,0}] = 1.0;
    
    std::map<keytype, int> firstMap;
    
    
    firstMap[{{0,0}}] = 1;
    firstMap[{{1,0}}] = 0;
    firstMap[{{2,0}}] = 0;
    
    
    
    //firstMap.insert(std::pair<std::array<int,2>, int> (key1, 5));
    
    
    return 0;
}

