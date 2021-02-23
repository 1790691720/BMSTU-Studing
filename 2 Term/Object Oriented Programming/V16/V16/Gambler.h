#pragma once
#ifndef GAMBLERH
#define GAMBLERH

#include "Heap.h"
#include <iostream>
class Gambler
{
protected:
	Heap* heap;
	const int limit; //Max input
	const char* name;
public:
	Gambler(Heap&, int);
	void query();
	virtual bool move() = 0;//True if all good, false if game is broken
	virtual ~Gambler();
};

#endif