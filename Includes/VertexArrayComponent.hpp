#ifndef VERTEXARRAYCOMPONENT_HPP
#define VERTEXARRAYCOMPONENT_HPP

#include "GraphicComponent.hpp"

#define PI 3.14159264

class VertexArrayComponent: public GraphicComponent {

	public:

		VertexArrayComponent();
		VertexArrayComponent(const std::string &name, std::shared_ptr<sf::Texture> texture, sf::VertexArray array);
		VertexArrayComponent(const std::string &name, sf::VertexArray array);
		VertexArrayComponent(const VertexArrayComponent &component);
		VertexArrayComponent &operator=(const VertexArrayComponent &component);

		std::unique_ptr<GraphicComponent> clone() const;

		virtual void setPosition(const sf::Vector2f newPosition);
		virtual void rotate(const float rotation);

		virtual void synchronizeTextureRotation();

		virtual void update(const unsigned int elapsedNanoTime);

	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		sf::VertexArray m_array;
		const bool m_usingTexture;

		std::vector<sf::Vector2f> m_originalPosition; //Needed for setPosition function
		float m_currentRotation;
		sf::Vector2f m_currentCenter;
};

#endif