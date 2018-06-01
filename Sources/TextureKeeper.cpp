#include "TextureKeeper.hpp"	

TextureKeeper::TextureKeeper(): m_logFile{"Output/TextureKeeper"} {}

TextureKeeper::~TextureKeeper() { m_logFile.close(); }

std::shared_ptr<sf::Texture> TextureKeeper::getTexture(const std::string name) {

	//A Rajouter: correspondance nom -> fichier

	bool isValid{false};

	if(!isLoaded(name)) {

		m_textures.insert(std::make_pair(name, std::make_shared<sf::Texture>()));
		m_logFile << "Load texture named " << name << std::endl;

		if(!m_textures[name]->loadFromFile(name)) { 

			m_logFile << "Warning: Can't load texture named " << name << std::endl; 
			m_textures.erase(name);
		}

		else { isValid = true; }
	}

	else { isValid = true; }

	if(isValid) { return m_textures[name]; }

	return nullptr;
}

bool TextureKeeper::isLoaded(const std::string name) {

	if(m_textures.find(name) != m_textures.end()) { return true; }

	return false;
}