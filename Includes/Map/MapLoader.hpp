/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <map>
#include <vector>
#include <string>
#include <list>

#include "Entity/EntityKeeper.hpp"

#include "Graphic/GraphicSystem.hpp"

#include "Utils/StringUtils.hpp"

#include "Movement/MovementSystem.hpp"

#include "LogWriter.hpp"

class MapLoader {

	public:

		MapLoader();
		MapLoader(const Entity &) = delete;
		MapLoader &operator=(const Entity &) = delete;

		std::list<Entity> loadGame(const std::string mapPath, EntityKeeper &keeper, MovementSystem &movementSystem);
		std::list<Entity> loadGraphics(const std::string mapPath, EntityKeeper &keeper, GraphicSystem &graphicSystem);
		std::list<Entity> loadSounds(const std::string mapPath, EntityKeeper &keeper);

	private:

		std::map<std::string, Entity> constructExampleTiles(const std::string path, EntityKeeper &keeper, GraphicSystem &system, const unsigned int tileSize);
		
		void extractMovementInformations(const Entity &entity, const std::map<std::string, std::string> &informations, MovementSystem &positionSystem);
		void extractGraphicInformations(const Entity &entity, const std::map<std::string, std::string> &informations, std::map<std::string, Entity> exampleTiles, GraphicSystem &graphicSystem);

		std::map<std::string, std::string> constructHexa(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		std::map<std::string, std::string> constructSquare(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		std::map<std::string, std::string> constructTriangle(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		
		LogWriter m_logWriter;
};

#endif