#pragma once
#ifndef DONH
#define DONH
#include "Figure.h"
#include "Camel.h"
#include "Alfil.h"

class Don : public Camel, public Alfil
{
public:
    Don(const char* p) : Camel(p), Alfil(p), Figure(p) {};
    char isA();
    int attack(char*);
};

#endif