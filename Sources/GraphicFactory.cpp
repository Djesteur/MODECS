#include "GraphicFactory.hpp"

GraphicFactory::GraphicFactory(): m_logWriter{"Output/Graphics/Factory"} {}

std::unique_ptr<GraphicComponent> GraphicFactory::newGraphicComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newComponent{nullptr};

	if(factoryParam.find("Name") != factoryParam.end()) {

		if(factoryParam.find("Type")->second == "Sprite") { newComponent = createSpriteComponent(factoryParam); }
		if(factoryParam.find("Type")->second == "VertexArray") { newComponent = createVertexArrayComponent(factoryParam); }
	}

	if(newComponent != nullptr) { //Sinon, type invalide ou paramètre manquant

		//Rajouter des attributs commun à tous les composants graphiques (position, ...)
		//currentEntity.second.back()->m_sprite.setPosition(sf::Vector2f{std::stof(factoryParam["PosX"]), std::stof(factoryParam["PosY"])});

		if(factoryParam.find("PosX") != factoryParam.end() && factoryParam.find("PosY") != factoryParam.end()) {

			newComponent->setPosition(sf::Vector2f{std::stof(factoryParam.find("PosX")->second), std::stof(factoryParam.find("PosY")->second)});
		}
	}

	return newComponent;
}

std::unique_ptr<GraphicComponent> GraphicFactory::createSpriteComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newSpriteComponent{nullptr};

	if(factoryParam.find("TextureName") != factoryParam.end()) {

		newSpriteComponent = std::make_unique<SpriteComponent>(factoryParam.find("Name")->second, m_textureKeeper.getTexture(factoryParam.find("TextureName")->second));
		m_logWriter << "Creating new sprite at adress " << std::to_string(reinterpret_cast<std::uintptr_t>(newSpriteComponent.get())) << " with arguments: \n";
		writeArgumentsToLog(factoryParam);
		//Rajouter rectangle sur la texture
	}

	return newSpriteComponent;
}

std::unique_ptr<GraphicComponent> GraphicFactory::createVertexArrayComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newVertexArrayComponent{nullptr};

	if(factoryParam.find("VertexArrayType") != factoryParam.end() && factoryParam.find("VertexNumber") != factoryParam.end()) {

		sf::VertexArray array;

		if(factoryParam.find("VertexArrayType")->second == "LineStrip") { array.setPrimitiveType(sf::LineStrip); }
		if(factoryParam.find("VertexArrayType")->second == "TriangleFan") { array.setPrimitiveType(sf::TriangleFan); }
		//Mettre les autres types

		const unsigned int nbVertices{static_cast<unsigned int>(std::stoul(factoryParam.find("VertexNumber")->second))};

		array.resize(nbVertices);

		std::string splitedDatas;

		for(unsigned int i{0}; i < nbVertices; i++) {

			if(factoryParam.find("VerticePosition-" + std::to_string(i) + "-X") != factoryParam.end() 
			&& factoryParam.find("VerticePosition-" + std::to_string(i) + "-Y") != factoryParam.end()) {

				array[i].position = sf::Vector2f{std::stof(factoryParam.find("VerticePosition-" + std::to_string(i) + "-X")->second),
												 std::stof(factoryParam.find("VerticePosition-" + std::to_string(i) + "-Y")->second)};
			}

			if(factoryParam.find("VerticeColor-" + std::to_string(i)) != factoryParam.end()) {

				array[i].color = sf::Color{static_cast<sf::Uint32>(convertStringHexToUnsigned(factoryParam.find("VerticeColor-" + std::to_string(i))->second))};
			}
		}

		if(factoryParam.find("TextureName") != factoryParam.end()) {

			newVertexArrayComponent = std::make_unique<VertexArrayComponent>(factoryParam.find("Name")->second, 
																			 m_textureKeeper.getTexture(factoryParam.find("TextureName")->second), 
																			 array);
		}

		else { 

			newVertexArrayComponent = std::make_unique<VertexArrayComponent>(factoryParam.find("Name")->second,array);
		}

		m_logWriter << "Creating new VertexArray at adress " << std::to_string(reinterpret_cast<std::uintptr_t>(newVertexArrayComponent.get())) << " with arguments: \n";
		writeArgumentsToLog(factoryParam);
		//Rajouter rectangle sur la texture
	}

	return newVertexArrayComponent;
}

void GraphicFactory::writeArgumentsToLog(const std::map<std::string, std::string> &factoryParam) {

	for(std::pair<std::string, std::string> currentPair: factoryParam) {

		m_logWriter << "\t" + currentPair.first << " - " << currentPair.second << "\n";
	}
}

std::vector<std::string> splitDatas(const std::string &datas, const char spliter) {

	std::stringstream ss{datas};
    std::string currentData;
    std::vector<std::string> splited;

    while (std::getline(ss, currentData, spliter)) { splited.push_back(currentData); }

    return splited;
}

unsigned int convertStringHexToUnsigned(const std::string &hexaString) {

	unsigned int result{0};

	std::istringstream iss{hexaString};
	iss >> std::setbase(16) >> result;

	return result;
}