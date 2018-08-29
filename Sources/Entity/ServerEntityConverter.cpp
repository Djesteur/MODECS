#include "Entity/ServerEntityConverter.hpp"

ServerEntityConverter::ServerEntityConverter(EntityKeeper &keeper):
	m_keeper{keeper},
	m_logWriter{"Output/Entity/ServerEntityWriter"} {}


Entity& ServerEntityConverter::newEntity(const unsigned int serverEntity) {

	m_serverConverter.insert(std::make_pair(serverEntity, m_keeper.newEntity()));
	m_logWriter << "New server entity " << serverEntity << " added as " << m_serverConverter[serverEntity] << "\n"; 

	return m_serverConverter[serverEntity];
}

void ServerEntityConverter::deleteEntity(const unsigned int serverEntity) {

	if(exist(serverEntity)) { 

		m_serverConverter.erase(serverEntity);
		m_logWriter << "Server entity" << serverEntity << " deleted";
	}
	
	else { m_logWriter << "Trying to delete an entity, " << serverEntity << "wich doesn't exist in converter"; }
}

Entity& ServerEntityConverter::getEntityFromServer(const unsigned int serverEntity) {

	m_logWriter << "Asking server entity " << serverEntity << "\n";

	if(m_serverConverter.find(serverEntity) == m_serverConverter.end()) {

		m_logWriter << "Entity doesn't exist in converter, creating new entity\n";
		newEntity(serverEntity);
	}

	return m_serverConverter[serverEntity];
}

unsigned int ServerEntityConverter::getServerEntity(const Entity &gameEntity) {

	m_logWriter << "Asking game entity " << gameEntity << "\n";

	for(std::pair<unsigned int, Entity> currentEntity: m_serverConverter) {

		if(currentEntity.second == gameEntity) { return currentEntity.first; }
	}

	m_logWriter << "Entity doesn't exist in converter, returning 0" << "\n";
	return 0;
}


bool ServerEntityConverter::exist(const unsigned int serverEntity) {

	if(m_serverConverter.find(serverEntity) != m_serverConverter.end()) {  return true; }

	return false;
}

bool ServerEntityConverter::exist(const Entity &gameEntity) {

	for(std::pair<unsigned int, Entity> currentEntity: m_serverConverter) {

		if(currentEntity.second == gameEntity) { return true; }
	}

	return false; 
}
