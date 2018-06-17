#include "Map/MapCreator.hpp"

MapCreator::MapCreator(): m_logWriter{"Output/Map/MapCreator"} {}

void MapCreator::create(const sf::Vector2u mapSize, const unsigned int tileSize) {


	    /* Complexité:

	    	- X*Y
	    	- (X-1)*Y
	    	- 2*(2*X-1)*(Y/2)
	    	- 2*(X-1)(Y-1)

	    	= 8XY-(3/2)Y - 4(X + y + 1)

	    	si X == Y

	    	= 8n² - (3/2)n - 4(2n +1)
	    	= 8n² - (3/2)n - 8n + 4
	    	= 8n² - (19/2)n  + 4
	    	*/

	const std::string mapPath{"Data/Map/NewMap.txt"};

	if(loadTilesTypes("Data/Tiles/TilesPath")) {

		try {

			std::ofstream mapFile{mapPath};

			if(mapFile) {

				const float tileSpace{tileSize*(1 + sqrtf(3.f))};
				const sf::Vector2f spacement{tileSpace/2.f, tileSpace*sqrtf(3.f)/2.f};

				std::vector<sf::Vector2f> hexaPositions;

				//Hexagon

			    std::default_random_engine engine{static_cast<long unsigned int>(std::time(nullptr))};
			    std::uniform_int_distribution<unsigned int> random(0, m_hexaTiles.size()); 

				for(unsigned int i{0}; i < mapSize.x*mapSize.y; i++) {

					mapFile << "Clone!" << m_hexaTiles[random(engine)] << std::endl;

					sf::Vector2f pos{(i%mapSize.x)*tileSpace + ((i/mapSize.x)%2)*spacement.x,
									 (i/mapSize.x)*spacement.y};

					mapFile << "PositionX!" << std::to_string(pos.x) << std::endl;
					mapFile << "PositionY!" << std::to_string(pos.y) << std::endl;
					mapFile << "Rotation!0" << std::endl;

					mapFile << "!!!" << std::endl;

					hexaPositions.emplace_back(pos);
				}

				//Square

				unsigned int currentHexa{0};

				unsigned int nbSquares{(mapSize.x-1)*mapSize.y};

				for(unsigned int i{0}; i < nbSquares; i++) {

					mapFile << "Clone!" << m_squareTiles[random(engine)] << std::endl;

					currentHexa = i + i/(mapSize.x-1); 

					mapFile << "PositionX!" << std::to_string(hexaPositions[currentHexa].x + tileSpace/2.f) << std::endl;
					mapFile << "PositionY!" << std::to_string(hexaPositions[currentHexa].y) << std::endl;
					mapFile << "Rotation!0" << std::endl;

					mapFile << "!!!" << std::endl;
				}

				nbSquares = (2*mapSize.x-1)*static_cast<int>(mapSize.y/2);
				if(mapSize.y%2 == 0) { nbSquares -= mapSize.x-1; }

				for(unsigned int i{0}; i < nbSquares; i++) {

					mapFile << "Clone!" << m_squareTiles[random(engine)] << std::endl;

					currentHexa = i + i/(2*mapSize.x-1);

					mapFile << "PositionX!" << std::to_string(hexaPositions[currentHexa].x + (tileSpace/2.f)*cosf(PI/3.f)) << std::endl;
					mapFile << "PositionY!" << std::to_string(hexaPositions[currentHexa].y + (tileSpace/2.f)*sinf(PI/3.f)) << std::endl;
					mapFile << "Rotation!60" << std::endl;

					mapFile << "!!!" << std::endl;
				}

				nbSquares = (2*mapSize.x-1)*static_cast<int>(mapSize.y/2);
				if(mapSize.y%2 == 0) { nbSquares -= mapSize.x; }

				for(unsigned int i{0}; i < nbSquares; i++) {

					mapFile << "Clone!" << m_squareTiles[random(engine)] << std::endl;

					currentHexa = i + 1 + i/(2*mapSize.x-1);

					mapFile << "PositionX!" << std::to_string(hexaPositions[currentHexa].x - (tileSpace/2.f)*cosf(PI/3.f)) << std::endl;
					mapFile << "PositionY!" << std::to_string(hexaPositions[currentHexa].y + (tileSpace/2.f)*sinf(PI/3.f)) << std::endl;
					mapFile << "Rotation!-60" << std::endl;

					mapFile << "!!!" << std::endl;
				}

				//Triangle

				for(unsigned int i{0}; i < (mapSize.x-1)*(mapSize.y-1); i++) {

					mapFile << "Clone!" << m_triangleTiles[random(engine)] << std::endl;

					currentHexa = i + i/(mapSize.x-1);

					mapFile << "PositionX!" << std::to_string(hexaPositions[currentHexa].x + tileSpace/2.f) << std::endl;
					mapFile << "PositionY!" << std::to_string(hexaPositions[currentHexa].y + tileSize*(3.f + sqrtf(3.0))/6.f) << std::endl;
					mapFile << "Rotation!180" << std::endl;

					mapFile << "!!!" << std::endl;
				}


				for(unsigned int i{0}; i < (mapSize.x-1)*(mapSize.y-1); i++) {

					mapFile << "Clone!" << m_triangleTiles[random(engine)] << std::endl;

					currentHexa = i + mapSize.x + i/(mapSize.x-1);

					mapFile << "PositionX!" << std::to_string(hexaPositions[currentHexa].x + tileSpace/2.f) << std::endl;
					mapFile << "PositionY!" << std::to_string(hexaPositions[currentHexa].y - tileSize*(3.f + sqrtf(3.0))/6.f) << std::endl;
					mapFile << "Rotation!0" << std::endl;

					mapFile << "!!!";

					if(i != (mapSize.x-1)*(mapSize.y-1) -1) { mapFile << std::endl; }
				}

				mapFile.close();
			}

			else { throw "can't open file"; }
		}

		catch(const std::string &error) { m_logWriter << "ERROR: " << error << " in file " << mapPath << "\n"; }
	}
}

bool MapCreator::loadTilesTypes(const std::string filePath) {

	bool result{true};

	std::ifstream tilesTypes{filePath};

	unsigned int currentLine{0};

	try {

		if(tilesTypes) {

			std::string currentData;
			std::vector<std::string> splitedDatas;

			std::getline(tilesTypes, currentData);
			currentLine++;
			
			while(currentData != "!!!") {

				if(tilesTypes.eof()) { throw "Invalid file format at line " + std::to_string(currentLine); }

				splitedDatas = splitDatas(currentData, '!');

				if(splitedDatas.size() != 2) { throw "Invalid data at line " + currentLine; }
				else { m_hexaTiles.emplace_back(splitedDatas[0]); }

				std::getline(tilesTypes, currentData);
				currentLine++;
			}

			std::getline(tilesTypes, currentData);
			currentLine++;
			
			while(currentData != "!!!") {

				if(tilesTypes.eof()) { throw "Invalid file format at line " + std::to_string(currentLine); }

				splitedDatas = splitDatas(currentData, '!');

				if(splitedDatas.size() != 2) { throw "Invalid data at line " + currentLine; }
				else { m_squareTiles.emplace_back(splitedDatas[0]); }

				std::getline(tilesTypes, currentData);
				currentLine++;
			}

			std::getline(tilesTypes, currentData);
			currentLine++;
			
			while(currentData != "!!!") {

				if(tilesTypes.eof()) { throw "Invalid file format at line " + std::to_string(currentLine); }

				splitedDatas = splitDatas(currentData, '!');

				if(splitedDatas.size() != 2) { throw "Invalid data at line " + currentLine; }
				else { m_triangleTiles.emplace_back(splitedDatas[0]); }

				std::getline(tilesTypes, currentData);
				currentLine++;
			}

			if(!tilesTypes.eof()) {

				m_logWriter << "WARNING: Data found in " << filePath << " which will be untreated:\n";

				while(std::getline(tilesTypes, currentData)) { m_logWriter << "\t" << currentData << "\n"; }
			}

			tilesTypes.close();
		}

		else { throw "can't open file"; }
	}

	catch(const std::string &error) { 

		m_logWriter << "ERROR: " << error << " in file " << filePath << "\n"; 
		result = false;
	}

	return result;
}