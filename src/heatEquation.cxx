/**
 * \file Final-project.cxx
 *
 * This file is the basis for the final project for Object Oriented Scientific Programming in C++
 *
 */

// Include header file for standard input/output stream library
#include <cmath>
#include <ostream>
#include <iomanip>
#include <exception>
#include <initializer_list>


// The global main function that is the designated start of the program
template<typename T> 
class Vector 
{	
	public
	int length;
	T* data;

// default constructor
Vector()
	: data(nullptr),
	length(0)
{
	std::clog << "Default constructor called" << std::endl;
}

// constructor with length as argument
Vector(int length)
	: data(new T[length]),		
	length(length)
{
	std::clog << "Constructor with length argument called" << std::endl;
}

// Constructor using another vector as input
Vector(Vector other)
	: Vector(other.length)
{
	data = other.data;						//  WELKE IS BETER? of data(new T(length)) met loop erach
	std::clog << "Copy constructor called" << std::endl;
}


// Constructor that takes an intialiser list representing the contents of this vector
Vector(std::initializer_list<T> list)
	: Vector(list.size())
{
	std::uninitialized_copy(list.begin(), list.end(), data);
	std::clog << "Constructor(std::initializer_list<double> list) called" << std::endl;
}

// copy assignment							// DO YOU NEED TO TEMPLATE THE INPUT?
Vector& operator=(const Vector& other)
{
	if (this != &other)
	{
		delete[] data;
		length	= other.length;
		data = new T(other.length);
		for (auto i = 1; i<other.length; i++)
			data[i] = other.data[i]
			std::clog << "Copy assignment called" << std::endl;
	}
	return *this
}


// Move assignment																				HOW DO YOU KNOW DIFFERENCE?
Vector& operator=(Vector&& other)
{
	if (this != &other)
	{
		delete[] data;
		length = other.length;
		data = other.data;
		other.data = nullptr;														// WAT IS HIER DE JUISTE VOLGORDE?
		other.length = 0;
		std::clog << "Move assignment called" << std::endl;
	}
	return *this;
}

// Sum operator																			MOET HIERBIJ HET ORIGINEEL HETZELFDE BLIJVEN?
template<typename U>
Vector& operator+(const Vector<U>& other) const
{
	// Throw exception if the vectors have different length
	if (length != other.length) throw "Vectors have different size!";
	
	else {
	// Add two vectors
		Vector<decltype(data[1] + other.data[1])> newVector(length);
		for (auto i = 0; i<length; i++)													// WERKT DIT MET VERSCHILLENDE SOORTEN?
			newVector = data[i] + other.data[i];
		return *newVector;
	}
}

// Subtraction operator
template<typename U>
Vector& operator-(const Vector<U>& other) const
{
	// Throw exception if the vectors have different length
	if (length != other.length) throw "Vectors have different size!";

	else {
		// Add two vectors
		Vector<decltype(data[1] + other.data[1])> newVector(length);
		for (auto i = 0; i < length; i++)													// WERKT DIT MET VERSCHILLENDE SOORTEN?
			newVector = data[i] - other.data[i];
		return *newVector;
	}
}

// Right multiplication
template<typename U>
Vector& operator*(const U scalar) const
{
	Vector<decltype(data[1] * scalar)> newVector(length);
	for (auto i = 0; i < length; i++)
		newVector[i] = data[i] * scalar;
	return *newVector;
}

//



// destructor
~Vector()
{
	delete[] data;
	length = 0;
}

};


// Left multiplication of vector
template<typename T>
Vector& operator*(const T Vect)
{
	Vector<decltype(this*Vect[1])> newVector(length);
	for (auto i = 0; i<length; i++)
		newVector[i] = this*Vect[i];
	return *newVector;
}



template<typename T, typename U>
auto dot(const Vector<T>& l, const Vector<U>& r)
{
	if (length != other.length) throw "Vectors have different size!";
	else {
		auto dotproduct = l[1] + r[1];
		for i = 1; i < l.size(); i++;
		dotproduct += l[i] * r[i];
		return dotproduct;
	}
}

int main()
{
	//default constructor
	Vector<double> a;
	// length input;
	Vector<int> b(5);
	// list input
	Vector<double> c = { 1,2,3,4 };
	// vector input
	







return 0; 
}
