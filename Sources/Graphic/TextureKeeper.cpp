#include "Graphic/TextureKeeper.hpp"	

TextureKeeper::TextureKeeper(): m_logWriter{"Output/Graphics/TextureKeeper"} {

	//Redirect SFML output to file
	m_logWriter.addRDBuf(sf::err());

	//Creating error texture

	const unsigned int errorSize{64};

	sf::Image image;
	image.create(errorSize, errorSize, sf::Color::Magenta);

	for(unsigned int i{0}; i < errorSize; i++) {
		for(unsigned int j{0}; j < errorSize; j++) {

			if(i == j || i == errorSize - j || i == 0 || i == errorSize-1 || j == 0 || j == errorSize-1) {

				image.setPixel(i, j, sf::Color::Yellow);
			}
		}
	}

	m_textures.insert(std::make_pair("Invalid", std::make_shared<sf::Texture>()));
	m_textures["Invalid"]->loadFromImage(image);

	//Loading texture path

	std::ifstream correspondingPath{"Data/TexturePath"};

	if(!correspondingPath) { m_logWriter << "Warning: can't open the corresponding path file.\n"; }
	else {

		std::string currentData, textureName, texturePath;
		std::istringstream iss;

		while(std::getline(correspondingPath, currentData)) {

			iss.str(currentData);
			iss >> textureName >> texturePath;
			m_pathToTextures.insert(std::make_pair(textureName, texturePath));

			iss.clear();
		}

		m_logWriter << "Corresponding file loaded.\n";
	}
}

std::shared_ptr<sf::Texture> TextureKeeper::getTexture(const std::string name) {

	bool isValid{false};

	if(havePath(name)) {

		if(!isLoaded(name)) {

			m_textures.insert(std::make_pair(name, std::make_shared<sf::Texture>()));
			m_logWriter << "Load texture named " << name << "\n";

			if(!m_textures[name]->loadFromFile(m_pathToTextures[name])) { 

				m_logWriter << "Warning: Can't load texture named " << name << " with path: " << m_pathToTextures[name] << "\n"; 
			}

			else { isValid = true; }
		}

		else { isValid = true; }
	}

	else { m_logWriter << "Asking for texture " << name << ", which have an unknow path.\n"; }

	if(isValid) { return m_textures[name]; }

	return m_textures["Invalid"];
}

bool TextureKeeper::isLoaded(const std::string name) {

	if(m_textures.find(name) != m_textures.end()) { return true; }

	return false;
}

bool TextureKeeper::havePath(const std::string name) {

	if(m_pathToTextures.find(name) != m_pathToTextures.end()) { return true; }

	return false;
}