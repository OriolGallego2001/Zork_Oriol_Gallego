#include "world.h"
#include "player.h"
#include "item.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>



world::world()
{
    reset_world();
    info();
}

void world::reset_world() {
    entities = std::vector<entity*>();
    std::ifstream file("example.txt");

    if (file.is_open()) {
        load_json_world(file);
        file.close();
    }
    else {
        std::cout << "World file not found" << std::endl;
    }

    define_actions();


}

void world::load_json_world(std::ifstream& file) {

    std::string line;
    std::map<std::string, std::string> data;

    while (std::getline(file, line)) {
        if (line.find('#') != std::string::npos)
            continue; //Skip comments

        if (line.find('{') != std::string::npos) {
            // Start of a new entity, clear previous data
            data.clear();

        }
        else if (line.find('}') != std::string::npos) {
            // End of an entity, extract and store data
            if (data["Type"] == "Creature") {
                room* r = (room*)entities[std::stoi(data["room_id"])];
                std::string name = data["name"];
                std::string description = data["description"];
                creature* e = new creature(name.c_str(), description.c_str(), r);
                entities.push_back(e);
                r->push_entity(e);

            } else if(data["Type"] == "Room") {
                std::string name = data["name"];
                std::string description = data["description"];
                room* e = new room(name.c_str(), description.c_str());
                entities.push_back(e);
            }
            else if (data["Type"] == "Item") {
                std::string name = data["name"];
                std::string description = data["description"];
                int size = std::stoi(data["item_size"]);
                item* e = new item(name.c_str(), description.c_str(), size);
                if (data["owner"] != "none") {
                    entity* owner = entities[std::stoi(data["owner"])];
                    owner->push_entity(e);
                }
                entities.push_back(e);
            }
            else if (data["Type"] == "Player") {
                room* r = (room*)entities[std::stoi(data["room_id"])];
                std::string name = data["name"];
                std::string description = data["description"];
                player* e = new player(name.c_str(), description.c_str(), r);
                main_player = e;
                entities.push_back(main_player);

            }
            else if (data["Type"] == "Exit") {
                room* r = (room*)entities[std::stoi(data["room_id"])];
                std::string direction = data["direction"];
                room* exit = (room*)entities[std::stoi(data["exit_id"])];
                r->push_exit(direction, exit);

            }
            else {
                std::cout << "Error loading world data" << std::endl;

            }
        }
        else if (line.find(':') != std::string::npos) {
            // Split the line into key and value
            size_t colonPos = line.find(':');
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);

            // Remove leading and trailing spaces from key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // Store key-value pair in the map
            data[key] = value;
        }
    }
    

	
}


void world::define_actions()
{
    actions.push_back("look");
    actions.push_back("l");

    actions.push_back("east");
    actions.push_back("e");

    actions.push_back("west");
    actions.push_back("w");

    actions.push_back("north");
    actions.push_back("n");

    actions.push_back("south");
    actions.push_back("s");

    actions.push_back("pick");
    actions.push_back("p");

    actions.push_back("drop");
    actions.push_back("d");

    actions.push_back("move");
    actions.push_back("m");

    actions.push_back("inventory");
    actions.push_back("i");

    actions.push_back("inspect");
    actions.push_back("ins");

    actions.push_back("build");
    actions.push_back("b");

    actions.push_back("reset");
    actions.push_back("R");

    actions.push_back("info");

}
void world::info() {
    std::cout << "Input \"l\" or \"look\" to get the current room information" << std::endl;
    std::cout << "Input \"e\" or \"east\" to move to the room located east if there is one" << std::endl;
    std::cout << "Input \"w\" or \"west\" to move to the room located west if there is one" << std::endl;
    std::cout << "Input \"n\" or \"north\" to move to the room located north if there is one" << std::endl;
    std::cout << "Input \"s\" or \"south\" to move to the room located south if there is one" << std::endl;
    std::cout << "Input \"p\" or \"pick\" to pick up an item in the current room if you have capacity for it" << std::endl;
    std::cout << "Input \"d\" or \"drop\" to drop an item in the current room and free up space in your inventory" << std::endl;
    std::cout << "Input \"m\" or \"move\" to put an item inside another" << std::endl;
    std::cout << "Input \"i\" or \"inventory\" to see what items are you currently holding" << std::endl;
    std::cout << "Input \"ins\" or \"inspect\" to see what entities are nearby" << std::endl;
    std::cout << "Input \"b\" or \"build\" to craft an item out ouf other items in your inventory (Sword and Bait are the current options)" << std::endl;
    std::cout << "Input \"R\" or \"reset\" to restart the game if you are stucked" << std::endl;
    std::cout << "Input \"info\" to print again this message" << std::endl;


}

bool world::parse(const char* input)
{
    std::vector<std::string> substrings;
    std::istringstream iss(input);

    std::string substring;
    while (iss >> substring) {
        substrings.push_back(substring);
    }

    if (!substrings.empty() && substrings.size() < 4) {
        if (std::find(actions.begin(), actions.end(), substrings[0]) != actions.end()) {
            switch (substrings.size())
            {
            case 1:
                if (substrings[0] == "l" || substrings[0] == "look") {
                    main_player->look();
                }
                else if (substrings[0] == "n" || substrings[0] == "north") {
                    main_player->move("north");
                }
                else if (substrings[0] == "e" || substrings[0] == "east") {
                    main_player->move("east");
                }
                else if (substrings[0] == "w" || substrings[0] == "west") {
                    main_player->move("west");
                }
                else if (substrings[0] == "s" || substrings[0] == "south") {
                    main_player->move("south");
                }
                else if (substrings[0] == "i" || substrings[0] == "inventory") {
                    main_player->get_inventory_weight(true);
                }
                else if (substrings[0] == "ins" || substrings[0] == "inspect") {
                    main_player->get_room()->inspect();
                }
                else if (substrings[0] == "R" || substrings[0] == "reset") {
                    reset_world();
                }
                else if (substrings[0] == "info") {
                    info();
                }
                break;
            case 2:
                if (substrings[0] == "p" || substrings[0] == "pick") {
                    main_player->pick(substrings[1]);
                } else if (substrings[0] == "d" || substrings[0] == "drop") {
                    main_player->drop(substrings[1]);
                }
                else if (substrings[0] == "ins" || substrings[0] == "inspect") {
                    entity* e = main_player->get_room()->get_contained_entity(substrings[1]);
                    if (e != NULL)
                        e->inspect();
                    else
                        std::cout << "There is no such item here" << std::endl;

                }
                else if (substrings[0] == "b" || substrings[0] == "build") {
                    main_player->build(substrings[1]);

                }
                break;

            case 3:
                if (substrings[0] == "m" || substrings[0] == "move") {
                    entity* movable = NULL;
                    for (entity* e:entities) {
                        if (e->get_name() == substrings[1] && e->get_type() == EntityType::Item)
                            movable = e;
                    }
                    if (movable != NULL) {           
                        for (entity* e : entities) {
                            if (e->get_name() == substrings[2] && e->get_type() == EntityType::Item) {
                                e->push_entity(movable);
                                std::cout << "You successfully moved the item!" << std::endl;
                                if (e == main_player)
                                    std::cout << "You moved this item from your inventory" << std::endl;
                            }
                            else if (e->get_name() != substrings[1]) {
                                e->remove_contained_entity(movable);
                            }
                            else {
                                std::cout << "You can not move items into: " << substrings[2] << std::endl;
                            }
                        }
                    }
                    else {
                        std::cout << "This item doesn't exist!" << std::endl;
                    }
                }
                break;

            default:
                break;
            }
            return true;
        }
        else {
            // Unrecognized action
            return false;

        }
        return true;
    }
    else {
        // No substrings found
        return false;
    }
}

player* world::get_player()
{
    return main_player;
}

