#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(): GraphicComponent() {}

SpriteComponent::SpriteComponent(const std::string &name, std::shared_ptr<sf::Texture> texture): 
	GraphicComponent(name, texture) {

		m_sprite.setTexture(*m_texture);
	}

SpriteComponent::SpriteComponent(const SpriteComponent &component): 
	GraphicComponent(component.m_name, component.m_texture) {

		m_sprite.setTexture(*m_texture);
	}

SpriteComponent &SpriteComponent::operator=(const SpriteComponent &component) {

	GraphicComponent::operator=(component);
	m_sprite.setTexture(*m_texture);
	return *this;
}

std::unique_ptr<GraphicComponent> SpriteComponent::clone() const { return std::make_unique<SpriteComponent>(*this); }

void SpriteComponent::setPosition(const sf::Vector2f newPosition) { m_sprite.setPosition(newPosition); }
void SpriteComponent::rotate(const float rotation) { m_sprite.rotate(rotation); }

void SpriteComponent::update(const unsigned int elapsedNanoTime) {}

void SpriteComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(m_sprite, states); }