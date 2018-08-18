#include "Server/Server.hpp"	

Server::Server(): 
	m_logWriter{"Output/Server/Server"},
	m_gameStarted{false} {}

void Server::run(const unsigned int nbPlayers, const sf::Vector2u mapSize) {

	bool gamePreparationFinished{false};

	std::thread gamePreparation{[&](){

		createNewGame(nbPlayers, mapSize, "Data/Map/NewMap");
		loadGame("Data/Map/NewMap");

		gamePreparationFinished = true;
	}};

	while(!m_gameStarted) {

		if(waitingForConnetion()) { newConnection(); }
		if(haveCommandToExecute()) {

			/*if(canExecuteThisCommand()) {

				executeCommand();
				sendCommandToPlayers();
			}*/
		}

		if(haveSomethingToSay()) { receiveAndSend(); }
	}

	if(!gamePreparationFinished) { gamePreparation.join(); }


}

// Player conection function 

bool Server::waitingForConnetion() const { return false; }

void Server::newConnection() {}

void Server::checkTimeOut() {}

// Chat function

unsigned int Server::haveSomethingToSay() const { return 0; }

void Server::receiveAndSend() {}

void Server::sendServerMessage(const std::string message) {}

// Command functions

unsigned int Server::haveCommandToExecute() const { return 0; }

bool Server::canExecuteThisCommand(const std::vector<std::string> command) { return false; }

void Server::sendCommandToPlayers() {}

// Map functions

bool Server::createNewGame(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path) {

	m_logWriter << "Begin a new game for " << nbPlayers << " players with a size of " << mapSize.x << "x" << mapSize.y << ".\n";

	m_logWriter << "Creating map ...";

	MapCreator creator;
	creator.create(mapSize, path);

	m_logWriter << " Done.\n";
}

bool Server::loadGame(const std::string path) {

	m_logWriter << "Loading map ...";  

	/*MapLoader loader;
	loader.load(path, m_keeper, m_movementSystem);*/

	m_logWriter << " Done.";
}