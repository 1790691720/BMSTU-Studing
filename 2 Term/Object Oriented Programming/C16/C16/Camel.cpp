#include "Camel.h"

char Camel::isA()
{
	return 'C';
}

int Camel::attack(char* p) {
	if (deskout(p) > 0) {
		return 0;
	}
	int x = p[0] - _position[0];
	int y = p[1] - _position[1];
	if (x < 0) {
		x = -x;
	}
	if (y < 0) {
		y = -y;
	}
	if ((x + y) != 4 || x == y || x * y == 0) {
		return 0;
	}
	return 1;
}