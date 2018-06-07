#include "VertexArrayComponent.hpp"

VertexArrayComponent::VertexArrayComponent(): GraphicComponent() {}

VertexArrayComponent::VertexArrayComponent(const std::string &name, std::shared_ptr<sf::Texture> texture, sf::VertexArray array):
	GraphicComponent(name, texture),
	m_array{array} {}

VertexArrayComponent::VertexArrayComponent(const std::string &name, sf::VertexArray array):
	GraphicComponent(name, nullptr),
	m_array{array} {}

VertexArrayComponent::VertexArrayComponent(const VertexArrayComponent &component): 
	GraphicComponent(component.m_name, component.m_texture) {}

VertexArrayComponent &VertexArrayComponent::operator=(const VertexArrayComponent &component) {

	GraphicComponent::operator=(component);
	return *this;
}


void VertexArrayComponent::setPosition(const sf::Vector2f newPosition) {  }

void VertexArrayComponent::update(const unsigned int elapsedNanoTime) {}

void VertexArrayComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(m_array, states); }