#include "student.h"

Student::Student(string studentName, int studentRollNo, studentType type)
{
	name = studentName;
	rollNo = studentRollNo;
	level = type;
}

string Student::getName()
{
	return name;
}

int Student::getRollNo()
{
	return rollNo;
}

studentType Student::getstudentType()
{
	return level;
}