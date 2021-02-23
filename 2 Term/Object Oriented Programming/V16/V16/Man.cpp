#include "Man.h"

Man::Man(Heap& h, int l, const char* n) :Gambler(h, l)
{
	name = n;
}

bool Man::move()
{
	int m;
	std::cin >> m;
	if (m<1 || m>limit || m > heap->get() || std::cin.fail())
		return false;

	heap->set((heap->get() - m));
	return true;
}
