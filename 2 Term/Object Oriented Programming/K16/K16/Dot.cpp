#include "Dot.h"

double Dot::getx()
{
	return _x;
}

double Dot::gety()
{
	return _y;
}

Dot::Dot(double x, double y) :_x(x), _y(y) {}

Dot::Dot()
{
	_x = 0;
	_y = 0;
}
