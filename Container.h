#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "student.h"

class Container {
public:
	Student *student;
	Container *next;
	Container();			// constructor
};

#endif // _CONTAINER_H_#pragma once
