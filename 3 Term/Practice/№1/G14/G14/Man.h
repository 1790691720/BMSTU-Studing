#pragma once
#ifndef MANH
#define MANH

#include "Gambler.h"
#include <iostream>
class Man : public Gambler
{
public:
	Man(Figure&, const char*);
	virtual bool move();
};

#endif