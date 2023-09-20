#include "action.h"

action::action(std::function<void(const char*, const char*)> callback) :  callback_2(callback)
{
}

action::action(std::function<void(const char*)> callback) : callback_1(callback)
{
}

action::action(std::function<void()> callback) : callback_0(callback)
{
}

void action::execute(const char* param1, const char* param2)
{
	callback_2(param1, param2);
}
void action::execute(const char* param1)
{
	callback_1(param1);
}
void action::execute()
{
	callback_0();
}
