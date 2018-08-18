#include "Movement/MovementSystem.hpp"

MovementSystem::MovementSystem(): 
	m_logWriter{"Output/Movement/System"} {}

void MovementSystem::addMovableEntity(const Entity &entity) {}
void MovementSystem::addMapEntity(const Entity &entity) {}

void MovementSystem::deleteEntity(const Entity &entity) {}

//Checkers

bool MovementSystem::isInSystem(const Entity &entity) {}
bool MovementSystem::haveComponent(const Entity &entity, const std::string &name) {}

//Move

void MovementSystem::goToPosition(const Entity &object, const Entity &position) {}