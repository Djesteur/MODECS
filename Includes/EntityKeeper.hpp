#ifndef ENTITYKEEPER_HPP
#define ENTITYKEEPER_HPP

#include "Entity.hpp"

class EntityKeeper {

	public:

		EntityKeeper();

		Entity& newEntity();
		void deleteEntity(const Entity &entity);

	private:

		std::vector<Entity> m_entities;
};


#endif