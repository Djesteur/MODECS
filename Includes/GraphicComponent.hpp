#ifndef GRAPHICCOMPONENT_HPP
#define GRAPHICCOMPONENT_HPP

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

class GraphicSystem;

class GraphicComponent: public sf::Drawable {

	public:

		GraphicComponent(const std::string &name, std::shared_ptr<sf::Texture> texture);

		virtual void update(const unsigned int elapsedNanoTime) = 0;

		bool isNamed(const std::string &possibleName) const;

	protected:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

		const std::string m_name;

		std::shared_ptr<sf::Texture> m_texture;
};


#endif