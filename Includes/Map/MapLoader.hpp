/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <map>
#include <vector>
#include <string>

#include "Entity/EntityKeeper.hpp"

#include "Graphic/GraphicSystem.hpp"

#include "Utils/StringUtils.hpp"

#include "Movement/MovementSystem.hpp"

#include "LogWriter.hpp"

class PositionSystem;

class MapLoader {

	public:

		MapLoader();
		MapLoader(const Entity &) = delete;
		MapLoader &operator=(const Entity &) = delete;

		std::list<Entity> load(const std::string mapPath, EntityKeeper &keeper, MovementSystem &movementSystem);

	private:

		//std::map<std::string, Entity> constructExampleTiles(const std::string path, EntityKeeper &keeper, GraphicSystem &system, const unsigned int tileSize);
		
		void extractMovementInformations(const Entity &entity, const std::map<std::string, std::string> &informations, MovementSystem &positionSystem);
		
		/*std::map<std::string, std::string> constructHexa(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		std::map<std::string, std::string> constructSquare(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		std::map<std::string, std::string> constructTriangle(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		*/
		LogWriter m_logWriter;
};

#endif