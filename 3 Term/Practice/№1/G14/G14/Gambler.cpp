#include "Gambler.h"

const char* Gambler::getName()
{
	return _name;
}

Gambler::Gambler(Figure& f)
{
	_figure = &f;
}
void Gambler::query()
{
	std::cout << _name <<": "<< (*_figure)<<"-"<<_figure->isA();
	return;
}