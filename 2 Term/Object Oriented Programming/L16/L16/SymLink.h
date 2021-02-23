#pragma once
#ifndef SYMLINK
#define SYMLINK

#include "DualLink.h"
class SymLink : public DualLink
{
private:
	unsigned char _sym;
public:
	SymLink(unsigned char);

	unsigned char getSymbol();
	SymLink* getNext();
	SymLink* getPrev();
	SymLink* getHead();
	SymLink* getTail();
	void printList();
};

#endif