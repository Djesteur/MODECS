/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef SERVER_HPP
#define SERVER_HPP

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

		void startNewGame(const unsigned int nbPlayers, const sf::Vector2u mapSize);
		void loadGame(const std::string path);
		void runGame();

	private:

		LogWriter m_logWriter;

		EntityKeeper m_keeper;
		MovementSystem m_movementSystem;
};


#endif