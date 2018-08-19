#include "Server/Server.hpp"	

Server::Server(): 
	m_logWriter{"Output/Server/Server"},
	m_gameStarted{false} {

		if(m_listener.listen(43234) != sf::Socket::Done) {

			m_logWriter << "ERROR: can't use the socket 43234"; 
			//Erreur à gérer autrement
		}
	}

void Server::run(const unsigned int nbPlayers, const sf::Vector2u mapSize) {

	m_logWriter << "Server Start\n";

	m_players.reserve(nbPlayers);

	bool gamePreparationFinished{false};

	std::thread gamePreparation{[&](){

		createNewGame(nbPlayers, mapSize, "Data/Map/NewMap");
		loadGame("Data/Map/NewMap");

		gamePreparationFinished = true;
	}};

	while(!m_gameStarted) {

		newConnection(nbPlayers);
		treatDatas(waitForDatas());
	}

	if(!gamePreparationFinished) { 

		m_logWriter << "Wainting the preparation of the map.\n";
		gamePreparation.join(); 
	}

	m_logWriter << "Begin of the game.\n";

}











// Player connection functions

void Server::newConnection(const unsigned int nbMaxPlayers) {

	std::unique_ptr<sf::TcpSocket> newPlayer = std::make_unique<sf::TcpSocket>();
	if(m_players.size() == 0) { m_logWriter << "Waiting first player...\n"; }
	else { newPlayer->setBlocking(false); }

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

unsigned int Server::waitForDatas() {

	unsigned int socket{0};

	m_selector.wait();

	for(unsigned int i{0}; i < m_players.size(); i++) {

		if(m_selector.isReady(*(m_players[i].second))) { socket = i; }
	}

	return socket;
}

void Server::treatDatas(const unsigned int socket) { if(m_players.size() == 2) { m_gameStarted = true; } }












// Chat function

void Server::receiveAndSend() {}

void Server::sendServerMessage(const std::string message) {}



















// Command functions

bool Server::canExecuteThisCommand(const std::vector<std::string> command) { return false; }

void Server::sendCommandToPlayers() {}


















// Map functions

bool Server::createNewGame(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path) {

	MapCreator creator;
	creator.create(mapSize, path);
}

bool Server::loadGame(const std::string path) {

	/*MapLoader loader;
	loader.load(path, m_keeper, m_movementSystem);*/
}