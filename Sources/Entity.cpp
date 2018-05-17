#include "Entity.hpp"

Entity::Entity(const unsigned int id): 
	m_ID{id},
	m_parent{nullptr},
	m_redirection{nullptr} {}

Entity::Entity(const Entity &entity):
	m_ID{entity.m_ID},
	m_parent{nullptr},
	m_redirection{std::make_shared<Entity>(entity)} {}

Entity& Entity::operator=(const Entity &entity) {

	Entity newEntity{entity.m_ID};
	newEntity.m_parent = nullptr;
	m_redirection = std::make_shared<Entity>(entity);
	return newEntity;
}

bool Entity::operator==(const Entity &entity) { return (m_ID == entity.m_ID); }

void Entity::changeParent(const Entity &newParent) { 

	if(m_redirection != nullptr) { m_redirection->changeParent(newParent); } 
	else { m_parent = std::make_shared<Entity>(newParent); }
}

void Entity::deleteParent() { 

	if(m_redirection != nullptr) { m_redirection->deleteParent(); } 
	else { m_parent = nullptr; }
}
		
void Entity::addChild(const Entity &newChild) { 

	if(m_redirection != nullptr) { m_redirection->addChild(newChild);  } 
	else { m_children.push_back(std::make_shared<Entity>(newChild)); }
}

void Entity::deleteChild(const Entity &childToDelete) {

	if(m_redirection != nullptr) { m_redirection->deleteChild(childToDelete);  } 
	else {

		for(unsigned int i{0}; i < m_children.size(); i++) {

			if(*(m_children[i]) == childToDelete) { m_children.erase(m_children.begin() + i); }
		}
	}
}

void Entity::deleteEntityWithoutBackup(const Entity &entityToDelete) {

	if(m_redirection != nullptr) { m_redirection->deleteEntityWithoutBackup(entityToDelete);  } 
	else {

		for(std::shared_ptr<Entity> currentChild: m_children) {

			if(*this == entityToDelete) { currentChild->deleteParent(); }

			else { currentChild->deleteEntityWithoutBackup(entityToDelete); }
		}
	}
}

void Entity::deleteEntityWithBackup(const Entity &entityToDelete, const Entity &newParent) {

	if(m_redirection != nullptr) { m_redirection->deleteEntityWithBackup(entityToDelete, newParent);  } 
	else {

		for(std::shared_ptr<Entity> currentChild: m_children) {

			if(*this == entityToDelete) { currentChild->changeParent(newParent); }

			else { currentChild->deleteEntityWithBackup(entityToDelete, newParent); }
		}
	}
}

bool Entity::haveChild(const Entity &child) const {

	if(m_redirection != nullptr) { return m_redirection->haveChild(child);  } 
	else {

		bool result{false};

		for(std::shared_ptr<Entity> currentChild: m_children) {

			if(*(currentChild) == child) { result = true; }
			else if(currentChild->haveChild(child)) { result = true; }
		}

		return result;
	}
}
