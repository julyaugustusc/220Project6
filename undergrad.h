#ifndef _UNDERGRAD_H
#define _UNDERGRAD_H

#include "student.h"

// Q1b: Create Undergrad class (5 points)
// Part 1: Create a child class of the Student class named 'undergrad'
class Undergrad : public Student {
public:
	// Part2: Declare constructor which accepts the same 3 parameters as the parent class Student's constructor.
	// Pass the 3 parameters to the super constructor of the Student class.
	Undergrad(string studentName, int studentRollNo, studentType studentLevel) : Student(studentName,
		studentRollNo, studentLevel) {} //":" passes it to super class Student

	// Part 3: Re-declare the method displayInfo (virtual method found inside of parent class Student)
	void displayInfo(); //declared in undergrad.cpp
};

#endif // _UNDERGRAD_H#pragma once
