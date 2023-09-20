#pragma once
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <iostream>


class action
{
public:
	action(std::function<void(const char*, const char*)> callback);
	action(std::function<void(const char*)> callback);
	action(std::function<void()> callback);

	void execute(const char* param1, const char* param2);
	void execute(const char* param1);
	void execute();
private:
	std::function<void(const char*, const char*)> callback_2;
	std::function<void(const char*)> callback_1;
	std::function<void()> callback_0;

};

