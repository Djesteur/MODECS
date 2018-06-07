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
	componentArguments.insert(std::make_pair("Type", "VertexArray"));
	componentArguments.insert(std::make_pair("Name", "FirstVertex"));
	componentArguments.insert(std::make_pair("TextureName", "Building"));
	componentArguments.insert(std::make_pair("PosX", "300"));
	componentArguments.insert(std::make_pair("PosY", "300"));
	componentArguments.insert(std::make_pair("VertexNumber", "7"));

	const unsigned int s{32};
	sf::Vector2f center{300, 300}, currentPoint{332, 300}, diff{0, 0}, newPoint{0, 0};

	componentArguments.insert(std::make_pair("Vertex0X", std::to_string(currentPoint.x)));
	componentArguments.insert(std::make_pair("Vertex0Y", std::to_string(currentPoint.y)));

	std::cout << "(" << currentPoint.x << ", " << currentPoint.y << "): " << 0 << std::endl;

	const float PI{3.14159265};

	for(unsigned int i{1}; i < 7; i++) {

		diff.x = currentPoint.x - center.x;
		diff.y = currentPoint.y - center.y;

		newPoint.x = currentPoint.x + diff.x*cos(PI/3.f) - diff.y*sin(PI/3.f);
		newPoint.y = currentPoint.y + diff.x*sin(PI/3.f) + diff.y*cos(PI/3.f); 

		currentPoint = newPoint;

		componentArguments.insert(std::make_pair("Vertex" + std::to_string(i) + "X", std::to_string(currentPoint.x)));
		componentArguments.insert(std::make_pair("Vertex" + std::to_string(i) + "Y", std::to_string(currentPoint.y)));

		std::cout << "(" << currentPoint.x << ", " << currentPoint.y << "): " << i << std::endl;
	}

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

	- Gérer copie des composants (impossible ?)
	- Réfléchir au log du systeme
	- Ajouter vertexArray comme composant
*/