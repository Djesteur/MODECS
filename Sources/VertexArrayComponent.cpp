#include "VertexArrayComponent.hpp"

VertexArrayComponent::VertexArrayComponent(): 
	GraphicComponent(),
	m_usingTexture{false},
	m_currentRotation{0.f} {}

VertexArrayComponent::VertexArrayComponent(const std::string &name, std::shared_ptr<sf::Texture> texture, sf::VertexArray array):
	GraphicComponent(name, texture),
	m_array{array},
	m_usingTexture{true},
	m_currentRotation{0.f} {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_originalPosition.emplace_back(array[i].position); }
	}

VertexArrayComponent::VertexArrayComponent(const std::string &name, sf::VertexArray array):
	GraphicComponent(name, nullptr),
	m_array{array},
	m_usingTexture{false},
	m_currentRotation{0.f} {

		for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_originalPosition.emplace_back(array[i].position); }
	}

VertexArrayComponent::VertexArrayComponent(const VertexArrayComponent &component): 
	GraphicComponent(component.m_name, component.m_texture),
	m_array{component.m_array},
	m_usingTexture{component.m_usingTexture},
	m_originalPosition{component.m_originalPosition},
	m_currentRotation{0.f} {}

VertexArrayComponent &VertexArrayComponent::operator=(const VertexArrayComponent &component) {

	GraphicComponent::operator=(component);
	const_cast<bool&>(m_usingTexture) = component.m_usingTexture;
	m_originalPosition = component.m_originalPosition;
	m_currentRotation = component.m_currentRotation;
	return *this;
}

std::unique_ptr<GraphicComponent> VertexArrayComponent::clone() const { return std::make_unique<VertexArrayComponent>(*this); }

void VertexArrayComponent::setPosition(const sf::Vector2f newPosition) { 

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { m_array[i].position = newPosition + m_originalPosition[i]; }
}

void VertexArrayComponent::rotate(const float rotation) { 

	sf::Vector2f center{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { center += m_array[i].position; }

	center /= static_cast<float>(m_array.getVertexCount());

	sf::Vector2f newPosition{0.f, 0.f}, diff{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) {

		diff = center - m_array[i].position;

		newPosition.x = center.x + diff.x*cos((rotation + 180.f)*PI/180.f) - diff.y*sin((rotation + 180.f)*PI/180.f); //+ 180°, sinon à l'envers ???
		newPosition.y = center.y + diff.x*sin((rotation + 180.f)*PI/180.f) + diff.y*cos((rotation + 180.f)*PI/180.f);

		m_array[i].position = newPosition;
	}

	m_currentRotation += rotation;
}

void VertexArrayComponent::synchronizeTextureRotation() {

	sf::Vector2f center{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) { center += m_array[i].texCoords; }

	center /= static_cast<float>(m_array.getVertexCount());

	sf::Vector2f newPosition{0.f, 0.f}, diff{0.f, 0.f};

	for(unsigned int i{0}; i < m_array.getVertexCount(); i++) {

		diff = center - m_array[i].texCoords;

		newPosition.x = center.x + diff.x*cos((m_currentRotation + 180.f)*PI/180.f) - diff.y*sin((m_currentRotation + 180.f)*PI/180.f); //+ 180°, sinon à l'envers ???
		newPosition.y = center.y + diff.x*sin((m_currentRotation + 180.f)*PI/180.f) + diff.y*cos((m_currentRotation + 180.f)*PI/180.f);

		m_array[i].texCoords = newPosition;
	}
}

void VertexArrayComponent::update(const unsigned int elapsedNanoTime) {}

void VertexArrayComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const { 

	if(m_usingTexture) { states.texture = m_texture.get(); }

	target.draw(m_array, states);
}