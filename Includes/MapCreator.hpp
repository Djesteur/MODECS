#ifndef MAPCREATOR_HPP
#define MAPCREATOR_HPP

#include <map>
#include <vector>
#include <string>

#include "EntityKeeper.hpp"
#include "LogWriter.hpp"
#include "GraphicSystem.hpp"

class MapCreator {

	public:

		MapCreator();
		MapCreator(const Entity &) = delete;
		MapCreator &operator=(const Entity &) = delete;

		std::list<Entity> create(EntityKeeper &keeper, GraphicSystem &system, const sf::Vector2u mapSize);

	private:

		std::map<std::string, std::string> constructHexa(const std::string textureName);
		
		LogWriter m_logWriter;
};

std::vector<std::string> splitDatas(const std::string &datas, const char spliter);


//Rajouter gestion des erreurs dans le chargement

#endif