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
	componentArguments.insert(std::make_pair("TextureName", "Test"));
	componentArguments.insert(std::make_pair("VertexArrayType", "TriangleFan"));
	componentArguments.insert(std::make_pair("PosX", "400"));
	componentArguments.insert(std::make_pair("PosY", "300"));
	componentArguments.insert(std::make_pair("VertexNumber", "8"));

	const unsigned int s{128};
	const float PI{3.14159265};
	const sf::Vector2f imageCenter{272.f, 272.f};

	sf::Vector2f center{0, 0}, newPoint{center}, diff{0, 0};

	componentArguments.insert(std::make_pair("VerticePosition-0-X", std::to_string(newPoint.x)));
	componentArguments.insert(std::make_pair("VerticePosition-0-Y", std::to_string(newPoint.y)));
	componentArguments.insert(std::make_pair("VerticeTexture-0-X", std::to_string(imageCenter.x + newPoint.x)));
	componentArguments.insert(std::make_pair("VerticeTexture-0-Y", std::to_string(imageCenter.y + newPoint.y)));

	newPoint.x = center.x;
	newPoint.y = center.y + s;

	componentArguments.insert(std::make_pair("VerticePosition-1-X", std::to_string(newPoint.x)));
	componentArguments.insert(std::make_pair("VerticePosition-1-Y", std::to_string(newPoint.y)));
	componentArguments.insert(std::make_pair("VerticeTexture-1-X", std::to_string(imageCenter.x + newPoint.x)));
	componentArguments.insert(std::make_pair("VerticeTexture-1-Y", std::to_string(imageCenter.y + newPoint.y)));

	for(unsigned int i{0}; i < 6; i++) {

		diff = newPoint - center;

		newPoint.x = center.x + diff.x*cos(60.f*PI/180.f) - diff.y*sin(60.f*PI/180.f);
		newPoint.y = center.y + diff.x*sin(60.f*PI/180.f) + diff.y*cos(60.f*PI/180.f);

		componentArguments.insert(std::make_pair("VerticePosition-" + std::to_string(i+2) + "-X", std::to_string(newPoint.x)));
		componentArguments.insert(std::make_pair("VerticePosition-" + std::to_string(i+2) + "-Y", std::to_string(newPoint.y)));
		componentArguments.insert(std::make_pair("VerticeTexture-" + std::to_string(i+2) + "-X", std::to_string(imageCenter.x + newPoint.x)));
		componentArguments.insert(std::make_pair("VerticeTexture-" + std::to_string(i+2) + "-Y", std::to_string(imageCenter.y + newPoint.y)));
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
*/