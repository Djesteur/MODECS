#include "Entity/Entity.hpp"

Entity::Entity(): 
	m_ID{0},
	m_isValid{false},
	m_parent{nullptr},
	m_redirection{nullptr},
	m_logWriter{nullptr} {}

Entity::Entity(const unsigned int id, LogWriter *logFile): 
	m_ID{id},
	m_isValid{true},
	m_parent{nullptr},
	m_redirection{nullptr},
	m_logWriter{logFile} { *m_logWriter << "NewEntity ------- " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << " ID: " << std::to_string(m_ID) << "\n"; }

Entity::Entity(const Entity &entity): 
	m_ID{entity.m_ID},
	m_isValid{true},
	m_parent{nullptr},
	m_redirection{nullptr},
	m_logWriter{nullptr} {

		if(entity.m_redirection == nullptr) { m_redirection = &const_cast<Entity&>(entity); }
		else { m_redirection = entity.m_redirection; }

		m_isValid = m_redirection->m_isValid;
		m_logWriter = m_redirection->m_logWriter;

		*m_logWriter << "CopyConstructor - " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << " (ID: " << std::to_string(m_redirection->m_ID) 
						 << " Adress: " << std::to_string(reinterpret_cast<std::uintptr_t>(m_redirection)) << ")" << "\n";
	}


Entity &Entity::operator=(const Entity &entity) {

	const_cast<unsigned int&>(m_ID) = entity.m_ID;
	m_parent = nullptr;

	if(entity.m_redirection == nullptr) { m_redirection = &const_cast<Entity&>(entity); }
	else { m_redirection = entity.m_redirection; }

	m_isValid = m_redirection->m_isValid;
	m_logWriter = m_redirection->m_logWriter;

	*m_logWriter << "CopyOperator ---- " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << " (ID: " << std::to_string(m_redirection->m_ID) 
		             << " Adress: " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << ")" << "\n";

	return *this;
}

Entity::~Entity() {

	if(m_redirection == nullptr) { *m_logWriter << "Destroying ------ " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << " ID: " << std::to_string(m_ID) << "\n"; }
	else { *m_logWriter << "Destroying ------ " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << " (ID: " << std::to_string(m_redirection->m_ID) 
							<< " Adress: " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << ")" << "\n"; }
 }


bool Entity::operator==(const Entity& entity) const { return (m_ID == entity.m_ID); }

void Entity::changeParent(Entity &parent) { 

	if(m_redirection == nullptr) { m_parent = &parent; }
	else {

		if(m_redirection->isValid()) { m_redirection->changeParent(parent); }
		else { *m_logWriter << "InvalidAcces " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << " (ID: " << std::to_string(m_ID) 
								<< " Adress: " << std::to_string(reinterpret_cast<std::uintptr_t>(this)) << ")" << "\n"; }
	}
}

bool Entity::isValid() const { return m_isValid; }