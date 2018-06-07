#ifndef GRAPHICFACTORY_HPP
#define GRAPHICFACTORY_HPP

#include <string>
#include <iomanip>
#include <string>

#include "TextureKeeper.hpp"
#include "SpriteComponent.hpp"
#include "VertexArrayComponent.hpp"

#include "LogWriter.hpp"

class GraphicFactory {

	public:

		GraphicFactory(const GraphicFactory &) = delete;
		GraphicFactory &operator=(const GraphicFactory &) = delete;

		GraphicFactory();

		std::unique_ptr<GraphicComponent> newGraphicComponent(const std::map<std::string, std::string> &factoryParam);

	private:

		std::unique_ptr<GraphicComponent> createSpriteComponent(const std::map<std::string, std::string> &factoryParam);
		std::unique_ptr<GraphicComponent> createVertexArrayComponent(const std::map<std::string, std::string> &factoryParam);

		void writeArgumentsToLog(const std::map<std::string, std::string> &factoryParam);

		TextureKeeper m_textureKeeper;

		LogWriter m_logWriter;

		/* A rajouter:

			- Ajouter animation (composant animation à faire)*/
};

std::vector<std::string> splitDatas(const std::string &datas, const char spliter);
unsigned int convertStringHexToUnsigned(const std::string &hexaString);

#endif