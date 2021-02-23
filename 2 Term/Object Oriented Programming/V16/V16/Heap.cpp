#include "Heap.h"

Heap::Heap(int s) : size(s)
{
}

int Heap::get()
{
	return size;
}

void Heap::set(int s)
{
	size = s;
	return;
}
