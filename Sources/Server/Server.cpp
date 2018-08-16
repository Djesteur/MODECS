#include "Server/Server.hpp"	

Server::Server(): m_logWriter{"Output/Server/Server"} {}

void Server::startNewGame(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string mapPath) {

	m_logWriter << "Begin a new game for " << nbPlayers << " players with a size of " << mapSize.x << "x" << mapSize.y << ".\n";

	m_logWriter << "Creating map ...";

	MapCreator creator;
	creator.create(mapSize, mapPath);

	m_logWriter << " Done.\n";
}

void Server::loadGame(const std::string path) {

	m_logWriter << "Loading map ...";  

	MapLoader loader;
	loader.load(path, m_keeper, m_movementSystem);

	m_logWriter << " Done.";
}

void Server::runGame() {}