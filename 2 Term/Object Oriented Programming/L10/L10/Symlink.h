#ifndef SYMLINK_H
#define SYMLINK_H

#include "Dlink.h"

class SymLink : public Dlink
{
private:
    unsigned char _sym;
public:
    SymLink(unsigned char ch) : Dlink(), _sym(ch) {};
    void print();
    unsigned char getsym() { return _sym; };
    SymLink* get_next() { return (SymLink*)Dlink::get_next(); };
    SymLink* get_prev() { return (SymLink*)Dlink::get_prev(); };
};



#endif //SYMLINK_H
