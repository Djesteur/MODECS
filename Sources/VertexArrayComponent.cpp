#include "VertexArrayComponent.hpp"

VertexArrayComponent::VertexArrayComponent(): 
	GraphicComponent(),
	m_usingTexture{false} {}

VertexArrayComponent::VertexArrayComponent(const std::string &name, std::shared_ptr<sf::Texture> texture, sf::VertexArray array):
	GraphicComponent(name, texture),
	m_array{array},
	m_usingTexture{true} {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_originalPosition.emplace_back(array[i].position); }
	}

VertexArrayComponent::VertexArrayComponent(const std::string &name, sf::VertexArray array):
	GraphicComponent(name, nullptr),
	m_array{array},
	m_usingTexture{false} {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_originalPosition.emplace_back(array[i].position); }
	}

VertexArrayComponent::VertexArrayComponent(const VertexArrayComponent &component): 
	GraphicComponent(component.m_name, component.m_texture),
	m_array{component.m_array},
	m_usingTexture{component.m_usingTexture},
	m_originalPosition{component.m_originalPosition} {}

VertexArrayComponent &VertexArrayComponent::operator=(const VertexArrayComponent &component) {

	GraphicComponent::operator=(component);
	const_cast<bool&>(m_usingTexture) = component.m_usingTexture;
	m_originalPosition = component.m_originalPosition;
	return *this;
}

void VertexArrayComponent::setPosition(const sf::Vector2f newPosition) { 

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_array[i].position = newPosition + m_originalPosition[i]; }
}

void VertexArrayComponent::update(const unsigned int elapsedNanoTime) {}

void VertexArrayComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const { 

	if(m_usingTexture) { states.texture = m_texture.get(); }

	target.draw(m_array, states);
}