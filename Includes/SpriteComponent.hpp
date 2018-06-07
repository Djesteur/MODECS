#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "GraphicComponent.hpp"

class SpriteComponent: public GraphicComponent {

	public:

		SpriteComponent();
		SpriteComponent(const std::string &name, std::shared_ptr<sf::Texture> texture);
		SpriteComponent(const SpriteComponent &component);
		SpriteComponent &operator=(const SpriteComponent &component);

		virtual void setPosition(const sf::Vector2f newPosition);

		virtual void update(const unsigned int elapsedNanoTime);

	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		sf::Sprite m_sprite;

		//copie à gérer
};


#endif