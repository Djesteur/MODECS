#include "Movement/MovementSystem.hpp"

MovementSystem::MovementSystem(): 
	m_logWriter{"Output/Movement/System"} {}


//Adding, copying and deleting

void MovementSystem::addEntity(const Entity &entity, const sf::Vector3i &pos, const bool canMove, const unsigned int maxMove, const bool canPassHere, const unsigned int travelCost) {

	if(!isInSystem(entity)) { 

		m_datas.insert(std::make_pair(entity, std::make_tuple(sf::Vector3i{0, 0, 0}, canMove, maxMove, maxMove, canPassHere, travelCost))); 
		m_logWriter << "Next entity " << entity << " added with parameters: (" << pos.x << ", " << pos.y << ", " << pos.z <<"), " << canMove << ", " << maxMove 
		<< "/" << maxMove << ", " << canPassHere << ", " << travelCost << "\n";
	}
}

void MovementSystem::copyAllComponents(const Entity &from, const Entity &to) {

	if(isInSystem(from)) {

		if(isInSystem(to)) { m_datas[to] = m_datas[from]; }

		else { m_logWriter << "Trying to copy to entity " << to << ", but he doesn't exist in system.\n"; }
	}

	else { m_logWriter << "Trying to copy from entity " << from << ", but he doesn't exist in system.\n"; }
}

void MovementSystem::deleteEntity(const Entity &entity) {

	if(isInSystem(entity)) { 

		m_datas.erase(m_datas.find(entity)); 
		m_logWriter << "Entity " << entity << " deleted of system.\n";
	}
}



//Checkers




bool MovementSystem::isInSystem(const Entity &entity) {

	if(m_datas.find(entity) == m_datas.end()) { return false; }

	return true;
}



std::vector<Entity> MovementSystem::somethingHere(const sf::Vector3i position) {

	std::vector<Entity> result;

	for(std::pair<Entity, MovementDatas> currentEntity: m_datas) {

		if(std::get<0>(currentEntity.second) == position) { result.emplace_back(currentEntity.first); }
	}

	return result;
}




//Moving


void MovementSystem::setPosition(const Entity &entity, const sf::Vector3i position) {

	if(isInSystem(entity)) {

		std::get<0>(m_datas[entity]) = position;
		m_logWriter << "Set position of " <<  entity << " at (" << position.x << ", " << position.y << ", " << position.z << ").\n";
	}

	else { m_logWriter << "Trying to change position of " << entity << ", but he doesn't exist in system.\n"; }
}






sf::Vector3i convertToCube(const sf::Vector2i &position) { return sf::Vector3i{position.x, position.y, -(position.x + position.y)}; }