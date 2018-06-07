#include "GraphicFactory.hpp"

GraphicFactory::GraphicFactory(): m_logWriter{"Output/Graphics/Factory"} {}

std::unique_ptr<GraphicComponent> GraphicFactory::newGraphicComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newComponent{nullptr};

	if(factoryParam.find("Name") != factoryParam.end()) {

		if(factoryParam.find("Type")->second == "Sprite") { newComponent = createSpriteComponent(factoryParam); }
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

/*std::unique_ptr<GraphicComponent> GraphicFactory::newGraphicComponent(const std::unique_ptr<GraphicComponent> base) {

	std::unique_ptr<GraphicComponent> newComponent{std::make_unique<GraphicComponent>(*base)};
	return newComponent;
}*/

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

void GraphicFactory::writeArgumentsToLog(const std::map<std::string, std::string> &factoryParam) {

	for(std::pair<std::string, std::string> currentPair: factoryParam) {

		m_logWriter << "\t" + currentPair.first << " - " << currentPair.second << "\n";
	}
}