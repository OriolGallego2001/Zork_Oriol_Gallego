#include "player.h"

player::player(const char* name, const char* description, room* r) : creature(name, description, r)
{
	set_type(EntityType::Player);
	capacity = 4;
}

void player::look()
{
	std::cout << get_room()->get_description() << "\n" << get_room()->get_name() << std::endl;
}

void player::pick(std::string item_name)
{
	entity* e = get_room()->get_contained_entity(item_name);
	int capacity_left = capacity - get_inventory_weight(false);
	if (e != NULL) {
		if (e->get_type() == EntityType::Item) {
			item* it = (item*)e;
			int it_weight = e->get_inventory_weight(true);
			if (item_name == "bagpack") {
				capacity = 15;
			}
			if (capacity_left - it_weight >= 0) {
				capacity_left -= it_weight;
				push_entity(it);
				std::cout << "You picked up " << it->get_name() << " (" << it->size << ")" << std::endl;
				get_room()->remove_contained_entity(it);
			}
			else
				std::cout << "You cannot pick up the item, there is no space for it in your inventory." << std::endl;
		}
		else {
			std::cout << "You cannot pick this, it is not an item!" << std::endl;
		}
	}else
		std::cout << "There is no item with this name here." << std::endl;
	std::cout << "You have (" << capacity_left << ") capacity left in your inventory." << std::endl;
}

void player::drop(std::string item_name)
{
	entity* e = get_contained_entity(item_name);
	int capacity_left = capacity - get_inventory_weight(false);
	if (e != NULL) {
		if (e->get_type() == EntityType::Item) {
			item* it = (item*)e;
			capacity_left += get_inventory_weight(false);
			get_room()->push_entity(it);
			std::cout << "You dropped up " << it->get_name() << " (" << it->get_inventory_weight(false) << ")" << std::endl;
			remove_contained_entity(it);
			
		}
		else
			std::cout << "You cannot drop this, it is not an item!" << std::endl;
	}
	else
		std::cout << "There is no item with this name in your inventory." << std::endl;
	std::cout << "You have (" << capacity_left << ") capacity left in your inventory." << std::endl;
}

void player::build(std::string item_name)
{
	entity* paper_ent = get_contained_entity("Paper");
	entity* stick_ent = get_contained_entity("Stick");
	entity* rock_ent = get_contained_entity("Rock");

	bool has_items = paper_ent != NULL;
	has_items = rock_ent != NULL && has_items;
	has_items = stick_ent != NULL && has_items;
	if (!has_items) {
		std::cout << "You don't have the items to build a " << item_name << std::endl;
		return;
	}

	remove_contained_entity(paper_ent);
	remove_contained_entity(rock_ent);
	remove_contained_entity(stick_ent);


	if (item_name == "Sword") {
		item* it = new item(item_name.c_str(), "A stone sword", 5);
		push_entity(it);
		std::cout << "You have crafted a stone sword!" << std::endl;
	}
	else if (item_name == "Bait") {
	item* it = new item(item_name.c_str(), "A mouse looking bait", 7);
	push_entity(it);
	std::cout << "You have crafted a mouse looking bait!" << std::endl;
	}
}

