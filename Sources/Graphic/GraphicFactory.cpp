#include "Graphic/GraphicFactory.hpp"

GraphicFactory::GraphicFactory(const std::string logPath): m_logWriter{logPath} {}

std::unique_ptr<GraphicComponent> GraphicFactory::newComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newComponent{nullptr};

	try {

		if(factoryParam.find("Name") != factoryParam.end()) {

			if(factoryParam.find("Type") != factoryParam.end()) {

				std::string type{factoryParam.find("Type")->second};

				if(type == "Sprite") { newComponent = createSpriteComponent(factoryParam); }
				else if(type == "VertexArray") { newComponent = createVertexArrayComponent(factoryParam); }
				else { throw "unknown type " + type; }

				if(newComponent == nullptr) { throw " problem with construction of " + type; }
			}

			else { throw "can't find agument \"Type\""; }
		}

		else { throw "can't find argument \"Name\""; }
	}

	catch(const std::string &error) {  m_logWriter << "ERROR: " << error << " with arguments:\n"; }

	writeArgumentsToLog(factoryParam);

	return newComponent;
}

std::unique_ptr<GraphicComponent> GraphicFactory::createSpriteComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newSpriteComponent{nullptr};
	const std::vector<std::string> argumentsToCheck{"TextureName"};

	try {

		if(checkArguments(factoryParam, argumentsToCheck)) {

			newSpriteComponent = std::make_unique<SpriteComponent>(factoryParam.find("Name")->second, m_textureKeeper.getTexture(factoryParam.find("TextureName")->second));
			m_logWriter << "Creating new sprite at adress " << newSpriteComponent.get() << " with arguments:\n";
		}

		else { throw "arguments missing"; }
	}

	catch(const std::string &error) { m_logWriter << "ERROR: " << error << "\n"; }

	return newSpriteComponent;
}

std::unique_ptr<GraphicComponent> GraphicFactory::createVertexArrayComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newVertexArrayComponent{nullptr};
	const std::vector<std::string> argumentsToCheck{"TextureName"};

	try {

		if(checkArguments(factoryParam, argumentsToCheck)) {

			sf::VertexArray array;
			const std::string arrayType{factoryParam.find("VertexArrayType")->second};

			if(arrayType == "Points") { array.setPrimitiveType(sf::Points); }
			if(arrayType == "Lines") { array.setPrimitiveType(sf::Lines); }
			if(arrayType == "LineStrip") { array.setPrimitiveType(sf::LineStrip); }
			if(arrayType == "Triangles") { array.setPrimitiveType(sf::Triangles); }
			if(arrayType == "TrianglesStrip") { array.setPrimitiveType(sf::TrianglesStrip); }
			if(arrayType == "TriangleFan") { array.setPrimitiveType(sf::TriangleFan); }
			if(arrayType == "Quads") { array.setPrimitiveType(sf::Quads); }

			const unsigned int nbVertices{static_cast<unsigned int>(std::stoul(factoryParam.find("VertexNumber")->second))};

			array.resize(nbVertices);

			std::string splitedDatas;

			for(unsigned int i{0}; i < nbVertices; i++) {

				if(factoryParam.find("VerticePosition!" + std::to_string(i) + "!X") != factoryParam.end() 
				&& factoryParam.find("VerticePosition!" + std::to_string(i) + "!Y") != factoryParam.end()) {

					array[i].position = sf::Vector2f{std::stof(factoryParam.find("VerticePosition!" + std::to_string(i) + "!X")->second),
													 std::stof(factoryParam.find("VerticePosition!" + std::to_string(i) + "!Y")->second)};
				}

				else { m_logWriter << "WARNING: missing position for vertice " << i << ".\n"; }
			}

			//Use texture

			if(factoryParam.find("TextureName") != factoryParam.end()) {

				for(unsigned int i{0}; i < nbVertices; i++) {

					if(factoryParam.find("VerticeTexture!" + std::to_string(i) + "!X") != factoryParam.end() &&
					   factoryParam.find("VerticeTexture!" + std::to_string(i) + "!Y") != factoryParam.end()) {

						array[i].texCoords = sf::Vector2f{std::stof(factoryParam.find("VerticeTexture!" + std::to_string(i) + "!X")->second),
													      std::stof(factoryParam.find("VerticeTexture!" + std::to_string(i) + "!Y")->second)};
					}

					else { m_logWriter << "WARNING: missing texture position for vertice " << i << ".\n"; }
				}

				newVertexArrayComponent = std::make_unique<VertexArrayComponent>(factoryParam.find("Name")->second, 
																				 m_textureKeeper.getTexture(factoryParam.find("TextureName")->second), 
																				 array);
			}

			//Use color

			else { 

				for(unsigned int i{0}; i < nbVertices; i++) {

					if(factoryParam.find("VerticeColor!" + std::to_string(i)) != factoryParam.end()) {

						array[i].color = sf::Color{static_cast<sf::Uint32>(convertStringHexToUnsigned(factoryParam.find("VerticeColor!" + std::to_string(i))->second))};
					}

					else { m_logWriter << "WARNING: missing color for vertice " << i << ".\n"; }
				}

				newVertexArrayComponent = std::make_unique<VertexArrayComponent>(factoryParam.find("Name")->second, array);
			}

			m_logWriter << "Creating new VertexArray at adress " << newVertexArrayComponent.get() << " with arguments: \n";
		}

		else { throw "arguments missing"; }
	}

	catch(const std::string &error) { m_logWriter << "ERROR: " << error << "\n"; }

	return newVertexArrayComponent;
}

bool GraphicFactory::checkArguments(const std::map<std::string, std::string> &factoryParam, const std::vector<std::string> argumentsToCheck) {

	for(std::string currentArgument: argumentsToCheck) {

		if(factoryParam.find(currentArgument) == factoryParam.end()) { return false; }
	}

	return true;
}

void GraphicFactory::writeArgumentsToLog(const std::map<std::string, std::string> &factoryParam) {

	for(std::pair<std::string, std::string> currentParam: factoryParam) {

		m_logWriter << '\t' << currentParam.first << " " << currentParam.second << '\n'; 
	}

}