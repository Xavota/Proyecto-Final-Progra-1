#include "Map_Manager.h"



Map_Manager::Map_Manager()
{
}


Map_Manager::~Map_Manager()
{
}

void Map_Manager::Init()
{
}

void Map_Manager::Update(sf::Time deltaTime)
{
	for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Update(deltaTime);
	}
}

void Map_Manager::handleInput(sf::Keyboard::Key key, bool ispressed)
{
	for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.handleInput(key, ispressed);
	}
}

void Map_Manager::AddMap(Map m, string map_name)
{
	mm_maps.insert(make_pair(map_name, m));
}

void Map_Manager::GoToMap(string map_name, sf::Vector2f pos)
{
	for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		if (mm_mapsIt->first == map_name) {
			if (mm_current_map != nullptr)
				mm_current_map->OutOfMap();
			mm_current_map = &(mm_mapsIt->second);
			mm_current_map->GoToMap(pos);
			return;
		}
	}
	throw runtime_error{"Mapa no encontrado"};
}

vector<Map*> Map_Manager::maps()
{
	vector<Map*> ms;
	for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		ms.push_back(&mm_mapsIt->second);
	}
	return ms;
}

void Map_Manager::Render(sf::RenderWindow * window)
{
	for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Render(window);
	}
}

void Map_Manager::Destroy()
{
	for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Destroy();
	}
}
