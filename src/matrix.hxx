#pragma once

using keytype = std::array<int, 2>;

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
    
//    void print()
//    {
//        auto it = this->dataMap.begin();
//        std::cout << "Matrix datatype: " << typeid((*it).second).name() << std::endl;
//        for(auto i=0; i<rows; i++){
//            for(auto j=0; j<columns; j++){
//                keytype index{{i,j}};
//                auto it = this->dataMap.at(index);
//                std::cout << it << ", ";
//            }
//            std::cout << std::endl;
//        }
//    }
    
    void print()
    {
        auto it = this->dataMap.begin();
        std::cout << "Matrix datatype: " << typeid((*it).second).name() << std::endl;
        auto iter = 0;
        for (auto& x: this->dataMap) {
            std::cout << x.second << ", ";
            if (iter!=0 & iter/this->rows == 0)
                std::cout << std::endl;
            iter++;
        }
        std::cout << std::endl;
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
	std::map <keytype, T> dataMap;
};
