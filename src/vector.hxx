#pragma once
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

// Why not return a common type?
template<typename T>
T dot(const Vector<T>& l, const Vector<T>& r)
{
    T dotproduct(0);
    for(auto i=0; i<l.size(); i++)
        dotproduct += l[i]*r[i];
    return dotproduct;
}