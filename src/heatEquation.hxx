# include <initializer_list>
# include <memory>
# include <iostream>
# include <type_traits>
# include <exception>
# include <map>
# include <array>
# include <math.h>
# include <cmath>

using keytype = const std::array<int,2>; //
const double pi = 3.14159265358979323846;

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

    void print()
    {
        std::cout << "Vector datatype: " << typeid(this->data[0]).name() << std::endl;
        for(auto i=0; i<this->length; i++)
            std::cout << this->data[i] << ", ";
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
    Vector<decltype(scalar*vector[1])> newVector(vector.size());
    for(auto i=0; i<vector.size(); i++)
        newVector[i] = scalar*vector[i];
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
                dataMap[{{i,j}}] = (double) 0;
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
    
    void print()
    {
        auto it = this->dataMap.begin();
        std::cout << "Matrix datatype: " << typeid((*it).second).name() << std::endl;
        for(auto i=0; i<rows; i++){
            for(auto j=0; j<columns; j++){
                keytype index{{i,j}};
                auto it = this->dataMap.at(index);
                std::cout << it << ", ";
            }
            std::cout << std::endl;
        }
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
    Matrix<T> helperA = A;
    Vector<T> p_k(b - helperA.matvec(x)), p_kP1, r_k(p_k), r_kP1, x_k(x), x_kP1; // Add a const before x? IDEA: maybe x is not put as a constant in the interface on purpose. Maybe we can change the value of x for each iteration. That way, we don't have to return x, as it just modifies the 'x_0' given to the function.
    T alpha_k, beta_k;
    int k(0);
    
    while(dot(r_k, r_k)>tol*tol && k < maxiter - 1)
    {
        alpha_k = dot(r_k, r_k) / dot(helperA.matvec(p_k), p_k);
        x_kP1 = x_k + alpha_k * p_k;
        r_kP1 = r_k - alpha_k * helperA.matvec(p_k);
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

class Heat1D
{
    
public:
    
    Heat1D(const double alpha, const int m, const double dt)
    : M(m,m), m(m), alpha(alpha), dt(dt)
    {
        
        
        double sumDkij;
        double identity;
        
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<m; j++)
            {
                if(i==j)
                {
                    sumDkij = -2;
                    identity = 1;
                }
                if(abs(j-i)==1)
                {
                    sumDkij = 1;
                    identity = 0;
                }
                else
                {
                    sumDkij = 0;
                    identity = 0;
                }
                M[{{i,j}}] = identity + alpha*dt/pow((1/m+1),2)*sumDkij;
            }
        }
        
        for(int i = 0; i<m; i++)
            wStart[i] = sin(pi*(i/(m+i)));
    }
    
    // Methods
    
    Vector<double> exact(double t) const
    {
        return exp(-pow(pi,2)*alpha*t)*wStart;
    }
    
    Vector<double> solve(double t_end) const
    {
        Vector<double> w(wStart); // Initialize w with w at t=0
        int iterations;
        
        for(auto t = 0; t<t_end ; t += dt)
        {
            iterations = cg(M, w, w, 0.0001, 50);
        }
        if (iterations==-1) throw "Maximum number of iterations: did not find solution within the maximum tolerance (Conjugate Gradient)";
        
        return w;
    }
private:
    Matrix<double> M;
    int const m;
    double const alpha;
    double const dt;
    Vector<double> wStart;
    
};

class Heat2D {
    Heat1D(const double alpha, const int m, const double dt)
    : M(m,m), m(m), alpha(alpha), dt(dt)
    {
        Matrix<double> D(m,m);
        for(int i=0; i<m; i++)
        {
            M[{{i,i}}] = 1;
            D[{{i,i}}] = -2;
            
            // First Dimension
            int j = i+pow(m,0)
            
            if (floor(double(j)/(double)m) == floor(double(i)/(double)m))
            {
                D[{{i,j}] = 1;
                D[{{j,i}}] = 1;
            }
            
            // Second Dimension
            j = i + pow(m,1)
            
            if (j < pow(m,n))
            {
                D[{{i,j}] = 1;
                D[{{j,i}}] = 1;
            }
    
        M[{{i,j}}] = M[{{i,j}}] + alpha*dt/pow((1/m+1),2)*D[{{i,j}}];
        M[{{j,i}}] = M[{{i,j}}] + alpha*dt/pow((1/m+1),2)*D[{{i,j}}];
                
        
        }
        
        for(int i = 0; i<m; i++) {
            for(int j = 0; j<m; j++)
                wStart[i+j*m] = sin(pi*(i/(m+1)))*sin(pi*(j/(m+1)));
        }

        
    }
};
