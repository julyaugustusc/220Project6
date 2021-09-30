#include "grad.h"
#include <iostream>

// Q2b: Define displayInfo() (5 points)
// Define the function displayInfo() for Grad class.
// See expected output in question file.

// (displayList() function in main.cpp can call this function.)
// Include necessary header files
void Grad::displayInfo() {
	cout << "Grad student: " << getName() << "\nRoll number: " << getRollNo() << "\n" << endl;
}



