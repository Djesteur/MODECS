/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#include <thread>
#include <chrono>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "Graphic/GraphicSystem.hpp"

#include "Entity/EntityKeeper.hpp"

#include "Map/MapLoader.hpp"

#include "Server/Server.hpp"

void startServer() {

	Server server;
	server.run(2, sf::Vector2u{3, 3});
}

bool connectionToServer(sf::TcpSocket &serverConnection, std::thread &serverThread) {

	std::cout << "Host game or join existing server (H/J) ?" << std::endl;

	std::string playerAnswer;

	while(playerAnswer != "H" && playerAnswer != "J") { playerAnswer = ""; std::cin >> playerAnswer; }

	std::string ipAdress;

	if(playerAnswer == "H") {

		serverThread = std::thread{startServer};
		ipAdress = "127.0.0.1";
		std::this_thread::sleep_for(std::chrono::seconds(3)); // Let the server start and be ready for accecpting connections
	}

	else { 

		std::cout << "Enter ip adress of the host: ";
		std::cin >> ipAdress;
	}

	sf::Socket::Status status{serverConnection.connect(ipAdress, 43234, sf::seconds(2.f))};

	//If error on this socket, try the second

	if(status != sf::Socket::Done) { 

		std::cout << "Can't connect with socket 43234, trying with 23432 ..." << std::endl;

		status = serverConnection.connect(ipAdress, 23432, sf::seconds(2.f)); 
	}

	if(status == sf::Socket::Done) { return true; }

	
	return false;
}

int main() {

	std::cout << "Welcome to MODECS v0.1" << std::endl;

	sf::TcpSocket serverConnection;
	std::thread serverThread;

	EntityKeeper keeper;
	MovementSystem movementSystem;
	MapLoader loader;

	if(connectionToServer(serverConnection, serverThread)) {

		std::cout << "Succesfully connected to server ! Waiting server orders." << std::endl; 
		
		bool startGame{false};
		std::string serverOrder;

		sf::Packet packet;

		while(!startGame) {

			serverConnection.receive(packet);
			packet >> serverOrder;

			packet.clear();

			if(serverOrder == "Downloading") {

				std::cout << "Downloading map..." << std::endl;

				serverConnection.receive(packet);
				std::string loadedMap;
				packet >> loadedMap;
				packet.clear();

				std::ofstream writeMap{"Data/Map/NewMapDownloaded"};
				writeMap << loadedMap;
				writeMap.close();

				packet << "Done";
				serverConnection.send(packet);
				packet.clear();

				std::cout << "Done, waiting others players." << std::endl;
			}

			if(serverOrder == "Load") {

				std::cout << "Loading map ..." << std::endl;

				loader.loadGame("Data/Map/NewMapDownloaded", keeper, movementSystem);
				std::cout << "LOO" << std::endl;
				packet << "Done";
				serverConnection.send(packet);
				packet.clear();

				std::cout << "Done, waiting others players." << std::endl;
			}

			if(serverOrder == "Start") {  

				std::cout << "Game start" << std::endl;
				startGame = true; 
			}
		}

		
	}

	else { std::cout << "Can't connect to the server." << std::endl; }

	if(serverThread.joinable()) { serverThread.join(); }
	
	return 0;
}


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