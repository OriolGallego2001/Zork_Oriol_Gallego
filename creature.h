#pragma once
#include "entity.h"
#include "room.h"
class creature :
    public entity
{
public:
    creature(const char* name, const char* description, room* r);
    room* get_room();
    void move(std::string direction);
    bool check_dragon(std::string direction);
private:
    room* location;

};

