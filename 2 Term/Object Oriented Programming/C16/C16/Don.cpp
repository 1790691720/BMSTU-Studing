#include "Don.h"

char Don::isA()
{
    return 'D';
}

int Don::attack(char* s) {
    if (Camel::attack(s) > 0)
        return 1;
    if (Alfil::attack(s) > 0)
        return 2;
    return 0;
}
