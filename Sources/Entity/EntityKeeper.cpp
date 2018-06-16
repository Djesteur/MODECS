#include "Entity/EntityKeeper.hpp"

EntityKeeper::EntityKeeper():
	m_logWriter{"Output/Entities"} {}

EntityKeeper::~EntityKeeper() {

	m_logWriter << "End of entity system.\n";
	m_entities.clear();
}

Entity& EntityKeeper::newEntity() {

	unsigned int maxEntityID{1}; //0 réservé pour "l'entité nulle" (entité créé avec constructeur par défaut, avant assignation)

	std::list<Entity>::iterator it{m_entities.begin()};

	while(it != m_entities.end()) {

		if(it->m_ID == maxEntityID) {

			maxEntityID++;
			it = m_entities.begin();
		}

		else { it++; }
	}

	m_entities.emplace_back(maxEntityID, &m_logWriter);

	return m_entities.back();
}

void EntityKeeper::invalidEntity(const Entity &entity) {


	for(Entity &currentEntity: m_entities) {

		if(currentEntity == entity) { currentEntity.m_isValid = false; }
	}

	//Enlever l'entité des systèmes
}

//Si il reste des entitées de copie ayant un pointeur vers l'entité, il pointerons vers une zone mémoire désalloué !

void EntityKeeper::deleteEntity(const Entity &entity) {

	for(std::list<Entity>::iterator it{m_entities.begin()}; it != m_entities.end(); it++) {

		if(*it == entity) { m_entities.erase(it); it = m_entities.end(); }
	}
}