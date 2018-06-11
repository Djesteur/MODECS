#include "MapCreator.hpp"

MapCreator::MapCreator(): m_logWriter{"Data/MapCreator"} {}

void MapCreator::create(const sf::Vector2u mapSize, const unsigned int tileSize) {

	std::ofstream mapFile{"Data/Map"};

	const float tileSpace{tileSize*(1 + sqrtf(3.f))};
	const sf::Vector2f spacement{tileSpace/2.f, tileSpace*sqrtf(3.f)/2.f};

	if(mapFile) {

		//Hexa

	    std::default_random_engine engine{static_cast<long unsigned int>(std::time(nullptr))};
	    std::uniform_int_distribution<unsigned int> random(1, 3); 

		for(unsigned int i{0}; i < mapSize.x*mapSize.y; i++) {

			mapFile << "Clone!";

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

			sf::Vector2f pos{(i%mapSize.x)*tileSpace + ((i/mapSize.x)%2)*spacement.x,
							 (i/mapSize.x)*spacement.y};

			mapFile << "PositionX!" << std::to_string(pos.x) << std::endl;
			mapFile << "PositionY!" << std::to_string(pos.y) << std::endl;
			mapFile << "Rotation!0" << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		//Square

		unsigned int currentHexa{0};
		sf::Vector2f pos{0.f, 0.f};

		unsigned int nbSquares{(mapSize.x-1)*mapSize.y};

		for(unsigned int i{0}; i < nbSquares; i++) {

			mapFile << "Clone!";

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

			currentHexa = i + i/2; 

			pos.x = (currentHexa%mapSize.x)*tileSpace + ((currentHexa/mapSize.x)%2)*spacement.x + tileSpace/2.f;
			pos.y = (currentHexa/mapSize.x)*spacement.y;

			mapFile << "PositionX!" << std::to_string(pos.x) << std::endl;
			mapFile << "PositionY!" << std::to_string(pos.y) << std::endl;
			mapFile << "Rotation!0" << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		nbSquares = (2*mapSize.x-1)*static_cast<int>(mapSize.y/2);
		if(mapSize.y%2 == 0) { nbSquares -= mapSize.x-1; }

		for(unsigned int i{0}; i < nbSquares; i++) {

			mapFile << "Clone!";

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

			currentHexa = i + i/(2*mapSize.x-1);
						
			pos.x = (currentHexa%mapSize.x)*tileSpace + ((currentHexa/mapSize.x)%2)*spacement.x + (tileSpace/2.f)*cosf(PI/3.f);
			pos.y = (currentHexa/mapSize.x)*spacement.y + (tileSpace/2.f)*sinf(PI/3.f);

			mapFile << "PositionX!" << std::to_string(pos.x) << std::endl;
			mapFile << "PositionY!" << std::to_string(pos.y) << std::endl;
			mapFile << "Rotation!60" << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		nbSquares = (2*mapSize.x-1)*static_cast<int>(mapSize.y/2);
		if(mapSize.y%2 == 0) { nbSquares -= mapSize.x; }

		for(unsigned int i{0}; i < nbSquares; i++) {

			mapFile << "Clone!";

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

			currentHexa = i + 1 + i/(2*mapSize.x-1);
			std::cout << i << " " << currentHexa << std::endl;


			pos.x = (currentHexa%mapSize.x)*tileSpace + ((currentHexa/mapSize.x)%2)*spacement.x - (tileSpace/2.f)*cosf(PI/3.f);
			pos.y = (currentHexa/mapSize.x)*spacement.y + (tileSpace/2.f)*sinf(PI/3.f);

			mapFile << "PositionX!" << std::to_string(pos.x) << std::endl;
			mapFile << "PositionY!" << std::to_string(pos.y) << std::endl;
			mapFile << "Rotation!-60" << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		mapFile.close();
	}
}

float MapCreator::getNorme(const sf::Vector2f u, const sf::Vector2f v) const { return sqrtf((v.x - u.x)*(v.x - u.x) + (v.y - u.y)*(v.y - u.y)); }