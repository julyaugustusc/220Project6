#ifndef _GRAD_H_
#define _GRAD_H_

#include "student.h"

// Q1b: Create Grad class (5 points)
// Part 1: Create a child class of the Student class named 'Grad'
class Grad : public Student {
public:
	// Part2: Declare constructor which accepts the same 3 parameters as the parent class Student's constructor.
	// Pass the 3 parameters to the super constructor of the Student class.
	Grad(string studentName, int studentRollNo, studentType studentLevel) : Student(studentName,
		studentRollNo, studentLevel){} //":" passes it to super class Student

	// Part 3: Re-declare the method displayInfo (virtual method found inside of parent class Student)
	void displayInfo(); //declared in grad.cpp
};


#endif // _GRAD_H_#pragma once
