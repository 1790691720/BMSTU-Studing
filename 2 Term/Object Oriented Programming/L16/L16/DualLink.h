#pragma once
#ifndef DUALLINK
#define DUALLINK

#include <cstdio>

// Dlink class
class DualLink {
protected:
	DualLink* _next;
	DualLink* _prev;
public:
	DualLink();						//Init list
	void exception();				//Except element
	void insertAfter(DualLink*);	//insert after current
	void insertBefore(DualLink*);	//insert before current
	DualLink* getNext();			//Get next element
	DualLink* getPrev();			//Get prev
	DualLink* getHead();			// Get head of list
	DualLink* getTail();			// Get taif of list
	int count();
};

#endif
