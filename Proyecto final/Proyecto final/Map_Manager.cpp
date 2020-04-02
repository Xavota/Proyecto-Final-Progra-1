#include "Map_Manager.h"

Map_Manager::Map_Manager()
{
	Init();
}

Map_Manager::~Map_Manager()
{
}

void Map_Manager::Init() // Inicializa el mapa
{
}

void Map_Manager::Update(sf::Time deltaTime) // Cada ciclo
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Update(deltaTime);
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.Update(deltaTime);
	}
}

void Map_Manager::handleInputs(sf::Keyboard::Key key, bool isPressed) // Convierte inputs en acciones, llama a los inputs de sus objetos
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.handleInput(key, ispressed);
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.handleInputs(key, isPressed);
	}
}

void Map_Manager::AddMap(Map m, string map_name) // Agrega un mapa
{
	//mm_maps.insert(make_pair(map_name, m));
	mm_maps.push_back(Map_Pair{ map_name, m });
}

void Map_Manager::GoToMap(string map_name, sf::Vector2i pos) // Te lleva al mapa dado en la posición dada
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

vector<Map*> Map_Manager::maps() // Regresa a la lista de mapas
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

Map & Map_Manager::getMap(string map_name) // Devuelve el mapa según su nombre
{
	//return mm_maps[map_name];
	for (Map_Pair& map : mm_maps) {
		if (map.map_name == map_name)
			return map.map;
	}
	return *mm_current_map;
}

Map_Manager::Map_Pair & Map_Manager::getMap() // Devuelve el mapa actual
{
	for (Map_Pair& map : mm_maps) {
		if (map.map.isActive()) {
			return map;
		}
	}
}

void Map_Manager::Render(sf::RenderWindow * window) // Renderiza los mapas
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Render(window);
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.Render(window);
	}
}

void Map_Manager::Destroy() // Libera la memoria
{
	/*for (mm_mapsIt = mm_maps.begin(); mm_mapsIt != mm_maps.end(); mm_mapsIt++) {
		mm_mapsIt->second.Destroy();
	}*/
	for (Map_Pair& map : mm_maps) {
		map.map.Destroy();
	}
	if (mm_current_map != nullptr) {
		mm_current_map = nullptr;
	}
}
