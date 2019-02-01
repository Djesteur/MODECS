#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

#include "LogWriter.hpp"

class EntityKeeper;

class Entity {

	public:

		Entity();
		Entity(const unsigned int id, LogWriter *logWriter);
		Entity(const Entity &entity);

		Entity &operator=(const Entity &entity);

		~Entity();

		bool operator==(const Entity &entity) const;
		bool operator<(const Entity &entity) const;

		bool isValid() const;

		void changeParent(Entity &parent);


	private:

		friend class EntityKeeper;
		friend std::ofstream &operator<<(std::ofstream& out, const Entity &entity);

		const unsigned int m_ID;

		bool m_isValid;

		Entity *m_parent;
		Entity *m_redirection;

		LogWriter *m_logWriter;
};

std::ofstream &operator<<(std::ofstream &out, const Entity &entity);

#endif