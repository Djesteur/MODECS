#include "EntityKeeper.hpp"

EntityKeeper::EntityKeeper() {}

Entity& EntityKeeper::newEntity() {

	unsigned int maxEntityID{1}; //0 réservé pour "l'entité nulle" (entité créé avec constructeur par défaut, avant assignation)
	for(unsigned int i{0}; i < m_entities.size(); i++) {

		if(m_entities[i].m_ID == maxEntityID) {

			maxEntityID++;
			i = 0;
		}
	}

	m_entities.emplace_back(maxEntityID);

	return m_entities.back();
}

void EntityKeeper::deleteEntity(const Entity &entity) {




}