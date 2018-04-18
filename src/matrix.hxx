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
        dataMap.clear();
    };
    
    auto & operator [](const keytype key)
    {
        return dataMap[key];
    }
    
    void print()
    {
        auto it = dataMap.begin();
        std::printf("Matrix datatype: %s\n", typeid((*it).second).name());
        std::printf("Matrix size: %ux%u\n", rows,columns);
        std::printf("DataMap size: %u\n", dataMap.size());
        auto iter = 1;
        for (auto& x: dataMap) {
            std::printf("% 6.4f , ", x.second);
            if (iter!=1 & iter % rows == 0) // next line after end of row
                std::printf("\n");
            iter++;
        }
        std::printf("\n");
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
