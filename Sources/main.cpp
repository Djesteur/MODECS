#include <iostream>

#include "EntityKeeper.hpp"

int main() {

	EntityKeeper keeper;

	Entity e1{keeper.newEntity()};
	Entity e3{keeper.newEntity()};;
	Entity e2{e1};

	e2.changeParent(e3);
	e2 = e3;
	return 0;
}