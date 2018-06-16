#ifndef ENTITYKEEPER_HPP
#define ENTITYKEEPER_HPP

#include <list>
#include <fstream>

#include "Entity/Entity.hpp"

#include "LogWriter.hpp"

class EntityKeeper {

	public:

		EntityKeeper(const Entity &) = delete;
		EntityKeeper &operator=(const Entity &) = delete;

		EntityKeeper();
		~EntityKeeper();

		Entity& newEntity();
		
		void invalidEntity(const Entity &entity);
		void deleteEntity(const Entity &entity);

	private:

		std::list<Entity> m_entities;
		
		LogWriter m_logWriter;
};


#endif