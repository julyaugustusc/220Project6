#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>
#include <iostream>
using namespace std;

enum studentType { undergrad = 0, grad };	// definition of studentType

class Student {

private:
	string name; // private local variables
	int rollNo;
	studentType level;

public:
	Student(string studentName, int studentRollNo, studentType studentLevel); // constructor

	// accessor methods
	string getName();
	int getRollNo();
	studentType getstudentType();
	virtual void displayInfo(){}

	// Q3a: Declare Friend Function changeRollNo()  (2 points)
	// Declare a friend function named changeRollNo() which has 2 parameters and no return value.
	// The first parameter is a pointer to Student class, and the second is an integer which is the new roll number.
	// Q3b will need you to define this function in main.cpp and 
	// Q3c will need you to call this function in case 'c' of executeAction() in main.cpp file
	friend Student changeRollNo(Student *ptrStudent, int newRollNo); // later declared in main

};

#endif // _STUDENT_H_#pragma once
