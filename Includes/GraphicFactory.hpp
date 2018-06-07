#ifndef GRAPHICFACTORY_HPP
#define GRAPHICFACTORY_HPP

#include <string>

#include "TextureKeeper.hpp"
#include "SpriteComponent.hpp"

#include "LogWriter.hpp"

class GraphicFactory {

	public:

		GraphicFactory(const GraphicFactory &) = delete;
		GraphicFactory &operator=(const GraphicFactory &) = delete;

		GraphicFactory();

		std::unique_ptr<GraphicComponent> newGraphicComponent(const std::map<std::string, std::string> &factoryParam);
		//std::unique_ptr<GraphicComponent> newGraphicComponent(const std::unique_ptr<GraphicComponent> base);

	private:

		std::unique_ptr<GraphicComponent> createSpriteComponent(const std::map<std::string, std::string> &factoryParam);

		void writeArgumentsToLog(const std::map<std::string, std::string> &factoryParam);

		TextureKeeper m_textureKeeper;

		LogWriter m_logWriter;

		/* A rajouter:

			- Ajouter vertexVector
			- Ajouter animation (composant animation à faire)*/
};


#endif