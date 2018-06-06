#include "GraphicSystem.hpp"

GraphicSystem::GraphicSystem(): m_logWriter{"Output/Graphics/System"} {}

void GraphicSystem::update(const unsigned int elapsedNanoTime) {}
void GraphicSystem::addComponent(const Entity &entity, std::map<std::string, std::string> &factoryParam) {

	if(isInSystem(entity)) {

		for(EntityAndComponent &currentEntity: m_datas) {

			if(currentEntity.first == entity) {

				currentEntity.second.emplace_back(m_factory.newGraphicComponent(factoryParam));
			}
		}
	}
}

void GraphicSystem::addEntity(const Entity &entity) { m_datas.emplace_back(std::make_pair(entity, std::list<std::unique_ptr<GraphicComponent>>{})); }

bool GraphicSystem::isInSystem(const Entity &entity) const {

	for(const EntityAndComponent &currentEntity: m_datas) {

		if(currentEntity.first == entity) { return true; }
	}

	return false;
}

bool GraphicSystem::haveComponent(const Entity &entity, const std::string &name) const { 

	if(!isInSystem(entity)) { return false; }
	else {

		for(const EntityAndComponent &currentEntity: m_datas) {

			if(currentEntity.first == entity) {

				for(const std::unique_ptr<GraphicComponent> &currentComponent: currentEntity.second) {

					if(currentComponent->isNamed(name)) { return true; }
				}
			}
		}
	}

	return false;
}


void GraphicSystem::drawComponents(sf::RenderWindow &window) const {

	for(const EntityAndComponent &currentEntity: m_datas) {

		for(const std::unique_ptr<GraphicComponent> &currentComponent: currentEntity.second) {

			window.draw(*currentComponent);
		}
	}
}
