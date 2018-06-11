#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <map>
#include <vector>
#include <string>

#include "EntityKeeper.hpp"
#include "LogWriter.hpp"
#include "GraphicSystem.hpp"

class MapLoader {

	public:

		MapLoader();
		MapLoader(const Entity &) = delete;
		MapLoader &operator=(const Entity &) = delete;

		std::list<Entity> load(EntityKeeper &keeper, GraphicSystem &system, const unsigned int tileSize);

	private:

		std::map<std::string, std::string> constructHexa(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		std::map<std::string, std::string> constructSquare(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		std::map<std::string, std::string> constructTriangle(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size);
		
		LogWriter m_logWriter;
};

std::vector<std::string> splitDatas(const std::string &datas, const char spliter);


//Rajouter gestion des erreurs dans le chargement

#endif