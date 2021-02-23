#include "DualLink.h"

DualLink::DualLink()
{
	_next = NULL;
	_prev = NULL;
}

void DualLink::exception()
{
	if (_next != NULL)
		_next->_prev = _prev;
	if (_prev != NULL)
		_prev->_next = _next;

	return;
}

void DualLink::insertAfter(DualLink* q)
{
	q->_next = _next;
	q->_prev = this;
	if (_next != NULL)
		_next->_prev = q;
	_next = q;
}

void DualLink::insertBefore(DualLink* q)
{
	q->_next = this;
	q->_prev = _prev;
	if (_prev != NULL) {
		_prev->_next = q;
	}
	_prev = q;
}

DualLink* DualLink::getNext()
{
	return _next;
}

DualLink* DualLink::getPrev()
{
	return _prev;
}

DualLink* DualLink::getHead()
{
	DualLink* p = this;
	DualLink* q = this;
	while (p != NULL)
	{
		q = p;
		p = p->_prev;
	}
	return q;
}

DualLink* DualLink::getTail()
{
	DualLink* p = this;
	while ((p->_next) != NULL)
		p = p->_next;
	return p;
}

int DualLink::count()
{
	DualLink* p = getHead();
	int n = 0;
	while (p->_next != NULL)
	{
		n++;
		p = p->_next;
	}
	return n;

}
