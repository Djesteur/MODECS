/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "Graphic/GraphicComponent.hpp"

class SpriteComponent: public GraphicComponent {

	public:

		SpriteComponent();
		SpriteComponent(const std::string &name, std::shared_ptr<sf::Texture> texture);
		SpriteComponent(const SpriteComponent &component);
		SpriteComponent &operator=(const SpriteComponent &component);

		virtual std::unique_ptr<GraphicComponent> clone() const;

		virtual void setPosition(const sf::Vector2f newPosition);
		virtual void rotate(const float rotation);

	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		sf::Sprite m_sprite;

		//copie à gérer
};

#endif