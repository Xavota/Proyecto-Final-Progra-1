#include "Map_Manager.h"



Map_Manager::Map_Manager()
{
	Init();
}


Map_Manager::~Map_Manager()
{
}

void Map_Manager::Init()
{
}

void Map_Manager::Update(sf::Time deltaTime)
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Update(deltaTime);
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.Update(deltaTime);
	}
}

void Map_Manager::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.handleInput(key, ispressed);
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.handleInputs(key, isPressed);
	}
}

void Map_Manager::AddMap(Map m, string map_name)
{
	//mm_maps.insert(make_pair(map_name, m));
	mm_maps.push_back(Map_Pair{ map_name, m });
}

void Map_Manager::GoToMap(string map_name, sf::Vector2i pos)
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		if (mm_mapsIt->first == map_name) {
			if (mm_current_map != nullptr)
				mm_current_map->OutOfMap();
			mm_current_map = &(mm_mapsIt->second);
			mm_current_map->GoToMap(pos);
			return;
		}
	}*/
	for (Map_Pair& map : mm_maps) {
		if (map.map_name == map_name) {
			if (mm_current_map != nullptr)
				mm_current_map->OutOfMap();
			mm_current_map = &(map.map);
			mm_current_map->GoToMap(pos);
			return;
		}
	}
	throw runtime_error{"Mapa no encontrado"};
}

vector<Map*> Map_Manager::maps()
{
	vector<Map*> ms;
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		ms.push_back(&mm_mapsIt->second);
	}*/
	for (Map_Pair& map : mm_maps) {
		ms.push_back(&map.map);
	}
	return ms;
}

Map & Map_Manager::getMap(string map_name)
{
	//return mm_maps[map_name];
	for (Map_Pair& map : mm_maps) {
		if (map.map_name == map_name)
			return map.map;
	}
	return *mm_current_map;
}

void Map_Manager::Render(sf::RenderWindow * window)
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Render(window);
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.Render(window);
	}
}

void Map_Manager::Destroy()
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Destroy();
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.Destroy();
	}
}
