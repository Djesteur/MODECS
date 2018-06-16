/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef GRAPHICFACTORY_HPP
#define GRAPHICFACTORY_HPP

#include <string>
#include <map>

#include "Graphic/TextureKeeper.hpp"
#include "Graphic/SpriteComponent.hpp"
#include "Graphic/VertexArrayComponent.hpp"

#include "Utils/StringUtils.hpp"

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

			- Animation (composant animation à faire)*/
};



#endif