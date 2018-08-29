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

	private:

		// Game functions

		void runGame();

		// Orders functions

		void sendForAll(const std::string message);
		std::pair<unsigned int, std::string> waitMessage();

		// Players connections functions

		void waitConnections(const unsigned int nbMaxPlayers);
		void addPlayer(const unsigned int nbMaxPlayers);
		void checkTimeOut();

		// Map functions

		void prepareMapForPlayers(const std::string mapPath);
		void playersLoadGame();

		void createNewMap(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path);
		void loadGame(const std::string path);

		LogWriter m_logWriter;

		EntityKeeper m_keeper;
		MovementSystem m_movementSystem;

		sf::TcpListener m_listener;
		sf::SocketSelector m_selector;

		std::vector<std::pair<unsigned int, std::unique_ptr<sf::TcpSocket>>> m_players;

		bool m_gameStarted;
		bool m_canStartServer;

		std::string m_loadedMap;

		/*

		 Players id start at 1 (0 mean no player want to execute a command/speak in chat)

		<*/

};


#endif