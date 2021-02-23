#include "Gambler.h"

Gambler::Gambler(Heap& h, int l) :limit(l)
{
	heap = &h;
}

void Gambler::query()
{
	std::cout << "Heap=" << heap->get() << ". " << name << " > ";
	return;
}

Gambler::~Gambler()
{
}
