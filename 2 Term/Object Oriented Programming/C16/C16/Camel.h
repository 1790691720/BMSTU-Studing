#pragma once
#ifndef CAMELH
#define CAMELH
#include "Figure.h"
class Camel : virtual public Figure
{
public:
    Camel(const char* p) : Figure(p) {};
    char isA();
    int attack(char*);
};

#endif