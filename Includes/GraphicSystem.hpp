#ifndef GRAPHICSYSTEM_HPP
#define GRAPHICSYSTEM_HPP

#include <list>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "GraphicFactory.hpp"

using EntityAndComponent = std::pair<Entity, std::list<std::unique_ptr<GraphicComponent>>>;

class GraphicSystem {

	public:

		GraphicSystem();

		void update(const unsigned int elapsedNanoTime);

		void addEntity(const Entity &entity);
		void addComponent(const Entity &entity, std::map<std::string, std::string> &factoryParam);

		bool isInSystem(const Entity &entity) const;
		bool haveComponent(const Entity &entity, const std::string &name) const;

		void drawComponents(sf::RenderWindow &window) const;

	private:

		std::list<EntityAndComponent> m_datas;

		GraphicFactory m_factory;


		//Entity as ID with a list of component
		//A optimiser: a chaque fois, on vérifie puis on applique l'operation, autant tout faire d'un coup
		//A Rajouter: sortie dans un fichier log
};


#endif