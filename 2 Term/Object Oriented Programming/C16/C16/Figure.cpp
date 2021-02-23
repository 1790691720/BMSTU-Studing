#include "Figure.h"


Figure::Figure(const char* inp)
{
	_position[0] = inp[0];
	_position[1] = inp[1];
}

Figure::Figure()
{
}

int Figure::deskout(char* pos)
{
	if(strlen(pos)==2)
		return (pos[0] > 'h') || (pos[0] < 'a') || (pos[1] < '1') || (pos[1] > '8');
	return 1;
}

void Figure::printBoard()
{
	char s[3];
	s[2] = '\0';
	const char* mark = ".+x";
	std::cout << "  a b c d e f g h\n";
	for (int i = 8; i > 0; i--) {
		std::cout << i << ' ';
		s[1] = '0' + i;
		for (int j = 0; j < 8; j++) {
			s[0] = 'a' + j;
			char m = (*this != s) ? mark[attack(s)] : isA();
			std::cout << m << ' ';
		}
		std::cout << i << "\n";
	}
	std::cout << "  a b c d e f g h\n";
}

Figure& Figure::operator=(char* p)
{
	_position[0] = p[0];
	_position[1] = p[1];
	return *this;
}

int Figure::operator!=(char* p)
{
	return (_position[0] != p[0]) || (_position[1] != p[1]);

}

int Figure::operator==(char* p)
{
	return((_position[0] == p[0]) && (_position[1] == p[1]));
}

std::ostream& operator<<(std::ostream& out, Figure& f)
{
	return out << f.isA() << f._position[0] << f._position[1];
}

std::istream& operator>>(std::istream& in, Figure& f)
{
	char s[3];
	std::cin.unsetf(std::ios::skipws);
	in >> s[0] >> s[1];
	s[2] = '\0';
	in.ignore(64, '\n');
	if (Figure::deskout(s) || (f.attack(s) == 0) || f == s)
		in.setstate(std::ios::failbit);
	f = s;
	return in;
}
