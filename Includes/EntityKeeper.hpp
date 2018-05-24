#ifndef ENTITYKEEPER_HPP
#define ENTITYKEEPER_HPP

#include <list>
#include <fstream>

#include "Entity.hpp"

class EntityKeeper {

	public:

		EntityKeeper();
		~EntityKeeper();

		Entity& newEntity();
		
		void invalidEntity(const Entity &entity);
		void deleteEntity(const Entity &entity);

	private:

		std::list<Entity> m_entities;
		std::ofstream m_logFile;
};


#endif