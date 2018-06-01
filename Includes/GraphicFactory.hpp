#ifndef GRAPHICFACTORY_HPP
#define GRAPHICFACTORY_HPP

#include "TextureKeeper.hpp"
#include "SpriteComponent.hpp"

class GraphicFactory {

	public:

		GraphicFactory();

		std::unique_ptr<GraphicComponent> newGraphicComponent(const std::map<std::string, std::string> &factoryParam);

	private:

		std::unique_ptr<GraphicComponent> createSpriteComponent(const std::map<std::string, std::string> &factoryParam);

		TextureKeeper m_textureKeeper;
};


#endif