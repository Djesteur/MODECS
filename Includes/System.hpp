/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <list>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"

#include "Graphic/GraphicFactory.hpp"

#include "LogWriter.hpp"

template <typename C>
using EntityAndComponent = std::pair<Entity, std::list<std::unique_ptr<T>>>;
//Entity as ID with a list of component

template <typename C, typename F>
class System {

	public:

		System(const System &) = delete;
		System &operator=(const System &) = delete;

		System();

		//Adding, copying and deleting

		void addEntity(const Entity &entity);
		void addComponent(const Entity &entity, std::map<std::string, std::string> &factoryParam);
		void copyAllComponents(const Entity &from, const Entity &to);
		void deleteEntity(const Entity &entity);

		//Checkers

		bool isInSystem(const Entity &entity);
		bool haveComponent(const Entity &entity, const std::string &name);

		//Apply to 1 component

		void setPosition(const Entity &entity, const sf::Vector2f newPosition);
		void rotate(const Entity &entity, const float rotation);
		void syncTextureRotation(const Entity &entity);


		//Apply to all components
		
		void drawComponents(sf::RenderTarget &target) const;
		void update(const unsigned int elapsedNanoTime);

	private:

		std::list<EntityAndComponent> m_datas;

		GraphicFactory m_factory;

		LogWriter m_logWriter;

		std::list<EntityAndComponent>::iterator m_lastResearchEntity;
};


#endif