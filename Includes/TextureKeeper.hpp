#ifndef TEXTUREKEEPER_HPP
#define TEXTUREKEEPER_HPP

#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>

class TextureKeeper {

	public:

		TextureKeeper();
		~TextureKeeper();

		void loadTexture(const std::string name, const std::string path);
		std::shared_ptr<sf::Texture> getTexture(const std::string name);

		//Rajouter un fichier pour faire la correspondance: nom texture/chemin

	private:

		bool isLoaded(const std::string name);

		std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
		std::ofstream m_logFile;
};


#endif