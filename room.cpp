#include "room.h"

room::room(const char* name, const char* description) : entity(EntityType::Room, name, description) {
    exits = std::map<std::string, room*>();
}

room* room::get_exit(std::string direction)
{
    if (exits.find(direction) == exits.end()) {
        return NULL;
    } 
    return exits.find(direction)->second;
}

void room::push_exit(std::string dir, room* r)
{
    exits[dir] = r;
}




