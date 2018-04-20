#pragma once
template<typename T>
class Vector {
public:
    //Default constructor
    Vector()
    : data(nullptr), length(0) {}
    
    //Length contsructor
    Vector(int length)
    : data(new T[length]), length(length) {}
    
    //Copy constructor
    Vector(const Vector<T>& vector)
    : Vector(vector.length)
    {
        for(int i = 0; i<length; i++)
            data[i] = vector.data[i];
    }
    
    //List constructor
    Vector(std::initializer_list<T> list)
    : Vector(list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), data);
    }
    
    //Destructor
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
    
    //Copy assignment
    Vector<T> & operator=(const Vector<T>& other)
    {
        delete[] data;
        length = other.size();
        data = new T[other.length];
        for(auto i = 0; i < other.length; i++)
            data[i] = other[i];
        return *this;
    }
    
    //Move assignment
    Vector<T> & operator=(Vector<T>&& other)
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
    
    template<typename U>
    auto operator+(const Vector<U> &other) const
    {
        if(length != other.length)
            throw "Addition: Vectors are of different size";
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
        if(length != other.length)
            throw "Substraction: Vectors are of different size";
        else {
        Vector<decltype(data[1] - other[1])> newVector(length);
        for(auto i=0; i<length; i++)
            newVector[i] = data[i]-other[i];
        return newVector;
        }
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
        std::printf("Vector datatype: %s \n", typeid(data[0]).name());
        std::printf("Vector length: %u \n", length);
        for(auto i=0; i<length; i++)
            std::printf("% 6.4f, ", data[i]);
        std::printf("\n\n");
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

template<typename T, typename S>
auto dot(const Vector<T>& l, const Vector<S>& r)
{
    if(l.size() != r.size()){
        throw "Vectors are of different size";}
    else{
        decltype(l[0]*r[0]) dotproduct(0);
        for(auto i=0; i<l.size(); i++)
            dotproduct += l[i]*r[i];
        return dotproduct;}
}
