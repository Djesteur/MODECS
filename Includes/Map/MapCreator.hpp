#ifndef MAPCREATOR_HPP
#define MAPCREATOR_HPP

#include <map>
#include <vector>
#include <string>
#include <deque>
#include <random>
#include <chrono>

#include <SFML/System/Vector2.hpp>

#include "Entity/EntityKeeper.hpp"

#include "Utils/MathUtils.hpp"

#include "LogWriter.hpp"

class MapCreator {

	public:

		MapCreator();
		MapCreator(const Entity &) = delete;
		MapCreator &operator=(const Entity &) = delete;

		void create(const sf::Vector2u mapSize, const unsigned int tileSize);

	private:
		
		LogWriter m_logWriter;
};

//Rajouter gestion des erreurs dans le chargement

#endif