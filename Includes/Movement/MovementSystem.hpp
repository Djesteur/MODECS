/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include <list>
#include <string>
#include <utility>

#include <SFML/Vector3.hpp>

#include "Entity/Entity.hpp"

#include "LogWriter.hpp"

using MovementEntityAndComponent = std::pair<Entity, std::array<Vector3u, 2>>;

/*
	0: 2D position (z = 0 all times)
	1: Cube Position
*/

using MapEntityAndComponent = std::pair<Entity, std::list<unsigned int>>;

class MovementSystem {

	public:

		MovementSystem(const MovementSystem &) = delete;
		MovementSystem &operator=(const MovementSystem &) = delete;

		MovementSystem();

		//Adding, copying and deleting

		void addMovableEntity(const Entity &entity);
		void addMapEntity(const Entity &entity);

		void deleteEntity(const Entity &entity);

		//Checkers

		bool isInSystem(const Entity &entity);
		bool haveComponent(const Entity &entity, const std::string &name);

		//Move

		void goToPosition(const Entity &object, const Entity &position);

	private:

		LogWriter m_logWriter;

		std::list<MovementEntityAndComponent> m_movableDatas;
		std::list<MapEntityAndComponent> m_mapDatas;
};

#endif