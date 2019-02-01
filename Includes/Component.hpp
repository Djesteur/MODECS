/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <memory>

class Component {

	public:

		Component();
		Component(const std::string &name);
		Component(const Component &component);
		Component &operator=(const Component &component);

		virtual std::unique_ptr<Component> clone() const = 0;

		bool isNamed(const std::string &possibleName) const;

	protected:

		const std::string m_name;
};

#endif