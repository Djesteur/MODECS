/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include <list>
#include <string>
#include <utility>
#include <map>
#include <tuple>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "Entity/Entity.hpp"

#include "LogWriter.hpp"

using MovementDatas = std::tuple<sf::Vector3i, bool, unsigned int, unsigned int, bool, unsigned int>;

class MovementSystem {

	public:

		MovementSystem(const MovementSystem &) = delete;
		MovementSystem &operator=(const MovementSystem &) = delete;

		MovementSystem();

		//Adding, copying and deleting

		void addEntity(const Entity &entity, const sf::Vector3i &pos, const bool canMove, const unsigned int maxMove, const bool canPassHere, const unsigned int travelCost);

		void copyAllComponents(const Entity &from, const Entity &to);

		void deleteEntity(const Entity &entity);

		//Checkers

		bool isInSystem(const Entity &entity);

		std::vector<Entity> somethingHere(const sf::Vector3i position);

		//Moving

		void setPosition(const Entity &entity, const sf::Vector3i position);

	private:

		LogWriter m_logWriter;

		std::map<Entity, MovementDatas> m_datas;
};

sf::Vector3i convertToCube(const sf::Vector2i &position);

#endif

//Position
//Peut bouger
//Déplacement actuel
//Déplacement max
//Peut être traversé
//Coût pour traverser
