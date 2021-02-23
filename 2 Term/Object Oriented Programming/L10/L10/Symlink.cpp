#include "Symlink.h"
#include <cstdio>


void SymLink::print()
{
    SymLink* p = this;
    p = (SymLink*)p->_next;

    printf("Link:\n");
    while ((p->_next) != NULL)
    {
        printf("%c", p->_sym);
        p = (SymLink*)p->_next;
    }
    printf("\n");
}