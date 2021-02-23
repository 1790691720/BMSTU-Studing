#pragma once
#ifndef ALFILH
#define ALFILH
#include "Figure.h"
class Alfil : virtual public Figure
{
public:
    Alfil(const char* p) : Figure(p) {};
    char isA();
    int attack(char*);
};

#endif
