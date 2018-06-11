#include <iostream>

#include <SFML/Graphics.hpp>

#include "GraphicSystem.hpp"
#include "EntityKeeper.hpp"
#include "MapLoader.hpp"
#include "MapCreator.hpp"

int main() {

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "MODECS"};
	window.setVerticalSyncEnabled(true);

	GraphicSystem system;
	EntityKeeper keeper;

	const unsigned int tileSize{128};

	MapCreator creator;
	creator.create(sf::Vector2u{3, 4}, tileSize);

	MapLoader loader;
	loader.load(keeper, system, tileSize);
	
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