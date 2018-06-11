#ifndef GRAPHICCOMPONENT_HPP
#define GRAPHICCOMPONENT_HPP

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

class GraphicSystem;

class GraphicComponent: public sf::Drawable {

	public:

		GraphicComponent();
		GraphicComponent(const std::string &name, std::shared_ptr<sf::Texture> texture);
		GraphicComponent(const GraphicComponent &component);
		GraphicComponent &operator=(const GraphicComponent &component);

		virtual void setPosition(const sf::Vector2f newPosition) = 0;
		virtual void rotate(const float rotation) = 0;

		virtual void update(const unsigned int elapsedNanoTime) = 0;

		virtual std::unique_ptr<GraphicComponent> clone() const = 0;

		virtual void synchronizeTextureRotation();

		bool isNamed(const std::string &possibleName) const;

	protected:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

		const std::string m_name;

		std::shared_ptr<sf::Texture> m_texture;
};

#endif