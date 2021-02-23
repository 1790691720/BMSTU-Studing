#include "Pen.h"

Pen::Pen(Heap& h, int l, const char* n) :Gambler(h, l)
{
	name = n;
}

bool Pen::move()
{
	int m;
	for (m = 1; m <= limit; m++)
		if ((heap->get() - m) % (limit + 1) == 0)
		{
			heap->set(heap->get() - m);
			std::cout << m << std::endl;
			return true;
		}
	heap->set(heap->get() - limit);
	std::cout << limit << std::endl;
	return true;
}