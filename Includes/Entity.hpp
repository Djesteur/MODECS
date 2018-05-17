#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <vector>

class EntityKeeper;

class Entity {

	public:

		Entity(const unsigned int id = 0);
		Entity(const Entity &entity);
		Entity& operator=(const Entity &entity);

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

		std::shared_ptr<Entity> m_parent;
		std::vector<std::shared_ptr<Entity>> m_children;

		std::shared_ptr<Entity> m_redirection;
		// Si != nullptr, alors c'est une copie. On ne veut pas modifier la copie, mais l'original.
};


#endif