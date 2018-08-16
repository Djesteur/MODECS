/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

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

#include "Utils/StringUtils.hpp"
#include "Utils/MathUtils.hpp"

#include "LogWriter.hpp"

class MapCreator {

	public:

		MapCreator();
		MapCreator(const Entity &) = delete;
		MapCreator &operator=(const Entity &) = delete;

		void create(const sf::Vector2u mapSize, const std::string path);

	private:

		bool loadTilesTypes(const std::string filePath);
		
		LogWriter m_logWriter;

		std::vector<std::string> m_hexaTiles, m_squareTiles, m_triangleTiles;
};

#endif