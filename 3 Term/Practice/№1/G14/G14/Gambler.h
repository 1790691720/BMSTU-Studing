#pragma once
#ifndef GAMBLERH
#define GAMBLERH

#include "Figure.h"
#include <iostream>
class Gambler
{
protected:
	Figure* _figure;
	const char* _name;
public:
	const char* getName();
	Gambler(Figure&);
	void query();
	virtual bool move() = 0;//True if all good, false if game is broken
};

#endif