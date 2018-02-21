/**
 * \file swap.cxx
 *
 * This file is part of the course tw3720tu:
 * Object Oriented Scientific Programming with C++
 *
 */

// Include header file for standard input/output stream library
#include <iostream>

void SwapByReference(int & a, int & b)
{
	int c = a;
	a = b;
	b = c;
}

void SwapByAddress(int * a, int * b)
{
	int  c = *a;
	*a = *b;
	*b = c; 

}

// The global main function that is the designated start of the program
int main(){

    // Read two integer values
    int i1; std::cin >> i1;
	int i2; std::cin >> i2;
	
	std::cout << "begin value of: i1 = " << i1 << ", i2 = " << i2  << std::endl;
	
	/** Values of i1 and i2 cannot be swapped when passing arguments BY VALUE.
	Therefore, no function is writen for this assignment*/

	/**Pass by reference*/
	SwapByReference(i1, i2);
	std::cout << "Value after swap by reference: i1 = " << i1 << ", i2 = " << i2 << std::endl;

	/**Pass by adress*/
	SwapByAddress(&i1, &i2);
	std::cout << "Value after swap by address: i1 = " << i1 << ", i2 = " << i2 << std::endl;
    

    // Return code 0 to the operating system (=no error)
    return 0;
}
/** Results when run

3
5
begin value of: i1 = 3, i2 = 5
Value after swap by reference: i1 = 5, i2 = 3
Value after swap by address: i1 = 3, i2 = 5

*/