#pragma once
#ifndef DOTH
#define DOTH


#include <iostream>
using namespace std;
class Dot
{
	friend class Triangle;

private:
	double _x;
	double _y;
public:
	double getx();
	double gety();
	Dot(double, double);
	Dot();
};

#endif 