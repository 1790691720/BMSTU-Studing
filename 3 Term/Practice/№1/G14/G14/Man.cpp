#include "Man.h"

Man::Man(Figure& f,const char* n) :Gambler(f)
{
	_name = n;
}

bool Man::move()
{
	char s[3];
	std::cin.unsetf(std::ios::skipws);
	std::cin >> s[0] >> s[1];
	s[2] = '\0';
	std::cin.ignore(64, '\n');
	if (Figure::deskout(s) || (_figure->attack(s) == 0) || (*_figure) == s)
		return false;
	(*_figure) = s;
	return true;
}
