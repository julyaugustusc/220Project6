#include "undergrad.h"
#include <iostream>

// Q2a: Define displayInfo() (5 points)
// Define the function displayInfo() for Grad class.
// See expected output in question file.

// (displayList() function in main.cpp can call this function.)
// Include necessary header files
void Undergrad::displayInfo() {
	cout << "Undergrad student: " << getName() << "\nRoll number: " << getRollNo() << "\n" << endl;
}