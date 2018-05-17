#include <iostream>

#include "EntityKeeper.hpp"

int main() {

	EntityKeeper keeper;

	std::cout << "LOL" << std::endl;
	Entity e1{keeper.newEntity()};
	std::cout << "LOL" << std::endl;
	Entity e2 = e1;

	std::cout << "E1: " << &e1 << " - E2: " << &e2 << std::endl;

	return 0;
}