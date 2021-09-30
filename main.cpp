//CSE220 Project 6 Spring 2019
// Name: Augustus Crosby
// Programming environment used: VS 


// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of students.
// Each student has the corresponding information: name, roll number and student type.
// This information is stored as an object of Student class.
// The classes Undergrad and Grad are child classes of the Stduent class.
// When adding a new student, these child classes are used to make the student node of the list.

//
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// Do not modify given code.
//
// You can assume that all input is valid:
// Valid name:	String containing alphabetical letters
// Valid roll number: a positive integer

#include <iostream>
#include <fstream>
#include <string>
#include "Container.h"
#include "student.h"
#include "grad.h"
#include "undergrad.h"

using namespace std;

// forward declarations of functions already implemented:
void executeAction(char c);
Student* searchStudent(string name_input);


// forward declarations of functions that need implementation:
void addStudent(string name_input, int rollNo_input, studentType type);			// 10 points
void displayList();							// 10 points
void removeStudent(string name_input);		// 10 points
void deleteList();							// 10 points
void sort(Container **head);				// 10 points
void save(string fileName);					// 10 points
void load(string fileName);					// 10 points

Container* list = NULL;				// global list

int main()
{
	char c = 'i';				// initialized to a dummy value

	load("list.txt");			// During first execution, there will be no list.txt in source directory. list.txt is generated by save() while exiting the program.

	do {
		cout << "\nCSE220 Project 6\n";
		cout << "Choose an action:\n";
		cout << "\t a: add a new student\n";
		cout << "\t d: display list of students\n";
		cout << "\t c: change roll number of a student\n";
		cout << "\t r: remove a student\n";
		cout << "\t s: sort the list\n";
		cout << "\t q: quit\n";
		cin >> c;
		cin.ignore();
		executeAction(c);
	} while (c != 'q');

	save("list.txt");			// save the linked list to a file

	deleteList();				// delete the list before exiting the program

	return 0;
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	string name_input;
	int rollNo_input;
	int type_input = 2;
	studentType type;
	Student* studentFound = NULL;

	switch (c)
	{
	case 'a':	// add student
				// input student details from user
		cout << endl << "Enter student's name: ";
		getline(cin, name_input);
		cout << "Enter roll number: ";
		cin >> rollNo_input;
		cin.ignore();

		while (!(type_input == 0 || type_input == 1))
		{
			cout << endl << "Enter student type: " << endl;
			cout << "0. Undergrad " << endl;
			cout << "1. Grad" << endl;
			cin >> type_input;
			cin.ignore();
		}

		type = (studentType)type_input;

		// searchStudent() will return the student node if found, else returns NULL
		studentFound = searchStudent(name_input);
		if (studentFound == NULL)
		{
			addStudent(name_input, rollNo_input, type);
			cout << endl << "Student added to list!" << endl << endl;
		}
		else
			cout << endl << "Student already present in the list!" << endl << endl;

		break;

	case 'd':		// display the list
		displayList();
		break;

	case 'r':		// remove a student
		cout << endl << "Enter student's name: ";
		getline(cin, name_input);
		studentFound = searchStudent(name_input);
		if (studentFound != NULL)
		{
			removeStudent(name_input);
			cout << endl << "Student removed!" << endl << endl;
		}
		else
			cout << endl << "Student not present in the list!" << endl << endl;


		break;

	case 's':		// sort the list
		sort(&list);
		cout << endl << "List sorted!" << endl << endl;
		break;

	case 'c':		// change roll number
		cout << endl << "Enter student's name: ";
		getline(cin, name_input);
		// searchStudent() will return the student node if found, else returns NULL
		studentFound = searchStudent(name_input);
		if (studentFound == NULL)
		{
			cout << endl << "Student not in list!" << endl << endl;
		}
		else
		{
			// if student exists in the list, then ask user for new roll number
			cout << endl << "Enter new roll number: ";
			cin >> rollNo_input;
			cin.ignore();

			// Q3c Call changeRollNo() here   (2 points)
			// 'studentFound' contains the student whose roll number is to be changed.
			// 'rollNo_input' contains the new roll number of the student.
			// Call the function with appropriate function arguments.
			changeRollNo(studentFound, rollNo_input);

			cout << endl << "Roll number changed!" << endl << endl;
		}
		break;

	case 'q':		// quit
		break;

	default: cout << c << " is invalid input!\n";
	}

}

// No implementation needed here, however it may be helpful to review this function
Student* searchStudent(string name_input)
{

	Container* tempList = list;			// work on a copy of 'list'

	while (tempList != NULL)			// parse till end of list
	{
		if (tempList->student->getName() == name_input)
		{
			return tempList->student;	// return the student if found
		}

		tempList = tempList->next;		// parse the list
	}

	return NULL;						// return NULL if student not found in list
}

// Q3b: Define Friend Function changeRollNo()  (5 points)
// Define the function changeRollNo()that is declared in student.h
// This function sets the new roll number of the student. The student and new roll number is to be passed as function arguments.
// Use 'd' display option after using 'c' option to verify whether the new roll number is set.
// You will need to implement addStudent() and displayList() before you test this function.
Student changeRollNo(Student *student, int newRollNo) {
	student->rollNo= newRollNo;		//student is a pointer to the member in it "rollNo"
	return *student;				//returns a student pointer, points to which student it changed
};


// Q4: addStudent  (10 points)
// This function is used to add a new student to the global linked list 'list'. You may add the new student to head or tail of the list. (Sample solution adds to tail)
// New student can be either undergrad or grad. You will need to use the function argument ‘type’ to determine which constructor to use to create new student node.
// For example, if the user enters undergrad student, then you need to use Undergrad class and constructor to create new student node and add it to the list.
// NOTE: In executeAction(), searchStudent() is called before this function. Therefore no need to check here if the student exists in the list.
//       See how this fucntion is called in case 'a' of executeAction()

void addStudent(string name_input, int rollNo_input, studentType type)
{
	Container* tempList = list;				// work on a copy of 'list'
	Container *c = new Container();			// declare a pointer to a new Container object (NULL)

	//Update student
	if (type == 0) {
		c->student = new Undergrad(name_input, rollNo_input, type); //if undergrad (0) declare a new Undergrad object
	} //how would I delete this without deleting everything?
	else {
		c->student = new Grad(name_input, rollNo_input, type);		//if grad (1) declare a new Undergrad object
	}  //how would I delete this without deleting everything?


	if (tempList == NULL) {		//if the list is empty
		c->next = NULL;			//c->next is already pointing to null, but for clarity
		list = c;				//beginning is now c
	}

	if (tempList != NULL) {		//if the list is not empty

		while (tempList->next != NULL) {	//while there is a container following the one tempList is pointing to, go to the next container
			tempList = tempList->next;
		}

		c->next = NULL;			//c->next is already pointing to null, but for clarity
		tempList->next = c;		//the next is now c instead of null
	}
}
	


// Q5: displayList	(10 points)
// This function displays the list of student and their details (roll number, student type)
// Parse the list and use the class member function to display the student info.
// See expected output in the question file.
void displayList()
{
	Container *tempList = list;			// work on a copy of 'list'

	while (tempList != NULL) {			//while list not empty
		tempList->student->displayInfo(); //virtual overrides in both undergrad and grad to display proper info

		tempList = tempList->next;		// go to next
	}

}

// Q6: removeStudent (10 points)
// This function removes the student whose name is passed as parameter.
// Parse the list to locate the student and delete that node without memory leak. 
// Removing the node will cause the list to break into 2 pieces.
// You will need to stitch those peices. See the list in this way: ...node1->studentToRemove->node2->...
// Remove the 'studentToRemove' node and stitch node1 to node2 so that list becomes: ...node1->node2->...
// Hint: You will need to separately consider the case when the 'studentToRemove node' is at the head of the list
void removeStudent(string name_input)
{
	Container *tempList = list;			// work on a copy of 'list'
	Container* studentToRemove = NULL;			// lable studentToRemove as said in instructions

	if (list->student->getName() != name_input) {	//if it's not the first one in the list
		while (tempList->next->student->getName() != name_input) { //while it's not the one after the container pointer to by tempList
			tempList = tempList->next;				//move along LL
		}
		if (tempList->next->student->getName() == name_input) {	//if it's the next one,
			studentToRemove = tempList->next;			//label it the studentToRemove
			tempList->next = studentToRemove->next;		//node before studentToRemove now points to the node after student to remove
			studentToRemove->next = NULL;				//points to NULL instead of next node
			delete(studentToRemove->student);			//delete student object first
			delete(studentToRemove);					//delete the container after
		}
	}
	else {								// if the first in the list, it's special
		studentToRemove = tempList;		//label it
		list = studentToRemove->next;	//set the beginning to the one following it
		tempList = studentToRemove->next;	//set tempList forward too as to not have and pointers pointing to nothing incorrectly
		studentToRemove->next = NULL;	// set that pointer to NULL instead of next node
		delete(studentToRemove->student);			//delete student object first
		delete(studentToRemove);					//delete the container after
	}

}

// Q7: deleteList (10 points)
// This function deletes all the nodes of 'list'.
// Parse the list and delete the nodes one after another, without memory leak.
void deleteList()
{
	Container *tempList = list;			// work on a copy of 'list'
	Container* studentToRemove = NULL;			// lable studentToRemove (which is all but one at a time)

	while(tempList != NULL){		//while not empty
		studentToRemove = tempList;		//label toremove the one we're pointed to 
		tempList = tempList->next;	//move along
		studentToRemove->next = NULL;	//set the node to point to NULL
		delete(studentToRemove->student);			//delete student object first
		delete(studentToRemove);					//delete the container after
	}

	list = NULL;			//Update list
}

// Q8: sort() (10 points)
// This function sorts the list by student name alphabetically.
// You can create a new list of sorted students. In this case, you must delete the old list(garbage collection).
// You may look at books and websites for a suitable implementation of sorting and modify it as per the need of this program. 
// You must cite the book/website that you used.
// You may add function parameters and edit the declaration & function call of this function as per your implementation.

void sort(Container **head)
{
	//What I want to do is parse the list while comparing the first letter of every name, and finding the one that
	//comes first. Of course, if they start with the same letter I would need to go to the next letter and so on 
	//until it can decide, and remember no 2 name can be exactly alike. Which ever one came first would be added 
	//to the newList and removed from the old list. I would need to set the tempList pointing back at the start 
	//(where list points). This would happen until the list had only one name (because
	//it couldn't compare) and then the final name from the list would be added to the newList and then list
	//would be set to being newList.

	//I Looked at http://www.cplusplus.com/reference/string/string/compare/ to understand how to compare strings in c++


	Container *tempList = list;			// work on a copy of 'list'
	Container *newList = NULL;		//the beginning of newList (don't parse)
	Container *containerToBeAdded = NULL;	//the container to be added after comparing the names
	Container *containerBefore = NULL;		//the container before containerToeAdded
	Container *nlEnd = NULL;	//the last Node in newList

	string nameToBeAdded = "";
	string nameToCompare = "";
	while (list != NULL) {				//while list is not empty (remember: moving one at a time to other list)
		
		nameToBeAdded = tempList->student->getName();		//assign value at first so that it's not changed in the while loop
		containerToBeAdded = tempList;						//assign default value according to nameToBeAdded
		
		while (tempList->next != NULL) { //while has at another name to compare
			nameToCompare = tempList->next->student->getName();	//assign the next name to be the one compared

			//I ASSUME THAT NAMES WILL EITHER HAVE A SINGLE CAPITAL AT THE BEGINNING OF NAME(s) OR ZERO CONSISTANTLY 
			//ex. either "harry potter" and "bob" or "Harry Potter" and "Bob"
			if (nameToBeAdded.compare(nameToCompare) > 0) {	// if positive value, nameToCompare comes before nameToBeAdded
				nameToBeAdded = nameToCompare;			//update to that being the one to add
				containerToBeAdded = tempList->next;	//update the according containers
				containerBefore = tempList;
			}

			tempList = tempList->next; // parse to next container to compare
		}
		
		/*There is 4 possibilities here to account for:
		1. The containerToBeAdded is at the beginning of the list and newList is empty
		2. The containerToBeAdded is at the beginning of the list and newList is not empty
		3. The containerToBeAdded is not at the beginning of the list and newList is empty
		4. The containerToBeAdded is not at the beginning of the list and newList is not empty
		*/

		if (containerToBeAdded == list) { //if the container to be added is at the beginning of the list
			list = list->next;			//update list to be pointing to the following container

			if (newList == NULL) {		//if at beginning of newList
				newList = containerToBeAdded;	//newList and nlEnd point to that container now
				nlEnd = containerToBeAdded;		
			}
			else {
				nlEnd->next = containerToBeAdded; //else the next node is container to be added
				nlEnd = nlEnd->next;		// update nlEnd as it's now the container to be added
			}
			containerToBeAdded->next = NULL;	//set the end to be NULL
		}
		else {
			containerBefore->next = containerToBeAdded->next;	// update list, the container before now points to the one after the container added to the new list

			if (newList == NULL) {		//if at beginning of newList
				newList = containerToBeAdded;	//newList and nlEnd point to that container now
				nlEnd = containerToBeAdded;
			}
			else {
				nlEnd->next = containerToBeAdded;	//else the next node is container to be added
				nlEnd = nlEnd->next;		// update nlEnd as it's now the container to be added
			}
			containerToBeAdded->next = NULL;	//set the end to be NULL
		}

		tempList = list; // reset the templist pointer to the list pointer
	}

	list = newList; // once list is empty, point it to newList (now list)

}


// Q6: save  (10 points)
// Save the linked list of students to a file list.txt using ofstream.
// You will need to save the number of students in linked list. That will help in load() when reading the file.
// One format to store is:
// <no. of students>
// <Student1 name>
// <Student1 roll no.>
// <Student1 type>
// <Student2 name>
// <Student2 roll no.>
// <Student2 type>
// ...

// You may store the list in another format if you wish. You need to read the file in same way in load().
// This function is called when exiting the program (end of main() ).
// Hint: You may want to cast the enum ‘studentType’ to an int before writing it to the file.

void save(string fileName)
{
	Container *tempList = list;			// work on a copy of 'list'
	int numberOfStudents = 0;		//counter

	while (tempList != NULL) {		//while not empty
		numberOfStudents++;			//count up a student
		tempList = tempList->next;	// go to next
	}

	ofstream myfile;	//declare for saving files
	tempList = list;	//reset pointer to beginning of list for another parse
	myfile.open(fileName);	//declare filename
	myfile << numberOfStudents << endl;	//save the first digit

	while (tempList != NULL) {		//while not empty
		myfile << tempList->student->getName() << endl << tempList->student->getRollNo() << 
			endl << tempList->student->getstudentType() << endl; //save the name, rollNo, studentType
		tempList = tempList->next;	//go to next student to save
	}
	myfile.close();			//MUST CLOSE

	//Note: LL is deleted after closing, which is when this is used/saved

}

// Q7: load (7 points)`
// Load the linked list of students from the file using ifstream.
// You will need to create the linked list in the same order that is was saved to the file in save().
// First, read the number of students saved in the file.
// Then, for every student you will need to create a new node depending on student type. You may add the student to head or tail of the list. 
// Hint: If you casted the enum ‘studentType’ to an int, you will need to cast it back to ‘studentType’ when making the student node.
// This function is called at the beginning of main().

void load(string fileName)
{
	//Note: LL is loaded at the beginning of running
	int numberOfStudents; //declare to be used while loading
	string name;
	int rollNo;
	int type;

	ifstream myfile;		//declare for loading
	myfile.open(fileName);	//declare filename
	myfile >> numberOfStudents;		//load first number, which is number of students to tell you the for loop

	for (int i = 0; i < numberOfStudents; i++) {
		myfile >> name >> rollNo >> type;	//load the according 3 values

		addStudent(name, rollNo, (studentType)type); //addStudent into list, cast int to enum StudentType
	}

	myfile.close(); //MUST CLOSE


}
