/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include <thread>

#include <SFML/Graphics.hpp>

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

		//Players connections functions

		bool waitingForConnetion() const;
		void newConnection();
		void checkTimeOut();

		// Chat functions

		unsigned int haveSomethingToSay() const;
		void receiveAndSend();
		void sendServerMessage(const std::string message);

		// Command functions

		unsigned int haveCommandToExecute() const;
		bool canExecuteThisCommand(const std::vector<std::string> command); // Chercher meilleurs formats
		void executeCommand(const std::vector<std::string> command);
		void sendCommandToPlayers();

		// Map functions

		bool createNewGame(const unsigned int nbPlayers, const sf::Vector2u mapSize, const std::string path);
		bool loadGame(const std::string path);

		void sendMapToPlayers();

	private:

		LogWriter m_logWriter;

		EntityKeeper m_keeper;
		MovementSystem m_movementSystem;

		bool m_gameStarted;

		/*

		 Players id start at 1 (0 mean no player want to execute a command/speak in chat)

		<*/
};


#endif