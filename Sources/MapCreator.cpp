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

							 std::cout << pos.x << " " << pos.y << std::endl;

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

			pos.x = (currentHexa%mapSize.x)*tileSpace + ((currentHexa/mapSize.x)%2)*spacement.x - (tileSpace/2.f)*cosf(PI/3.f);
			pos.y = (currentHexa/mapSize.x)*spacement.y + (tileSpace/2.f)*sinf(PI/3.f);

			mapFile << "PositionX!" << std::to_string(pos.x) << std::endl;
			mapFile << "PositionY!" << std::to_string(pos.y) << std::endl;
			mapFile << "Rotation!-60" << std::endl;

			mapFile << "/!\\" << std::endl;
		}

		//Triangles

		std::deque<sf::Vector2f> usedHexagon;
		usedHexagon.emplace_back(0.f, 0.f);
		usedHexagon.emplace_back(spacement.x, spacement.y);
		usedHexagon.emplace_back(tileSpace, 0);

		sf::Vector2f triangleCenter{0.f, 0.f};

		for(unsigned int i{0}; i < (mapSize.x+1)*(mapSize.y-1); i++) {

			mapFile << "Clone!";

			switch(random(engine)) {

				case 1:
					mapFile << "TriangleMountains";
					break;

				case 2:
					mapFile << "TriangleOcean";
					break;

				case 3:
					mapFile << "TrianglePlains";
					break;
			}

			mapFile << std::endl;

			triangleCenter = sf::Vector2f{0.f, 0.f};

			for(sf::Vector2f currentPos: usedHexagon) { triangleCenter += currentPos; std::cout << currentPos.x << " " << currentPos.y << std::endl; }
			triangleCenter /= static_cast<float>(usedHexagon.size());

			mapFile << "PositionX!" << std::to_string(triangleCenter.x) << std::endl;
			mapFile << "PositionY!" << std::to_string(triangleCenter.y) << std::endl;

			mapFile << "/!\\" << std::endl;

			//Pivot

			usedHexagon.pop_front();

			if(i == mapSize.x-1) { //Changement de ligne


			}

			else {}
		}

		mapFile.close();
	}
}

float MapCreator::getNorme(const sf::Vector2f u, const sf::Vector2f v) const { return sqrtf((v.x - u.x)*(v.x - u.x) + (v.y - u.y)*(v.y - u.y)); }