#include "Server/Server.hpp"	

Server::Server(): 
	m_logWriter{"Output/Server/Server"},
	m_gameStarted{false},
	m_canStartServer{true} {

		if(m_listener.listen(43234) != sf::Socket::Done) {

			m_logWriter << "WARNING: can't use the socket 43234\n"; 
			//Erreur à gérer autrement

			if(m_listener.listen(23432) != sf::Socket::Done) { 

				m_logWriter << "ERROR: can't use the socket 23432\n"; 
				m_canStartServer = false;
			}
		}

		m_selector.add(m_listener);
	}

void Server::run(const unsigned int nbPlayers, const sf::Vector2u mapSize) {

	if(m_canStartServer) {

		m_logWriter << "Server Start\n";

		createNewMap(nbPlayers, mapSize, "Data/Map/NewMap");
		loadGame("Data/Map/NewMap");
		prepareMapForPlayers("Data/Map/NewMap");

		m_players.reserve(nbPlayers);

		while(!m_gameStarted) { waitConnections(nbPlayers); }

		m_logWriter << "Begin of the game.\n";

		playersLoadGame();
		runGame();

		m_logWriter << "End of the game.\n";

		for(std::pair<unsigned int, std::unique_ptr<sf::TcpSocket>> &socket: m_players) { socket.second->disconnect(); }
		m_listener.close();
	}
}


// Game functions

void Server::runGame() {}

// Orders functions

void Server::sendForAll(const std::string message) {

	sf::Packet packet;
	packet << message;

	for(std::pair<unsigned int, std::unique_ptr<sf::TcpSocket>> &currentPlayer: m_players) { currentPlayer.second->send(packet); }
}

std::pair<unsigned int, std::string> Server::waitMessage() {

	m_selector.wait();

	std::pair<unsigned int, std::string> result;
	sf::Packet packet;

	for(unsigned int i{0}; i < m_players.size(); i++) {

		if(m_selector.isReady(*(m_players[i].second))) {

			result.first = i + 1; //For id
			m_players[i].second->receive(packet);
			packet >> result.second;

			return result;
		}
	}

	return std::make_pair(0, "");
}

// Player connection functions

void Server::waitConnections(const unsigned int nbMaxPlayers) {

	m_selector.wait();

	if(m_selector.isReady(m_listener)) { addPlayer(nbMaxPlayers); }
}

void Server::addPlayer(const unsigned int nbMaxPlayers) {

	std::unique_ptr<sf::TcpSocket> newPlayer = std::make_unique<sf::TcpSocket>();

	if(m_listener.accept(*newPlayer) == sf::Socket::Done) {

		// Select player number, then add player with this number

		if(m_players.size() >= nbMaxPlayers) {

			sf::Packet packet;
			packet << "Can't connect to server, enought players already connected.\n";
			newPlayer->send(packet);
		}

		else {

			unsigned int newPlayerNumber{1};

			for(unsigned int i{0}; i < m_players.size(); i++) {

				if(m_players[i].first == newPlayerNumber) { 

					newPlayerNumber++;
					i = 0;
				}
			}

			m_players.emplace_back(std::make_pair(newPlayerNumber, std::move(newPlayer)));
			m_selector.add(*(m_players.back().second));

			m_logWriter << "New player connected with id " << newPlayerNumber << "\n";

			if(m_players.size() == nbMaxPlayers) { m_gameStarted = true; }
		}
	}
}

void Server::checkTimeOut() {}





// Map functions


void Server::prepareMapForPlayers(const std::string mapPath) {

	std::ifstream map{mapPath};

	if(!map) { m_logWriter << "ERROR: can't open map for players.\n"; }
	else {

		std::string currentData;
		m_loadedMap = "";

		while(std::getline(map, currentData)) { m_loadedMap += currentData + "\n"; }
	}
}

void Server::playersLoadGame() {

	m_logWriter << "Players downloading the map ...\n";

	sendForAll("Downloading");
	sendForAll(m_loadedMap);

	unsigned int nbDone{0};
	std::pair<unsigned int, std::string> result;

	while(nbDone != m_players.size()) {

		result = waitMessage();

		if(result.first != 0 && result.second == "Done") { 

			nbDone++; 
			m_logWriter << "Player " << result.first << " downloaded the map.\n";
		}
	}

	m_logWriter << "Done\nPlayers loading the map ...\n";

	sendForAll("Load");

	loadGame("Data/Map/NewMap");

	nbDone = 0;

	while(nbDone != m_players.size()) {

		result = waitMessage();

		if(result.first != 0 && result.second == "Done") { 

			nbDone++; 
			m_logWriter << "Player " << result.first << " loaded the map.\n";
		}
	}

	sendForAll("Start");

	m_logWriter << "Done\n";
}


void Server::createNewMap(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path) {

	MapCreator creator;
	creator.create(mapSize, path);
}

void Server::loadGame(const std::string path) {

	MapLoader loader;
	loader.loadGame(path, m_keeper, m_movementSystem);
}