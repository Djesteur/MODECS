#ifndef MAPCREATOR_HPP
#define MAPCREATOR_HPP

#include <map>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "EntityKeeper.hpp"
#include "LogWriter.hpp"

#define PI 3.14159265

class MapCreator {

	public:

		MapCreator();
		MapCreator(const Entity &) = delete;
		MapCreator &operator=(const Entity &) = delete;

		void create(const sf::Vector2u mapSize, const unsigned int tileSize);

	private:

		float getNorme(const sf::Vector2f u, const sf::Vector2f v) const;
		
		LogWriter m_logWriter;
};

//Rajouter gestion des erreurs dans le chargement

#endif