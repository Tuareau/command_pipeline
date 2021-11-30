#include <iostream>

#include "iinput.h"
#include "pipeline.h"

int main() 
{
	std::cout << ">>> put commands count: ";
	auto commands_count = IInput<size_t>().getValueFromInput();
	Pipeline pipeline(commands_count);
	pipeline.run();
	return 0;
}