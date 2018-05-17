#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <vector>
#include <iostream>

class EntityKeeper;

class Entity {

	public:

		Entity(const unsigned int id = 0);
		Entity(const Entity &entity);

		bool operator==(const Entity &entity);

		void changeParent(const Entity &newParent);
		void deleteParent();
		
		void addChild(const Entity &newChild);
		void deleteChild(const Entity &childToDelete);

		void deleteEntityWithBackup(const Entity &entityToDelete, const Entity &newParent);
		void deleteEntityWithoutBackup(const Entity &entityToDelete);

		bool haveChild(const Entity &child) const;

	private:

		friend class EntityKeeper;

		const unsigned int m_ID;

		Entity *m_parent;
		/*Obligation d'utiliser un pointer nu car:
			- Un smart pointer se construit en construisant un objet
			- Une référence ou reéférence_wrapper ne peut pas ne pas avoir de valeur
			*/
		std::vector<std::reference_wrapper<Entity>> m_children;

		const Entity *m_redirection;
		//Pour le pointeur nu, idem qu'au dessus
		// Si != nullptr, alors c'est une copie. On ne veut pas modifier la copie, mais l'original.
};


#endif