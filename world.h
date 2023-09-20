#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "entity.h"
#include "room.h"
#include "player.h"
#include "action.h"



class world
{
public:
    world();
    void load_json_world(std::ifstream& file);
    bool parse(const char* input);
    player* get_player();
    
private:
    void reset_world();
    std::vector<entity*> entities;
    player* main_player;
    std::vector<std::string> actions;
    void define_actions();

    void info();

};

