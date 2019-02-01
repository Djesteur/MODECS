#include "Master/MasterOfSystems.hpp"

MasterOfSystems::MasterOfSystems(const bool wantGraphics, const bool wantSounds):
	m_logWriter{"Output/Master/MasterOfSystems"},
	m_entityConverter{m_keeper},
	m_haveGraphics{wantGraphics},
	m_haveSounds{wantSounds} {}


void MasterOfSystems::receiveMessage(std::string message) {

	m_logWriter << "Received message: \"" << message << "\"\n";

	std::string extractedOrder{getPartOfMessage(message)};

	if(extractedOrder == "LOAD") {

		MapLoader loader;
		loader.loadGame("Data/Map/NewMapDownloaded", m_keeper, m_movementSystem);

		if(m_haveGraphics) { loader.loadGraphics("Data/Map/NewMapDownloaded", m_keeper, m_graphicSystem); }
		if(m_haveSounds) { loader.loadSounds("Data/Map/NewMapDownloaded", m_keeper); }
	}
}

void MasterOfSystems::update(const unsigned int elapsedNanoTime) { m_graphicSystem.update(elapsedNanoTime); }

void MasterOfSystems::drawGame(sf::RenderTarget &target) { m_graphicSystem.drawComponents(target); }