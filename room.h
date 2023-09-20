#pragma once
#include "entity.h"
#include <iostream>
#include <fstream>

#include <string>
#include <map>
class room:
	public entity
{
public:
	room(const char* name, const char* description);
	room* get_exit(std::string direction);
	void push_exit(std::string dir, room* r);

private:
	std::map<std::string, room*> exits;
	
};

