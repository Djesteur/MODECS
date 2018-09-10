#include "Graphic/GraphicSystem.hpp"

GraphicSystem::GraphicSystem(): 
	m_logWriter{"Output/Graphics/System"},
	m_lastResearchEntity{m_datas.end()} {}

void GraphicSystem::addComponent(const Entity &entity, std::map<std::string, std::string> &factoryParam) {

	if(isInSystem(entity)) {

		std::unique_ptr<GraphicComponent> newComponent{m_factory.newGraphicComponent(factoryParam)};

		if(newComponent != nullptr) { 

			m_logWriter << "Adding component " << newComponent.get() << " to entity " << m_lastResearchEntity->first << ".\n";
			m_lastResearchEntity->second.emplace_back(std::move(newComponent)); 
		}
	}
}

void GraphicSystem::addEntity(const Entity &entity) { m_datas.emplace_back(std::make_pair(entity, std::list<std::unique_ptr<GraphicComponent>>{})); }

void GraphicSystem::copyAllComponents(const Entity &from, const Entity &to) {

	if(isInSystem(from)) {

		std::list<EntityAndComponent>::iterator fromSearch{m_lastResearchEntity};
		
		if(isInSystem(to)) {

			m_logWriter << "Copying all components from entity " << fromSearch->first << " to entity " << m_lastResearchEntity->first << ":\n";

			for(std::unique_ptr<GraphicComponent> &currentComponent: fromSearch->second) { 

				m_logWriter << "\t" << currentComponent.get() << " copied as ";
				m_lastResearchEntity->second.emplace_back(currentComponent->clone());
				m_logWriter << m_lastResearchEntity->second.back().get() << "\n";
			}
		}
	}
}

void GraphicSystem::deleteEntity(const Entity &entity) {

	if(isInSystem(entity)) {

		m_logWriter << " Deleting entity " << m_lastResearchEntity->first << " of the system.\n";

		m_datas.erase(m_lastResearchEntity);
		m_lastResearchEntity = m_datas.end();
	}
}












bool GraphicSystem::isInSystem(const Entity &entity) {

	for(std::list<EntityAndComponent>::iterator it{m_datas.begin()}; it != m_datas.end(); it++) {

		if(it->first == entity) { m_lastResearchEntity = it; return true; }
	}

	m_lastResearchEntity = m_datas.end();
	return false;
}


bool GraphicSystem::haveComponent(const Entity &entity, const std::string &name) { 

	if(isInSystem(entity)) {

		for(const std::unique_ptr<GraphicComponent> &currentComponent: m_lastResearchEntity->second) {

			if(currentComponent->isNamed(name)) { return true; }
		}
	}

	return false;
}











void GraphicSystem::setPosition(const Entity &entity, const sf::Vector2f newPosition) {

	if(isInSystem(entity)) {

		m_logWriter << "Changing position of entity " << m_lastResearchEntity->first << " to (" << newPosition.x << ", " << newPosition.y << ").\n";

		for(std::unique_ptr<GraphicComponent> &currentComponent: m_lastResearchEntity->second) { currentComponent->setPosition(newPosition); }
	}
}

void GraphicSystem::rotate(const Entity &entity, const float rotation) {

	if(isInSystem(entity)) {

		m_logWriter << "Rotate entity " << m_lastResearchEntity->first << " of " << rotation << " degrees.\n";

		for(std::unique_ptr<GraphicComponent> &currentComponent: m_lastResearchEntity->second) { currentComponent->rotate(rotation); }
	}
}

void GraphicSystem::syncTextureRotation(const Entity &entity) {

	if(isInSystem(entity)) {

		m_logWriter << "Synchronize entity " << m_lastResearchEntity->first << " texture to its rotations.\n";

		for(std::unique_ptr<GraphicComponent> &currentComponent: m_lastResearchEntity->second) { currentComponent->synchronizeTextureRotation(); }
	}
}












void GraphicSystem::drawComponents(sf::RenderTarget &target) const {

	for(const EntityAndComponent &currentEntity: m_datas) {

		for(const std::unique_ptr<GraphicComponent> &currentComponent: currentEntity.second) {

			target.draw(*currentComponent);
		}
	}
}

void GraphicSystem::update(const unsigned int elapsedNanoTime) {

	for(const EntityAndComponent &currentEntity: m_datas) {

		for(const std::unique_ptr<GraphicComponent> &currentComponent: currentEntity.second) {

			currentComponent->update(elapsedNanoTime);
		}
	}
}