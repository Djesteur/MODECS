#include "Graphic/VertexArrayComponent.hpp"

VertexArrayComponent::VertexArrayComponent(): 
	GraphicComponent(),
	m_usingTexture{false},
	m_currentRotation{0.f},
	m_currentCenter{0.f, 0.f} {}

VertexArrayComponent::VertexArrayComponent(const std::string &name, std::shared_ptr<sf::Texture> texture, sf::VertexArray array):
	GraphicComponent(name, texture),
	m_array{array},
	m_borders{sf::LinesStrip},
	m_usingTexture{true},
	m_currentRotation{0.f},
	m_currentCenter{0.f, 0.f} {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_originalPosition.emplace_back(array[i].position); }

		//Borders

		if(m_array.getPrimitiveType() == sf::TrianglesFan) { m_borders.resize(m_array.getVertexCount()-1); }
		else { m_borders.resize(m_array.getVertexCount()+1); }

		for(unsigned int i{0}; i < m_borders.getVertexCount(); i++) { m_borders[i].color = sf::Color::Black; }

		syncBorders();
	}

VertexArrayComponent::VertexArrayComponent(const std::string &name, sf::VertexArray array):
	GraphicComponent(name, nullptr),
	m_array{array},
	m_borders{sf::LinesStrip},
	m_usingTexture{false},
	m_currentRotation{0.f},
	m_currentCenter{0.f, 0.f} {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_originalPosition.emplace_back(array[i].position); }

		//Borders

		if(m_array.getPrimitiveType() == sf::TrianglesFan) { m_borders.resize(m_array.getVertexCount()-1); }
		else { m_borders.resize(m_array.getVertexCount()+1); }

		for(unsigned int i{0}; i < m_borders.getVertexCount(); i++) { m_borders[i].color = sf::Color::Black; }

		syncBorders();
	}

VertexArrayComponent::VertexArrayComponent(const VertexArrayComponent &component): 
	GraphicComponent(component.m_name, component.m_texture),
	m_array{component.m_array},
	m_borders{component.m_borders},
	m_usingTexture{component.m_usingTexture},
	m_originalPosition{component.m_originalPosition},
	m_currentRotation{0.f},
	m_currentCenter{0.f, 0.f} {}

VertexArrayComponent &VertexArrayComponent::operator=(const VertexArrayComponent &component) {

	GraphicComponent::operator=(component);
	m_array = component.m_array;
	m_borders = component.m_borders;
	const_cast<bool&>(m_usingTexture) = component.m_usingTexture;
	m_originalPosition = component.m_originalPosition;
	m_currentRotation = component.m_currentRotation;
	m_currentCenter = component.m_currentCenter;
	return *this;
}

std::unique_ptr<GraphicComponent> VertexArrayComponent::clone() const { return std::make_unique<VertexArrayComponent>(*this); }

void VertexArrayComponent::setPosition(const sf::Vector2f newPosition) {

	sf::Vector2f diff{newPosition - m_currentCenter}; 

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_array[i].position += diff; }
		
	m_currentCenter = newPosition;
	syncBorders();
}

void VertexArrayComponent::rotate(const float rotation) {

	m_currentRotation += rotation;

	sf::Vector2f newPosition{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) {

		newPosition.x = m_originalPosition[i].x*cos(m_currentRotation*PI/180.f) - m_originalPosition[i].y*sin(m_currentRotation*PI/180.f);
		newPosition.y = m_originalPosition[i].x*sin(m_currentRotation*PI/180.f) + m_originalPosition[i].y*cos(m_currentRotation*PI/180.f);

		m_array[i].position = m_currentCenter + newPosition;
	}

	syncBorders();
}

void VertexArrayComponent::synchronizeTextureRotation() {

	sf::Vector2f center{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { center += m_array[i].texCoords; }

	center /= static_cast<float>(m_array.getVertexCount());

	sf::Vector2f newPosition{0.f, 0.f}, diff{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) {

		diff = m_array[i].texCoords - center;

		newPosition.x = center.x + diff.x*cos(m_currentRotation*PI/180.f) - diff.y*sin(m_currentRotation*PI/180.f);
		newPosition.y = center.y + diff.x*sin(m_currentRotation*PI/180.f) + diff.y*cos(m_currentRotation*PI/180.f);

		m_array[i].texCoords = newPosition;
	}
}

void VertexArrayComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const { 

	if(m_usingTexture) { states.texture = m_texture.get(); }

	target.draw(m_array, states);
	target.draw(m_borders);
}

void VertexArrayComponent::syncBorders() {

	if(m_array.getPrimitiveType() == sf::TrianglesFan) {

		for(unsigned int i{0}; i < m_borders.getVertexCount(); i++) { m_borders[i].position = m_array[i+1].position; }
	}

	else {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_borders[i].position = m_array[i].position; }
		m_borders[m_borders.getVertexCount()-1].position = m_array[0].position;
	}
}