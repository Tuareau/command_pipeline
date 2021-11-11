#include <iostream>

#include "pipeline.h"

int main() 
{
	size_t commands_count;
	std::cout << "Put commands count: ";
	std::cin >> commands_count;
	Pipeline pipeline(commands_count);
	pipeline.run();
	return 0;
}