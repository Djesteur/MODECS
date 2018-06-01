#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const std::string &name, std::shared_ptr<sf::Texture> texture): 
	GraphicComponent(name, texture) {

		m_sprite.setTexture(*m_texture);
	}

void SpriteComponent::update(const unsigned int elapsedNanoTime) {}

void SpriteComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(m_sprite, states); }