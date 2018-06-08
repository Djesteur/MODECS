#include <iostream>

#include <SFML/Graphics.hpp>

#include "GraphicSystem.hpp"
#include "EntityKeeper.hpp"
#include "MapCreator.hpp"

int main() {

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "MODECS"};
	window.setVerticalSyncEnabled(true);

	GraphicSystem system;
	EntityKeeper keeper;

	MapCreator creator;
	creator.create(keeper, system, sf::Vector2u{10, 10});
	
	sf::Event event;

	while(window.isOpen()) {

		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) { window.close(); }
		}

		system.update(0);

		window.clear(sf::Color::Black);
		system.drawComponents(window);
		window.display();
	}
	
	return 0;
}

/* Encore a faire:
	
	- Log du system*/