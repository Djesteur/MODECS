#include "Map/MapLoader.hpp"

MapLoader::MapLoader(): m_logWriter{"Output/Map/MapLoader"} {}

std::list<Entity> MapLoader::loadGame(const std::string mapPath, EntityKeeper &keeper, MovementSystem &movementSystem) {

	const std::string endOfTile{"!!!"};
	std::list<Entity> tiles;

	//Constructing map

	unsigned int currentLine{0};

	try {

		std::ifstream tilesFile{mapPath};
		if(!tilesFile) { throw "Can't open tiles file \"" + mapPath + "\""; }

		std::string currentData;
		std::vector<std::string> newInformations;
		std::map<std::string, std::string> tileInformations;

		while(!tilesFile.eof()) {

			std::getline(tilesFile, currentData);
			currentLine++;

			while(currentData != endOfTile) {

				newInformations = splitDatas(currentData, '!');

				if(newInformations.size() != 2) { throw "Invalid information format \"" + currentData + "\""; }
				else { tileInformations.insert(std::make_pair(newInformations[0], newInformations[1])); }

				if(tilesFile.eof()) { throw "Invalid file format"; }

				std::getline(tilesFile, currentData);
				currentLine++;
			}

			tiles.push_back(keeper.newEntity());

			extractMovementInformations(tiles.back(), tileInformations, movementSystem);
		}

		if(currentData != endOfTile) { m_logWriter << "WARNING: the tile file have a bad end line.\n"; }
	}

	catch(const std::string &error) { 

		m_logWriter << "ERROR: " << error << " while loading map at line " << currentLine << ".\n";

		for(Entity &currentEntity: tiles) { 

			//movementSystem.deleteEntity(currentEntity);
			keeper.deleteEntity(currentEntity);
		}

		tiles.clear();
	}

	catch(const char *error) { 

		m_logWriter << "ERROR: " << error << " while loading map at line " << currentLine << ".\n";

		for(Entity &currentEntity: tiles) { 

			//movementSystem.deleteEntity(currentEntity);
			keeper.deleteEntity(currentEntity);
		}

		tiles.clear();
	}

	return tiles;
}

std::list<Entity> MapLoader::loadGraphics(const std::string mapPath, EntityKeeper &keeper, GraphicSystem &graphicSystem) { std::list<Entity> tiles; return tiles; }
std::list<Entity> MapLoader::loadSounds(const std::string mapPath, EntityKeeper &keeper) { std::list<Entity> tiles; return tiles; }

/*

std::map<std::string, Entity> MapLoader::constructExampleTiles(const std::string path, EntityKeeper &keeper, GraphicSystem &system, const unsigned int tileSize) {

	std::map<std::string, Entity> examples;
	std::map<std::string, std::string> tilesPath;

	unsigned int currentLine{0}; 

	try {

		//Load list of examples tiles

		std::ifstream examplesPath{path};

		if(examplesPath) {

			std::string currentData;

			while(std::getline(examplesPath, currentData)) {

				if(currentData != "!!!") {

					std::vector<std::string> splitedDatas{splitDatas(currentData, '!')};

					if(splitedDatas.size() == 2) { tilesPath.insert(std::make_pair(splitedDatas[0], splitedDatas[1])); }
					else { throw "invalid data at line " + currentLine; }
				}

				currentLine++;
			}
		}

		else { throw "can't open file" + path; }

		//Construct each example tile

		std::ifstream currentTileFile;
		std::string textureName, tileType, currentData;
		sf::Vector2f texturePositiont;

		for(std::pair<std::string, std::string> currentTile: tilesPath) {

			examples.insert(std::make_pair(currentTile.first, keeper.newEntity()));
			system.addEntity(examples[currentTile.first]);

			currentTileFile.open(currentTile.second);

			if(currentTileFile) {

				std::getline(currentTileFile, textureName);

				if(currentTileFile.eof()) { throw "invalid data format in file " + currentTile.second; }

				std::getline(currentTileFile, currentData);
				std::istringstream(currentData) >> texturePosition.x >> texturePosition.y;

				if(currentTileFile.eof()) { throw "invalid data format in file " + currentTile.second; }

				std::getline(currentTileFile, tileType);

				if(!currentTileFile.eof()) { throw "invalid data format in file " + currentTile.second; }

				std::map<std::string, std::string> componentDatas;

				if(tileType == "Hexagon") { componentDatas = constructHexa(textureName, texturePosition, tileSize); }
				if(tileType == "Square") { componentDatas = constructSquare(textureName, texturePosition, tileSize); }
				if(tileType == "Triangle") { componentDatas = constructTriangle(textureName, texturePosition, tileSize); }

				system.addComponent(examples[currentTile.first], componentDatas);

				currentTileFile.close();
			}

			else { throw "can't open file " + currentTile.second; }
		}
	}

	catch(const std::string &error) {

		m_logWriter << "ERROR: " << error << " while constructing examples.\n";

		for(std::pair<std::string, Entity> currentTile: examples) {

			system.deleteEntity(currentTile.second);
			keeper.deleteEntity(currentTile.second);
		}

		examples.clear();
	}

	return examples;
}
*/


void MapLoader::extractMovementInformations(const Entity &entity, const std::map<std::string, std::string> &informations, MovementSystem &positionSystem) {



}

/*

std::map<std::string, std::string> MapLoader::constructHexa(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size) {

	std::map<std::string, std::string> componentArguments;
	componentArguments.insert(std::make_pair("Type", "VertexArray"));
	componentArguments.insert(std::make_pair("Name", "GraphicTile"));
	componentArguments.insert(std::make_pair("TextureName", textureName));
	componentArguments.insert(std::make_pair("VertexArrayType", "TriangleFan"));
	componentArguments.insert(std::make_pair("VertexNumber", "8"));

	sf::Vector2f center{0, 0}, newPoint{center}, diff{0, 0};

	componentArguments.insert(std::make_pair("VerticePosition!0!X", std::to_string(newPoint.x)));
	componentArguments.insert(std::make_pair("VerticePosition!0!Y", std::to_string(newPoint.y)));
	componentArguments.insert(std::make_pair("VerticeTexture!0!X", std::to_string(textureCenter.x + newPoint.x)));
	componentArguments.insert(std::make_pair("VerticeTexture!0!Y", std::to_string(textureCenter.y + newPoint.y)));

	newPoint.x = center.x;
	newPoint.y = center.y + size;

	componentArguments.insert(std::make_pair("VerticePosition!1!X", std::to_string(newPoint.x)));
	componentArguments.insert(std::make_pair("VerticePosition!1!Y", std::to_string(newPoint.y)));
	componentArguments.insert(std::make_pair("VerticeTexture!1!X", std::to_string(textureCenter.x + newPoint.x)));
	componentArguments.insert(std::make_pair("VerticeTexture!1!Y", std::to_string(textureCenter.y + newPoint.y)));

	for(unsigned int i{0}; i < 6; i++) {

		diff = newPoint - center;

		newPoint.x = center.x + diff.x*cos(60.f*PI/180.f) - diff.y*sin(60.f*PI/180.f);
		newPoint.y = center.y + diff.x*sin(60.f*PI/180.f) + diff.y*cos(60.f*PI/180.f);

		componentArguments.insert(std::make_pair("VerticePosition!" + std::to_string(i+2) + "!X", std::to_string(newPoint.x)));
		componentArguments.insert(std::make_pair("VerticePosition!" + std::to_string(i+2) + "!Y", std::to_string(newPoint.y)));
		componentArguments.insert(std::make_pair("VerticeTexture!" + std::to_string(i+2) + "!X", std::to_string(textureCenter.x + newPoint.x)));
		componentArguments.insert(std::make_pair("VerticeTexture!" + std::to_string(i+2) + "!Y", std::to_string(textureCenter.y + newPoint.y)));
	}

	return componentArguments;
}

std::map<std::string, std::string> MapLoader::constructSquare(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size) {

	std::map<std::string, std::string> componentArguments;
	componentArguments.insert(std::make_pair("Type", "VertexArray"));
	componentArguments.insert(std::make_pair("Name", "GraphicTile"));
	componentArguments.insert(std::make_pair("TextureName", textureName));
	componentArguments.insert(std::make_pair("VertexArrayType", "Quads"));
	componentArguments.insert(std::make_pair("VertexNumber", "4"));

	componentArguments.insert(std::make_pair("VerticePosition!0!X", std::to_string(-static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticePosition!0!Y", std::to_string(-static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!0!X", std::to_string(textureCenter.x - static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!0!Y", std::to_string(textureCenter.y - static_cast<float>(size)/2.f)));

	componentArguments.insert(std::make_pair("VerticePosition!1!X", std::to_string(static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticePosition!1!Y", std::to_string(-static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!1!X", std::to_string(textureCenter.x + static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!1!Y", std::to_string(textureCenter.y - static_cast<float>(size)/2.f)));

	componentArguments.insert(std::make_pair("VerticePosition!2!X", std::to_string(static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticePosition!2!Y", std::to_string(static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!2!X", std::to_string(textureCenter.x + static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!2!Y", std::to_string(textureCenter.y + static_cast<float>(size)/2.f)));

	componentArguments.insert(std::make_pair("VerticePosition!3!X", std::to_string(-static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticePosition!3!Y", std::to_string(static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!3!X", std::to_string(textureCenter.x - static_cast<float>(size)/2.f)));
	componentArguments.insert(std::make_pair("VerticeTexture!3!Y", std::to_string(textureCenter.y + static_cast<float>(size)/2.f)));

	return componentArguments;
}


std::map<std::string, std::string> MapLoader::constructTriangle(const std::string textureName, const sf::Vector2f textureCenter, const unsigned int size) {

	std::map<std::string, std::string> componentArguments;
	componentArguments.insert(std::make_pair("Type", "VertexArray"));
	componentArguments.insert(std::make_pair("Name", "GraphicTile"));
	componentArguments.insert(std::make_pair("TextureName", textureName));
	componentArguments.insert(std::make_pair("VertexArrayType", "Triangles"));
	componentArguments.insert(std::make_pair("VertexNumber", "3"));

	//Pointe vers le haut

	const float h{size*sqrtf(3.f)/2.f};

	sf::Vector2f A{0, -2.f*h/3.f} , B{-static_cast<float>(size)/2.f, h/3.f}, C{size/2.f, h/3.f};

	componentArguments.insert(std::make_pair("VerticePosition!0!X", std::to_string(static_cast<float>(A.x))));
	componentArguments.insert(std::make_pair("VerticePosition!0!Y", std::to_string(static_cast<float>(A.y))));
	componentArguments.insert(std::make_pair("VerticeTexture!0!X", std::to_string(textureCenter.x + static_cast<float>(A.x))));
	componentArguments.insert(std::make_pair("VerticeTexture!0!Y", std::to_string(textureCenter.y + static_cast<float>(A.y))));

	componentArguments.insert(std::make_pair("VerticePosition!1!X", std::to_string(static_cast<float>(B.x))));
	componentArguments.insert(std::make_pair("VerticePosition!1!Y", std::to_string(static_cast<float>(B.y))));
	componentArguments.insert(std::make_pair("VerticeTexture!1!X", std::to_string(textureCenter.x + static_cast<float>(B.x))));
	componentArguments.insert(std::make_pair("VerticeTexture!1!Y", std::to_string(textureCenter.y + static_cast<float>(B.y))));

	componentArguments.insert(std::make_pair("VerticePosition!2!X", std::to_string(static_cast<float>(C.x))));
	componentArguments.insert(std::make_pair("VerticePosition!2!Y", std::to_string(static_cast<float>(C.y))));
	componentArguments.insert(std::make_pair("VerticeTexture!2!X", std::to_string(textureCenter.x + static_cast<float>(C.x))));
	componentArguments.insert(std::make_pair("VerticeTexture!2!Y", std::to_string(textureCenter.y + static_cast<float>(C.y))));

	return componentArguments;
}*/