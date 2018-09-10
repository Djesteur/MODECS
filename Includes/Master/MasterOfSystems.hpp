#ifndef MASTEROFSYSTEMS_HPP
#define MASTEROFSYSTEMS_HPP

#include "LogWriter.hpp"

#include "Utils/StringUtils.hpp"

#include "Entity/EntityKeeper.hpp"
#include "Entity/ServerEntityConverter.hpp"

#include "Graphic/GraphicSystem.hpp"

#include "Movement/MovementSystem.hpp"

#include "Map/MapCreator.hpp"
#include "Map/MapLoader.hpp"


class MasterOfSystems {

	public:

		MasterOfSystems(const bool wantGraphics, const bool wantSounds);

		MasterOfSystems(const MasterOfSystems &MasterOfSystems) = delete;
		MasterOfSystems &operator=(const MasterOfSystems &MasterOfSystems) = delete;

		void receiveMessage(std::string message);

		void update(const unsigned int elapsedNanoTime);

		void drawGame(sf::RenderTarget &target);

	private:

		LogWriter m_logWriter;

		EntityKeeper m_keeper;
		GraphicSystem m_graphicSystem;
		MovementSystem m_movementSystem;
		ServerEntityConverter m_entityConverter;

		bool m_haveGraphics, m_haveSounds;
};

#endif