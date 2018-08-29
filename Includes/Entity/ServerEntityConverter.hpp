#ifndef SERVERENTITYCONVERTER_HPP
#define SERVERENTITYCONVERTER_HPP

#include <map>
#include <string>

#include "LogWriter.hpp"

#include "Entity/Entity.hpp"
#include "Entity/EntityKeeper.hpp"

class ServerEntityConverter {

	public:

		ServerEntityConverter(EntityKeeper &keeper);

		ServerEntityConverter() = delete;
		ServerEntityConverter(const ServerEntityConverter &) = delete;
		ServerEntityConverter &operator=(const ServerEntityConverter &) = delete;

		Entity& newEntity(const unsigned int serverEntity);
		void deleteEntity(const unsigned int serverEntity);

		Entity& getEntityFromServer(const unsigned int serverEntity);
		unsigned int getServerEntity(const Entity &gameEntity);

		bool exist(const unsigned int serverEntity);
		bool exist(const Entity &entity);

	private:

		std::map<unsigned int, Entity> m_serverConverter;

		EntityKeeper &m_keeper;

		LogWriter m_logWriter;
};

#endif