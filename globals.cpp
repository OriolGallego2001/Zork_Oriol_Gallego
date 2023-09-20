#include "globals.h"


int globals::rollDice(const int dieType, const int quantity)
{
    int resutlt = 0;
    for (int i = 0; i++; i < quantity)
        resutlt += rand() % dieType + 1;
    return resutlt;
}
