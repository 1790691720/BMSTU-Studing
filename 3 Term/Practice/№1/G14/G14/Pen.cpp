#include "Pen.h"

Pen::Pen(Figure& f, const char* n) :Gambler(f)
{
	_name = n;
}

bool Pen::move()
{
	static char s[3];
	s[0] = _figure->getPosAlp();
	s[1] = _figure->getPosNum();
	s[2] = '\0';
	if (s[1] - '1' < s[0] - 'a')
		s[1] = s[1] + ((s[0] - 'a') - (s[1] - '0')) + 1;
	else
		s[0] = s[0] - ((s[0] - 'a') - (s[1] - '0')) - 1;
	(*_figure) = s;
	std::cout << s;
	std::cin.ignore(64,'\n');
	return true;
}