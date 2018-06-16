/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef TEXTUREKEEPER_HPP
#define TEXTUREKEEPER_HPP

#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "LogWriter.hpp"

class TextureKeeper {

	public:

		TextureKeeper(const TextureKeeper &) = delete;
		TextureKeeper &operator=(const TextureKeeper &) = delete;

		TextureKeeper();

		void loadTexture(const std::string name, const std::string path);
		std::shared_ptr<sf::Texture> getTexture(const std::string name);

	private:

		bool isLoaded(const std::string name);
		bool havePath(const std::string name);

		std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
		std::map<std::string, std::string> m_pathToTextures;

		LogWriter m_logWriter;
};

#endif