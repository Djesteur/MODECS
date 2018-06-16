/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#include <SFML/Graphics.hpp>

#include "Graphic/GraphicSystem.hpp"

#include "Entity/EntityKeeper.hpp"

#include "Map/MapLoader.hpp"
#include "Map/MapCreator.hpp"

int main() {

	GraphicSystem system;
	EntityKeeper keeper;

	const unsigned int tileSize{128};
	const float tileSpace{tileSize*(1 + sqrtf(3.f))};

	MapCreator creator;
	creator.create(sf::Vector2u{10, 10}, tileSize);

	MapLoader loader;
	loader.load(keeper, system, tileSize);

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "MODECS"};
	window.setVerticalSyncEnabled(true);
	
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

	- Optimiser création de tiles
	- Vérifier fichier lors du chargement
	- Log du system
*/