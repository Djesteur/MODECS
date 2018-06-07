#ifndef VERTEXARRAYCOMPONENT_HPP
#define VERTEXARRAYCOMPONENT_HPP

#include "GraphicComponent.hpp"

class VertexArrayComponent: public GraphicComponent {

	public:

		VertexArrayComponent();
		VertexArrayComponent(const std::string &name, std::shared_ptr<sf::Texture> texture, sf::VertexArray array);
		VertexArrayComponent(const std::string &name, sf::VertexArray array);
		VertexArrayComponent(const VertexArrayComponent &component);
		VertexArrayComponent &operator=(const VertexArrayComponent &component);

		virtual void setPosition(const sf::Vector2f newPosition);

		virtual void update(const unsigned int elapsedNanoTime);

	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		sf::VertexArray m_array;
		//const bool m_usingTexture;

		//copie à gérer
};

#endif