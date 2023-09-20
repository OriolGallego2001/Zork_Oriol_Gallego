#include "creature.h"

creature::creature(const char* name, const char* description, room* r) :entity(EntityType::Creature, name, description)
{
	this->location = r;
}

room* creature::get_room()
{
	return location;
}

void creature::move(std::string direction)
{
	if (check_dragon(direction))
		return;
	room* exit = location->get_exit(direction);
	if (exit != NULL) {
		location = exit;
	}
	else {
		std::cout << "You cannot go there!" << std::endl;
	}
}

bool creature::check_dragon(std::string direction)
{
	if (direction != "n" && direction != "north")
		return false;
	if (location->get_contained_entity("Dragon")) {
		if (get_contained_entity("Sword")) {
			std::cout << "You really wanted to defeat the dragon with a sword made of stone? (try to *reset* the game and build a different thing)"
				<< std::endl;
			return true;
		}
		if (get_contained_entity("Bait")) {
			std::cout << "Surprisingly the dragon believed that the contraption you made was a mouse"<< 
				" (and everyone knows that dragons are scared of mice). It has now fled and you can advance north!"<<std::endl;
			return false;
		}
		std::cout << "You cannot escape! The giant dragon blocks your path to the " << direction << "." << std::endl;
		return true;
	}

}
