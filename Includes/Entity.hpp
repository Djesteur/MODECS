#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

class EntityKeeper;

class Entity {

	public:

		Entity();
		Entity(const unsigned int id, std::ofstream *logFile);
		Entity(const Entity &entity);

		Entity &operator=(const Entity &entity);

		~Entity();

		bool operator==(const Entity &entity) const;

		bool isValid() const;

		void changeParent(Entity &parent);


	private:

		friend class EntityKeeper;

		const unsigned int m_ID;

		bool m_isValid;

		Entity *m_parent;
		Entity *m_redirection;

		std::ofstream *m_logFile;
};


#endif