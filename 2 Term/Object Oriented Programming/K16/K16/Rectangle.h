#pragma once
#ifndef RECTANGLEH
#define RECTANGLEH

#include "Dot.h"
class Triangle
{
private:
	Dot point[3];

public:
	Triangle();
	Triangle(Dot A, Dot B, Dot C);
	double calcRadius();
	double calcLine(int, int);

};

#endif 