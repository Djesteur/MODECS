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
	const float tileSpace{tileSize*(1 + sqrtf(3.f))};

	MapCreator creator;
	creator.create(sf::Vector2u{10, 10}, tileSize);

	MapLoader loader;
	loader.load(keeper, system, tileSize);
	
	sf::Event event;
	sf::View currentView{sf::Vector2f{640, 360}, sf::Vector2f{1280, 720}};

	while(window.isOpen()) {

		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) { window.close(); }

			if(event.type == sf::Event::KeyPressed) {

				if(event.key.code == sf::Keyboard::Z) { currentView.move(0.f, -tileSpace); }
				if(event.key.code == sf::Keyboard::S) { currentView.move(0.f, tileSpace); }
				if(event.key.code == sf::Keyboard::Q) { currentView.move(-tileSpace, 0.f); }
				if(event.key.code == sf::Keyboard::D) { currentView.move(tileSpace, 0.f); }

				if(event.key.code == sf::Keyboard::T) { system.haveToDrawBorders(true); }
				if(event.key.code == sf::Keyboard::Y) { system.haveToDrawBorders(false); }
			}
		}

		system.update(0);

		window.clear(sf::Color::Black);

		window.setView(currentView);
		system.drawComponents(window);
		window.setView(window.getDefaultView());

		window.display();
	}
	
	return 0;
}

/* Encore a faire:

	- Optimiser création de tiles et chargement
	- Créer un fichier "utils" ?
	
	- Log du system*/