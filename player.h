#pragma once
#include "creature.h"
#include "room.h"
#include "item.h"
class player :
    public creature
{
public:
    player(const char* name, const char* description, room* r);
    void look();
    void pick(std::string item_name);
    void drop(std::string item_name);
    void build(std::string item_name);
private:
    int capacity;

};

