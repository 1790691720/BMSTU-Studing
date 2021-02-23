#include "SymLink.h"
#include <iostream>
SymLink::SymLink(unsigned char c): DualLink(), _sym(c) {}
unsigned char SymLink::getSymbol()
{
	return _sym;
}
SymLink* SymLink::getNext()
{
	return (SymLink*)DualLink::getNext();
}

SymLink* SymLink::getPrev()
{
	return (SymLink*)DualLink::getPrev();
}

SymLink* SymLink::getHead()
{
	return (SymLink*)DualLink::getHead();
}

SymLink* SymLink::getTail()
{
	return (SymLink*)DualLink::getTail();
}

void SymLink::printList()
{
	SymLink* p = getHead();
	while (p->_next != NULL)
	{
		std::cout << p->_sym;
		p = p->getNext();
	}
	std::cout << std::endl;
	return;
}