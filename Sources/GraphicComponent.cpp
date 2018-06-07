#include "GraphicComponent.hpp"

GraphicComponent::GraphicComponent(): 
	m_name{"Invalid"},
	m_texture{nullptr} {}

GraphicComponent::GraphicComponent(const std::string &name, std::shared_ptr<sf::Texture> texture): 
	m_name{name},
	m_texture{texture} {}

GraphicComponent::GraphicComponent(const GraphicComponent &component): 
	m_name{component.m_name},
	m_texture{component.m_texture} {}

GraphicComponent &GraphicComponent::operator=(const GraphicComponent &component) {

	const_cast<std::string&>(m_name) = component.m_name;
	m_texture = component.m_texture;

	return *this;
}

bool GraphicComponent::isNamed(const std::string &possibleName) const { return (m_name == possibleName); }