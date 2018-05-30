#include <iostream>

#include <SFML/Graphics.hpp>

#include "GraphicSystem.hpp"
#include "EntityKeeper.hpp"

int main() {

	sf::RenderWindow window{sf::VideoMode{800, 600}, "MODECS"};

	GraphicSystem system;

	EntityKeeper keeper;

	Entity e1{keeper.newEntity()}, e3{keeper.newEntity()};

	system.addEntity(e1);
	system.addComponent(e1, "SBLA");

	sf::Event event;

	while(window.isOpen()) {

		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) { window.close(); }
		}

		system.update(0);
		system.drawComponents(window);
	}
	
	return 0;
}

/*Pour la prochaine fois:

	-Créer une factory pour le systeme graphique