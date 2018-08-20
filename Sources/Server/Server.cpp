#include "Server/Server.hpp"	

Server::Server(): 
	m_logWriter{"Output/Server/Server"},
	m_gameStarted{false},
	m_mapIsReady{false} {

		if(m_listener.listen(43234) != sf::Socket::Done) {

			m_logWriter << "ERROR: can't use the socket 43234"; 
			//Erreur à gérer autrement
		}

		m_selector.add(m_listener);
	}

void Server::run(const unsigned int nbPlayers, const sf::Vector2u mapSize) {

	m_logWriter << "Server Start\n";

	std::thread gamePreparation{[&](){

		createNewMap(nbPlayers, mapSize, "Data/Map/NewMap");
		prepareMapForPlayers("Data/Map/NewMap");
		m_mapIsReady = true;
	}};

	m_players.reserve(nbPlayers);

	while(!m_gameStarted) { communicate(nbPlayers); }

	m_logWriter << "Begin of the game.\n";

	for(std::pair<unsigned int, std::unique_ptr<sf::TcpSocket>> &socket: m_players) { socket.second->disconnect(); }
	m_listener.close();
}





// Player connection functions

void Server::communicate(const unsigned int nbMaxPlayers) {

	m_selector.wait();

	if(m_selector.isReady(m_listener)) { addPlayer(nbMaxPlayers); }

	else {

		for(unsigned int i{0}; i < m_players.size(); i++) {

			if(m_selector.isReady(*(m_players[i].second))) { treatDatas(i); }
		}
	}
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
		}
	}
}

void Server::checkTimeOut() {}






// General commnication functions

void Server::treatDatas(const unsigned int socket) { 

	sf::Packet packet;
	m_players[socket].second->receive(packet);

	std::string command;
	packet >> command;

	m_logWriter << "Receive command from player " << m_players[socket].first << ": " << command << "\n";

	packet.clear();

	if(command == "Stop") {

		packet << "Stop";

		for(std::pair<unsigned int, std::unique_ptr<sf::TcpSocket>> &socket: m_players) { socket.second->send(packet); }

		m_gameStarted = true;
	}

	else if(command == "Download Map") {

		if(m_mapIsReady) {

			packet << "Downloading";
			m_players[socket].second->send(packet);

			packet.clear();
			packet << m_loadedMap;
			m_players[socket].second->send(packet);
		}

		else {

			packet << "Map isn't redy yet.\n";
			m_players[socket].second->send(packet);
		}

		
	}

	else {

		/* overloading << don't work ???
		packet << "Server: sdf"  << " sbla " << 3;
		packet << command << " sbla\n";*/

		std::string messagetoSend{"Server: Unknow command"};
		packet << messagetoSend;

		m_players[socket].second->send(packet);
	}
}












// Chat function

void Server::receiveAndSend() {}

void Server::sendServerMessage(const std::string message) {}



















// Command functions

bool Server::canExecuteThisCommand(const std::vector<std::string> command) { return false; }

void Server::sendCommandToPlayers() {}












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


void Server::createNewMap(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path) {

	MapCreator creator;
	creator.create(mapSize, path);
}

void Server::loadGame(const std::string path) {

	/*MapLoader loader;
	loader.load(path, m_keeper, m_movementSystem);*/
}