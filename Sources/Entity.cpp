#include "Entity.hpp"

Entity::Entity(): 
	m_ID{0},
	m_isValid{false},
	m_parent{nullptr},
	m_redirection{nullptr},
	m_logFile{nullptr} {}

Entity::Entity(const unsigned int id, std::ofstream *logFile): 
	m_ID{id},
	m_isValid{true},
	m_parent{nullptr},
	m_redirection{nullptr},
	m_logFile{logFile} { *m_logFile << "NewEntity ------- " << this << " ID: " << m_ID << "\n"; }

Entity::Entity(const Entity &entity): 
	m_ID{entity.m_ID},
	m_isValid{true},
	m_parent{nullptr},
	m_redirection{nullptr},
	m_logFile{nullptr} {

		if(entity.m_redirection == nullptr) { m_redirection = &const_cast<Entity&>(entity); }
		else { m_redirection = entity.m_redirection; }

		m_isValid = m_redirection->m_isValid;
		m_logFile = m_redirection->m_logFile;

		*m_logFile << "CopyConstructor - " << this << " (ID: " << m_redirection->m_ID << " Adress: " << m_redirection << ")" << "\n";
	}


Entity &Entity::operator=(const Entity &entity) {

	const_cast<unsigned int&>(m_ID) = entity.m_ID;
	m_parent = nullptr;

	if(entity.m_redirection == nullptr) { m_redirection = &const_cast<Entity&>(entity); }
	else { m_redirection = entity.m_redirection; }

	m_isValid = m_redirection->m_isValid;
	m_logFile = m_redirection->m_logFile;

	*m_logFile << "CopyOperator ---- " << this << " (ID: " << m_redirection->m_ID << " Adress: " << m_redirection << ")" << "\n";

	return *this;
}

Entity::~Entity() {

	if(m_redirection == nullptr) { *m_logFile << "Destroying ------ " << this << " ID: " << m_ID << "\n"; }
	else { *m_logFile << "Destroying ------ " << this << " (ID: " << m_redirection->m_ID << " Adress: " << m_redirection << ")" << "\n"; }
 }


bool Entity::operator==(const Entity& entity) const { return (m_ID == entity.m_ID); }

void Entity::changeParent(Entity &parent) { 

	if(m_redirection == nullptr) { m_parent = &parent; }
	else {

		if(m_redirection->isValid()) { m_redirection->changeParent(parent); }
		else { *m_logFile << "InvalidAcces " << this << " (ID: " << m_ID << " Adress: " << m_redirection << ")" << "\n"; }
	}
}

bool Entity::isValid() const { return m_isValid; }