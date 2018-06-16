/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef GRAPHICSYSTEM_HPP
#define GRAPHICSYSTEM_HPP

#include <list>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"

#include "Graphic/GraphicFactory.hpp"

#include "LogWriter.hpp"

using EntityAndComponent = std::pair<Entity, std::list<std::unique_ptr<GraphicComponent>>>;

class GraphicSystem {

	public:

		GraphicSystem(const GraphicSystem &) = delete;
		GraphicSystem &operator=(const GraphicSystem &) = delete;

		GraphicSystem();

		void update(const unsigned int elapsedNanoTime);

		void addEntity(const Entity &entity);
		void addComponent(const Entity &entity, std::map<std::string, std::string> &factoryParam);

		void deleteEntity(const Entity &entity);

		bool isInSystem(const Entity &entity) const;
		bool haveComponent(const Entity &entity, const std::string &name) const;

		void drawComponents(sf::RenderWindow &window) const;

		void copyAllComponents(const Entity &from, const Entity &to);

		void setPosition(const Entity &entity, const sf::Vector2f newPosition);
		void rotate(const Entity &entity, const float rotation);
		void syncTextureRotation(const Entity &entity);

	private:

		std::list<EntityAndComponent> m_datas;

		GraphicFactory m_factory;

		LogWriter m_logWriter;

		//Entity as ID with a list of component
		//A optimiser: a chaque fois, on vérifie puis on applique l'operation, autant tout faire d'un coup
		//Log: informations dans le log ? necessite afficher Entity.m_ID
};


#endif