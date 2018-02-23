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
																							// SHOULD ATTRIBUTES BE HIDDEN?
	public
	int length;
	T* data;

// default constructor
Vector()
	: data(nullptr),
	length(0)
{}

// constructor with length as argument
Vector(int length)
	: data(new T(length)),		//																IS THIS CORRECT?
	length(length)
{}

// Constructor using another vector as input
Vector(Vector other)
	: Vector(other.length)
{
	data = other.data;     // of data(new T(length)) met loop erach
}


// Constructor that takes an intialiser list representing the contents of this vector
Vector(std::initializer_list<T> list)
	: Vector((int)list.size())
{
	std::uninitialized_copy(list.begin(), list.end(), data);
}

// copy assignment
Vector& operator=(const Vector& other)
{
	if (this != &other)
	{
		delete[] data;
		length	= other.length;
		data = new T(other.length);
		for (auto i = 1; i<other.length; i++)
			data[i] = other.data[i]
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
		other.data = nullptr;							// WAT IS HIER DE JUISTE VOLGORDE?
		other.length = 0;
	}
	return *this;
}

// Sum operator																			MOET HIERBIJ HET ORIGINEEL HETZELFDE BLIJVEN?
Vector& operator+(const Vector& other)
{
	// Throw exception if the vectors have different length
	if (length != other.length) throw "Vectors have different size!";

	// Add two vectors
	for (auto i = 0; i<length; i++)													// WERKT DIT MET VERSCHILLENDE SOORTEN?
		data[i] += other.data[i];

	return *this;
}

// Subtraction operator
Vector& operator-(const Vector& other)
{
	// Throw exception if the vectors have different length
	if (length != other.length) throw "Vectors have different size!";

	// Add two vectors
	for (auto i = 0; i<length; i++)
		data[i] -= other.data[i];

	return *this;
}

// Right multiplication
Vector& operator*(const double scalar)
{
	for (auto i = 0; i < length; i++)
		data[i] = data[i] * scalar;
	
	return *this;
}

// Left multiplication

Vector& operator*(const Vector& other)
{
	
	Vector result(other.length)

	for (auto i = 0; i < length; i++)
		result.data[i] = other.data[i] * this;
	return *result;
}
// destructor
~Vector()
{
	delete[] data;
	length = 0;
}

};




int main()
{




return 0; 
}
