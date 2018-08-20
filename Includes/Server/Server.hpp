/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include <thread>
#include <memory>
#include <fstream>

#include <SFML/Network.hpp>

#include "LogWriter.hpp"

#include "Map/MapCreator.hpp"
#include "Map/MapLoader.hpp"

#include "Entity/EntityKeeper.hpp"

#include "Movement/MovementSystem.hpp"

class Server {

	public:

		Server(const Server &) = delete;
		Server &operator=(const Server &) = delete;

		Server();

		void run(const unsigned int nbPlayers, const sf::Vector2u mapSize);

		// Players connections functions

		void communicate(const unsigned int nbMaxPlayers);
		void addPlayer(const unsigned int nbMaxPlayers);
		void checkTimeOut();

		// General commnication functions

		void treatDatas(const unsigned int socket);

		// Chat functions

		void receiveAndSend();
		void sendServerMessage(const std::string message);

		// Command functions

		bool canExecuteThisCommand(const std::vector<std::string> command); // Chercher meilleurs formats
		void executeCommand(const std::vector<std::string> command);
		void sendCommandToPlayers();

		// Map functions

		void prepareMapForPlayers(const std::string mapPath);
		void createNewMap(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path);
		void loadGame(const std::string path);

	private:

		LogWriter m_logWriter;

		EntityKeeper m_keeper;
		MovementSystem m_movementSystem;

		sf::TcpListener m_listener;
		sf::SocketSelector m_selector;

		std::vector<std::pair<unsigned int, std::unique_ptr<sf::TcpSocket>>> m_players;

		bool m_gameStarted;
		bool m_mapIsReady;

		std::string m_loadedMap;

		/*

		 Players id start at 1 (0 mean no player want to execute a command/speak in chat)

		<*/

};


#endif