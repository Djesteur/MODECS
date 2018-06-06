#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "GraphicComponent.hpp"

class GraphicSystem;

class SpriteComponent: public GraphicComponent {

	public:

		SpriteComponent(const std::string &name, std::shared_ptr<sf::Texture> texture);

		virtual void update(const unsigned int elapsedNanoTime);

	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		sf::Sprite m_sprite;

		//copie à gérer
};


#endif