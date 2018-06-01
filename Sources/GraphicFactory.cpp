#include "GraphicFactory.hpp"

GraphicFactory::GraphicFactory() {}

std::unique_ptr<GraphicComponent> GraphicFactory::newGraphicComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newComponent{nullptr};

	if(factoryParam.find("Name") != factoryParam.end()) {

		if(factoryParam.find("Type")->second == "Sprite") { newComponent = createSpriteComponent(factoryParam); }
	}

	if(newComponent != nullptr) { //Sinon, type invalide ou paramètre manquant

		//Rajouter des attributs commun à tous les composants graphiques (position, ...)
		//currentEntity.second.back()->m_sprite.setPosition(sf::Vector2f{std::stof(factoryParam["PosX"]), std::stof(factoryParam["PosY"])});
	}

	return newComponent;
}

std::unique_ptr<GraphicComponent> GraphicFactory::createSpriteComponent(const std::map<std::string, std::string> &factoryParam) {

	std::unique_ptr<GraphicComponent> newSpriteComponent{nullptr};

	if(factoryParam.find("Texture") != factoryParam.end()) {

		newSpriteComponent = std::make_unique<SpriteComponent>(factoryParam.find("Name")->second, m_textureKeeper.getTexture(factoryParam.find("Texture")->second));
		//Rajouter rectangle sur la texture
	}

	return newSpriteComponent;
}