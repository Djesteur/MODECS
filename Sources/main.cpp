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

	MapCreator creator;
	creator.create(sf::Vector2u{10, 10}, tileSize);

	MapLoader loader;
	loader.load(keeper, system, tileSize);

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "MODECS"};
	window.setVerticalSyncEnabled(true);
	
	sf::Event event;
	sf::View currentView{sf::Vector2f{0, 0}, sf::Vector2f{1280, 720}};

	bool movingMouseMap{false};
	float moveView{1.f};
	sf::Vector2i oldMousePosition, newMousePosition;

	while(window.isOpen()) {

		//Event

		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) { window.close(); }

			if(event.type == sf::Event::MouseWheelScrolled) {

				if(event.mouseWheelScroll.delta > 0) { currentView.zoom(0.8f); moveView *= 0.8f; }
				if(event.mouseWheelScroll.delta < 0) { currentView.zoom(1.25f); moveView *= 1.25f; }
			}

			if(event.type == sf::Event::MouseButtonPressed) {

				if(event.mouseButton.button == sf::Mouse::Left) { movingMouseMap = true; oldMousePosition = sf::Mouse::getPosition(); } 
			}

			if(event.type == sf::Event::MouseButtonReleased) {

				if(event.mouseButton.button == sf::Mouse::Left) { movingMouseMap = false; } 
			}
		}

		//Update

		system.update(0);

		if(movingMouseMap) {

			newMousePosition = sf::Mouse::getPosition();
			currentView.move((oldMousePosition.x - newMousePosition.x)*moveView, (oldMousePosition.y - newMousePosition.y)*moveView);
			oldMousePosition = newMousePosition;
		}

		//Draw

		window.clear(sf::Color::Black);

		window.setView(currentView);
		system.drawComponents(window);
		window.setView(window.getDefaultView());

		window.display();
	}
	
	return 0;
}

/* To do:

	- Optimiser création de map (possible ?)
	- Recherche dichotomique des entités (graphic et keeper) (pas pour le moment)
*/