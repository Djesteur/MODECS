#include "MapCreator.hpp"

MapCreator::MapCreator(): m_logWriter{"Data/MapCreator"} {}

void MapCreator::create(const sf::Vector2u mapSize, const unsigned int tileSize) {

	std::ofstream mapFile{"Data/Map"};

	const float tileSpace{tileSize + 2.f*sqrtf((3.f/4.f)*tileSize*tileSize)};

	if(mapFile) {

		//Hexa

	    std::default_random_engine engine{static_cast<long unsigned int>(std::time(nullptr))};
	    std::uniform_int_distribution<unsigned int> random(1, 3); 

		for(unsigned int i{0}; i < mapSize.x*mapSize.y; i++) {

			mapFile << "Clone-";

			switch(random(engine)) {

				case 1:
					mapFile << "HexaMountains";
					break;

				case 2:
					mapFile << "HexaOcean";
					break;

				case 3:
					mapFile << "HexaPlains";
					break;
			}

			mapFile << std::endl;

			mapFile << "PositionX-" << std::to_string((i%mapSize.x)*tileSpace + ((i/mapSize.x)%2)*tileSpace/2.f) << std::endl;
			mapFile << "PositionY-" << std::to_string((i/mapSize.x)*tileSpace) << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		//Square

		for(unsigned int i{0}; i < (mapSize.x-1)*mapSize.y; i++) {

			mapFile << "Clone-";

			switch(random(engine)) {

				case 1:
					mapFile << "SquareMountains";
					break;

				case 2:
					mapFile << "SquareOcean";
					break;

				case 3:
					mapFile << "SquarePlains";
					break;
			}

			mapFile << std::endl;

			mapFile << "PositionX-" << std::to_string((i%(mapSize.x-1))*tileSpace + tileSpace/2.f + ((i/mapSize.x)%2)*tileSpace/2.f) << std::endl;
			mapFile << "PositionY-" << std::to_string((i/mapSize.x)*tileSpace) << std::endl;

			mapFile << "Rotation-0" << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		mapFile.close();
	}
}