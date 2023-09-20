#include "item.h"

item::item(const char* name, const char* description, int size):entity(EntityType::Item, name, description)
{
	this->size = size;
}
