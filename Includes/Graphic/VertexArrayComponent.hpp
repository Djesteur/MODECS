/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef VERTEXARRAYCOMPONENT_HPP
#define VERTEXARRAYCOMPONENT_HPP

#include "GraphicComponent.hpp"

#include "Utils/MathUtils.hpp"

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

	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		void syncBorders();

		sf::VertexArray m_array, m_borders;
		const bool m_usingTexture;

		std::vector<sf::Vector2f> m_originalPosition; //Needed for setPosition function
		float m_currentRotation;
		sf::Vector2f m_currentCenter;
};

#endif