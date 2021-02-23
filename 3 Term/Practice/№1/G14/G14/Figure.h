
#ifndef FIGUREH
#define FIGUREH
#include <iostream>
#include <string.h>
class Figure
{
protected:
	char _position[2];
public:
	Figure(const char*);//Construcor with string-position
	Figure();

	char getPosAlp();
	char getPosNum();

	char isA();//will return what is figure
	int attack(char*);
	static int deskout(char*);
	void printBoard();
	Figure& operator=(char*);
	int operator!=(char*);
	int operator==(char*);
	friend std::ostream& operator<<(std::ostream&, Figure&);
};

#endif 