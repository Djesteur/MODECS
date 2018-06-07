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
	//componentArguments.insert(std::make_pair("TextureName", "Building"));
	componentArguments.insert(std::make_pair("VertexArrayType", "TriangleFan"));
	//componentArguments.insert(std::make_pair("PosX", "300"));
	//componentArguments.insert(std::make_pair("PosY", "300"));
	componentArguments.insert(std::make_pair("VertexNumber", "8"));

	const unsigned int s{64};
	sf::Vector2f center{300, 300}, newPoint{0, 0};

	const float PI{3.14159265};

	for(unsigned int i{0}; i < 8; i++) {

		newPoint.x = center.x + s*cos(i*60.f*PI/180.f) - s*sin(i*60.f*PI/180.f);
		newPoint.y = center.y + s*sin(i*60.f*PI/180.f) + s*cos(i*60.f*PI/180.f); 

		componentArguments.insert(std::make_pair("VerticePosition-" + std::to_string(i) + "-X", std::to_string(newPoint.x)));
		componentArguments.insert(std::make_pair("VerticePosition-" + std::to_string(i) + "-Y", std::to_string(newPoint.y)));

		componentArguments.insert(std::make_pair("VerticeColor-" + std::to_string(i), "00FFFFFF"));
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