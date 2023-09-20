#pragma once
#include <string>
#include <list>

enum class EntityType { Creature, Room, Item, Exit, Player };
class entity
{
public:
    entity(EntityType type, const char* name, const char* description);

    std::string get_name();
    std::string get_description();
    void look();
    void set_name(const char* name);
    void push_entity(entity* e);
    int get_inventory_weight(bool print);
    void inspect();
    void print_info();
    EntityType get_type();
    entity* get_contained_entity(std::string entity_name);
    void remove_contained_entity(entity* e);
    void set_type(EntityType new_type);
private:
    EntityType type;
    std::string name;
    std::string description;
    std::list<entity*> containedEntities;

};

