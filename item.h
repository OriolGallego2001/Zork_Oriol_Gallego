#pragma once
#include "entity.h"


class item : 
    public entity
{
public:
    item(const char* name, const char* description, int size);
    int size;
};

