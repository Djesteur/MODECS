#include "MapCreator.hpp"

MapCreator::MapCreator(): m_logWriter{"Output/Map/Creator"} {}

std::list<Entity> MapCreator::create(EntityKeeper &keeper, GraphicSystem &system, const sf::Vector2u mapSize) {

	m_logWriter << "Loading map file.\n";

	std::ifstream mapFile{"Data/Map"};

	Entity mountain{keeper.newEntity()}, ocean{keeper.newEntity()}, plains{keeper.newEntity()};

	m_logWriter << "Loading temporary entities.\n";

	std::string currentData;
	std::vector<std::string> splitedDatas;

	std::map<std::string, std::string> correspondingTilePath;
	std::map<std::string, Entity> correspondingTileEntity;

	std::ifstream tmpEntitiesFile{"Data/TilePath"};

	while(std::getline(tmpEntitiesFile, currentData)) {

		splitedDatas = splitDatas(currentData, '-');
		correspondingTilePath.insert(std::make_pair(splitedDatas[0], splitedDatas[1]));
		correspondingTileEntity.insert(std::make_pair(splitedDatas[0], Entity{keeper.newEntity()}));
		system.addEntity(correspondingTileEntity[splitedDatas[0]]);
	}

	tmpEntitiesFile.close();

	std::string textureName;
	std::map<std::string, std::string> tileParams;

	for(std::pair<std::string, Entity> currentTile: correspondingTileEntity) {

		tmpEntitiesFile.open(correspondingTilePath[currentTile.first]);

		std::getline(tmpEntitiesFile, textureName);
		std::getline(tmpEntitiesFile, currentData);

		if(currentData == "Hexagon") { tileParams = constructHexa(textureName); }

		system.addComponent(currentTile.second, tileParams);

		tmpEntitiesFile.close();
	}

	m_logWriter << "Assigning entities to tiles.\n";

	std::list<Entity> tiles;
	sf::Vector2f position{0.f, 0.f};

	//Mettre des trow/catch au cas ou fichier mal formé

	while(std::getline(mapFile, currentData)) {

		tiles.emplace_back(keeper.newEntity());
		system.addEntity(tiles.back());

		m_logWriter << "\tA new entity as been created";

		while(currentData != "/!\\") {

			splitedDatas = splitDatas(currentData, '-');

			if(splitedDatas[0] == "Clone") {

				for(std::pair<std::string, Entity> currentTile: correspondingTileEntity) {

					if(splitedDatas[1] == currentTile.first) { 

						system.copyAllComponents(currentTile.second, tiles.back());
						m_logWriter << " as clone of " << currentTile.first; 
					}
				}
			}

			if(splitedDatas[0] == "PositionX") { std::istringstream(splitedDatas[1]) >> position.x; }
			if(splitedDatas[0] == "PositionY") { std::istringstream(splitedDatas[1]) >> position.y; }

			std::getline(mapFile, currentData);
		}

		system.setPosition(tiles.back(), position);

		m_logWriter << " with position (" << std::to_string(position.x) << ", " << std::to_string(position.y) << ").\n"; 
	}

	m_logWriter << "Number of tiles: " << std::to_string(tiles.size()) << ".\n";
	m_logWriter << "End of the map construction, deleting temporary entites.\n";

	mapFile.close();

	system.deleteEntity(mountain);
	system.deleteEntity(ocean);
	system.deleteEntity(plains);

	keeper.deleteEntity(mountain);
	keeper.deleteEntity(ocean);
	keeper.deleteEntity(plains);

	m_logWriter << "End of the construction.\n";

	return tiles;
}

std::map<std::string, std::string> MapCreator::constructHexa(const std::string textureName) {

	std::map<std::string, std::string> componentArguments;
	componentArguments.insert(std::make_pair("Type", "VertexArray"));
	componentArguments.insert(std::make_pair("Name", "GraphicTile"));
	componentArguments.insert(std::make_pair("TextureName", textureName));
	componentArguments.insert(std::make_pair("VertexArrayType", "TriangleFan"));
	componentArguments.insert(std::make_pair("VertexNumber", "8"));

	const unsigned int s{128};
	const sf::Vector2f imageCenter{272.f, 272.f};
	const float PI{3.14159265};

	sf::Vector2f center{0, 0}, newPoint{center}, diff{0, 0};

	componentArguments.insert(std::make_pair("VerticePosition-0-X", std::to_string(newPoint.x)));
	componentArguments.insert(std::make_pair("VerticePosition-0-Y", std::to_string(newPoint.y)));
	componentArguments.insert(std::make_pair("VerticeTexture-0-X", std::to_string(imageCenter.x + newPoint.x)));
	componentArguments.insert(std::make_pair("VerticeTexture-0-Y", std::to_string(imageCenter.y + newPoint.y)));

	newPoint.x = center.x;
	newPoint.y = center.y + s;

	componentArguments.insert(std::make_pair("VerticePosition-1-X", std::to_string(newPoint.x)));
	componentArguments.insert(std::make_pair("VerticePosition-1-Y", std::to_string(newPoint.y)));
	componentArguments.insert(std::make_pair("VerticeTexture-1-X", std::to_string(imageCenter.x + newPoint.x)));
	componentArguments.insert(std::make_pair("VerticeTexture-1-Y", std::to_string(imageCenter.y + newPoint.y)));

	for(unsigned int i{0}; i < 6; i++) {

		diff = newPoint - center;

		newPoint.x = center.x + diff.x*cos(60.f*PI/180.f) - diff.y*sin(60.f*PI/180.f);
		newPoint.y = center.y + diff.x*sin(60.f*PI/180.f) + diff.y*cos(60.f*PI/180.f);

		componentArguments.insert(std::make_pair("VerticePosition-" + std::to_string(i+2) + "-X", std::to_string(newPoint.x)));
		componentArguments.insert(std::make_pair("VerticePosition-" + std::to_string(i+2) + "-Y", std::to_string(newPoint.y)));
		componentArguments.insert(std::make_pair("VerticeTexture-" + std::to_string(i+2) + "-X", std::to_string(imageCenter.x + newPoint.x)));
		componentArguments.insert(std::make_pair("VerticeTexture-" + std::to_string(i+2) + "-Y", std::to_string(imageCenter.y + newPoint.y)));
	}

	return componentArguments;
}