#include "GraphicComponent.hpp"

GraphicComponent::GraphicComponent(): 
	m_name{"Invalid"},
	m_texture{nullptr},
	m_drawBorders{false} {

		m_borders.setPrimitiveType(sf::LineStrip);
	}

GraphicComponent::GraphicComponent(const std::string &name, std::shared_ptr<sf::Texture> texture): 
	m_name{name},
	m_texture{texture},
	m_drawBorders{false} {

		m_borders.setPrimitiveType(sf::LineStrip);
	}

GraphicComponent::GraphicComponent(const GraphicComponent &component): 
	m_name{component.m_name},
	m_texture{component.m_texture},
	m_drawBorders{component.m_drawBorders},
	m_borders{component.m_borders} {}

GraphicComponent &GraphicComponent::operator=(const GraphicComponent &component) {

	const_cast<std::string&>(m_name) = component.m_name;
	m_texture = component.m_texture;
	m_drawBorders = component.m_drawBorders;
	m_borders = component.m_borders;

	return *this;
}

bool GraphicComponent::isNamed(const std::string &possibleName) const { return (m_name == possibleName); }

void GraphicComponent::synchronizeTextureRotation() {}

void GraphicComponent::haveToDrawBorders(const bool borders) { m_drawBorders = borders; }