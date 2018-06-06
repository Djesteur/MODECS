#include <iostream>

#include <SFML/Graphics.hpp>

#include "GraphicSystem.hpp"
#include "EntityKeeper.hpp"

int main() {

	sf::RenderWindow window{sf::VideoMode{800, 600}, "MODECS"};
	window.setVerticalSyncEnabled(true);

	GraphicSystem system;

	EntityKeeper keeper;

	Entity e1{keeper.newEntity()}, e3{keeper.newEntity()};

	system.addEntity(e1);
	std::map<std::string, std::string> componentArguments;
	componentArguments.insert(std::make_pair("Type", "Sprite"));
	componentArguments.insert(std::make_pair("Name", "FirstSprite"));
	componentArguments.insert(std::make_pair("TextureName", "TestSprite"));
	componentArguments.insert(std::make_pair("PosX", "0"));
	componentArguments.insert(std::make_pair("PosY", "0"));

	system.addComponent(e1, componentArguments);

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

/*Pour la prochaine fois:

	- Gérer copie des composants
	- Réfléchir au log du systeme
	- Ajouter vertexArray comme composant

*/