/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Graphic/GraphicSystem.hpp"

#include "Entity/EntityKeeper.hpp"

#include "Map/MapLoader.hpp"

#include "Server/Server.hpp"

void startServer() {

	Server server;
	server.run(2, sf::Vector2u{10, 10});
}

int main() {


	std::cout << "Welcome to MODECS v0.1" << std::endl;
	std::cout << "Host game or join existing server (H/J) ?" << std::endl;

	std::string playerAnswer;

	while(playerAnswer != "H" && playerAnswer != "J") { playerAnswer = ""; std::cin >> playerAnswer; }

	bool wantToHost{false}; 

	std::thread serverThread;

	std::string ipAdress;

	if(playerAnswer == "H") {

		wantToHost = true;
		serverThread = std::thread{startServer};
		ipAdress = "127.0.0.1";
		std::this_thread::sleep_for(std::chrono::seconds(3)); // Let the server start and be ready for accecpting connections
	}

	else { 

		std::cout << "Enter ip adress of the host: ";
		std::cin >> ipAdress;
	}

	sf::TcpSocket serverConnection;

	sf::Socket::Status status{serverConnection.connect(ipAdress, 43234, sf::seconds(5.f))};

	while(status != sf::Socket::Done) {

		status = serverConnection.connect(ipAdress, 43234);
	}

	if(status == sf::Socket::Done) { 

		std::cout << "Succesfully connected to server !" << std::endl << "Enter command: " << std::endl; 
		
		bool haveToQuit{false};
		std::string playerCommand, serverAnswer;

		sf::Packet packet;

		while(!haveToQuit) {

			playerCommand = "";

			std::cin >> playerCommand;
			packet << playerCommand;
			serverConnection.send(packet);

			packet.clear();

			serverConnection.receive(packet);
			packet >> serverAnswer;
			std::cout << serverAnswer;

			packet.clear();

			if(serverAnswer == "QUIT") {  std::cout << std::endl; haveToQuit = true; }
		}
	}

	else { std::cout << "Can't connect to server." << std::endl; }

	if(wantToHost && serverThread.joinable()) { serverThread.join(); }
	
	return 0;


	/*


	GraphicSystem system;
	EntityKeeper keeper;


	const unsigned int tileSize{128};

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "MODECS"};
	window.setVerticalSyncEnabled(true);
	
	sf::Event event;
	sf::View currentView{sf::Vector2f{0, 0}, sf::Vector2f{1280, 720}};

	bool movingMouseMap{false};
	float moveView{1.f};

	const unsigned int minZoom{1}, maxZoom{11};
	unsigned int currentZoom{11};
	sf::Vector2i oldMousePosition, newMousePosition;

	while(window.isOpen()) {

		//Event

		while(window.pollEvent(event)) {

			if(event.type == sf::Event::Closed) { window.close(); }

			if(event.type == sf::Event::MouseWheelScrolled) {

				if(event.mouseWheelScroll.delta > 0) { 

					if(currentZoom < maxZoom) {

						currentView.zoom(0.8f); 
						moveView *= 0.8f; 
						currentZoom++;
					}
				}

				if(event.mouseWheelScroll.delta < 0) { 

					if(currentZoom > minZoom) {

						currentView.zoom(1.25f); 
						moveView *= 1.25f; 
						currentZoom--;
					}
				}
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
	}*/
}

/* 
	To do:

		- Optimiser création de map (possible ?)
		- Recherche dichotomique des entités (graphic et keeper) (pas pour le moment)
*/