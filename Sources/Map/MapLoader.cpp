#include "Map/MapLoader.hpp"

MapLoader::MapLoader(): m_logWriter{"Output/Map/MapLoader"} {}

std::list<Entity> MapLoader::load(EntityKeeper &keeper, GraphicSystem &system, const unsigned int tileSize) {

	//Load examples

	m_logWriter << "Loading examples tiles.\n";

	std::map<std::string, Entity> mapExamples{constructExampleTiles("Data/Tiles/TilesPath", keeper, system, tileSize)};

	m_logWriter << mapExamples.size() << " examples tiles has been loaded:\n";

	for(std::pair<std::string, Entity> currentTile: mapExamples) { m_logWriter << "\t" << currentTile.first << "\n"; }

	m_logWriter << "Loading map tiles.\n";

	std::list<Entity> tiles;
	//Constructing map

	try {

		if(mapExamples.size() != 0) {

			std::ifstream mapFile{"Data/Map/NewMap.txt"};

			if(mapFile) {

				std::string currentData;
				std::vector<std::string> splitedDatas;
				sf::Vector2f tilePosition{0.f, 0.f};
				float rotation{0.f};

				unsigned int currentLine{0};

				while(!mapFile.eof()) {

					tilePosition = sf::Vector2f{0.f, 0.f};
					rotation = 0.f;

					Entity currentEntity{keeper.newEntity()};
					system.addEntity(currentEntity);

					std::getline(mapFile, currentData);

					//For each tile in file

					while(currentData != "!!!") {

						if(mapFile.eof()) { throw "Invalid file format at line " + std::to_string(currentLine); }

						splitedDatas = splitDatas(currentData, '!');
						if(splitedDatas.size() == 2) {

							if(splitedDatas[0] == "Clone") {

								for(std::pair<std::string, Entity> currentTile: mapExamples) {

									if(currentTile.first == splitedDatas[1]) { system.copyAllComponents(currentTile.second, currentEntity); }
								}
							}

							if(splitedDatas[0] == "PositionX") { std::istringstream(splitedDatas[1]) >> tilePosition.x; }
							if(splitedDatas[0] == "PositionY") { std::istringstream(splitedDatas[1]) >> tilePosition.y; }
							if(splitedDatas[0] == "Rotation") { std::istringstream(splitedDatas[1]) >> rotation; }

						}

						else { throw "Invalid data format at line " + std::to_string(currentLine); }

						std::getline(mapFile, currentData);
						currentLine++;
					}

					system.setPosition(currentEntity, tilePosition);
					system.rotate(currentEntity, rotation);
					system.syncTextureRotation(currentEntity);

					tiles.emplace_back(currentEntity);
				}

			}

			else { throw "can't load file Datas/Map/NewMap.txt"; }
		}

		else { throw "problem with tiles example construction"; }
	}

	catch(const std::string &error) { 

		m_logWriter << "ERROR: " << error << " while loading map.\n";

		for(Entity &currentEntity: tiles) {

			system.deleteEntity(currentEntity);
			keeper.deleteEntity(currentEntity);
		}

		tiles.clear();
	}

	catch(const char error[]) { 

		m_logWriter << "ERROR: " << error << " while loading map.\n"; 
		
		for(Entity &currentEntity: tiles) {

			system.deleteEntity(currentEntity);
			keeper.deleteEntity(currentEntity);
		}

		tiles.clear();
	}

	m_logWriter << "End of loading, deleting examples tiles.\n";

	for(std::pair<std::string, Entity> currentTile: mapExamples) {

		system.deleteEntity(currentTile.second);
		keeper.deleteEntity(currentTile.second);
	}

	m_logWriter << "The map has been loaded.\n";

	return tiles;
}

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
		sf::Vector2f texturePosition;

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
}