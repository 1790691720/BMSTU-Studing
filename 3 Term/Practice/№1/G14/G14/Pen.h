#pragma once
#ifndef PENH
#define PENH

#include "Gambler.h"
class Pen : public Gambler
{
public:
	Pen(Figure&, const char*);
	virtual bool move();
};

#endif