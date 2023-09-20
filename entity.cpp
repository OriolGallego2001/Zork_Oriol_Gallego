#include "entity.h"
#include <iostream>
#include "item.h"

entity::entity(EntityType type, const char* name, const char* description)
{
	this->name = name;
	this->type = type;
	this->description = description;
}

std::string entity::get_name()
{
	return name;
}

std::string entity::get_description()
{
	return description;
}

void entity::look()
{
	std::cout << name << "\n" << description << std::endl;
}

void entity::set_name(const char* name)
{
	this->name = name;
}

void entity::push_entity(entity* e)
{
	containedEntities.push_back(e);
}

int entity::get_inventory_weight(bool print)
{
	int out = 0;
	if (type == EntityType::Item) {
		item* it = (item*)this;
		out += it->size;
	}

	if (containedEntities.size() > 0) {
		if (print) {
			if (type==EntityType::Player)
				std::cout << "\n" << "Your inventory has: " << std::endl;
			else
				std::cout << "\n" << "Enitiy " << name << " has: " << std::endl;
		}
		for (entity* e : containedEntities) {
			if (e->type==EntityType::Item) {
				item* it = (item*)e;		
				int inside_weight = it->get_inventory_weight(print);
				out += inside_weight;
				if (print) std::cout << it->get_name() <<" ("<<it->size<<")"<<std::endl;


			}
		}

	}
	return out;
}

void entity::inspect()
{
	std::cout << name << std::endl << description << std::endl;
	if (containedEntities.size() > 0) {

		std::cout << "That contains:" << std::endl;
		for (entity* e : containedEntities) 
			e->inspect();
	}
}

void entity::print_info()
{
	std::cout << name << "\n" << description << std::endl;
	get_inventory_weight(true);
}

EntityType entity::get_type()
{
	return type;
}

entity* entity::get_contained_entity(std::string entity_name)
{
	for (entity* e : containedEntities) {
		if (e->name == entity_name) {
			return e;
		}
	}
	return NULL;
}

void entity::remove_contained_entity(entity* e)
{
	containedEntities.remove(e);
}

void entity::set_type(EntityType new_type)
{
	type = new_type;
}
