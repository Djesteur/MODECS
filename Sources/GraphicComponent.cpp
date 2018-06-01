#include "GraphicComponent.hpp"

GraphicComponent::GraphicComponent(const std::string &name, std::shared_ptr<sf::Texture> texture): 
	m_name{name},
	m_texture{texture} {}

bool GraphicComponent::isNamed(const std::string &possibleName) const { return (m_name == possibleName); }