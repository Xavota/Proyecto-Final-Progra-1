#pragma once
#include "Map.h"
#include <map>
class Map_Manager
{
public:
	Map_Manager();
	~Map_Manager();
	void Init();
	void Update(sf::Time deltaTime);
	void handleInput(sf::Keyboard::Key key, bool ispressed);
	void AddMap(Map m, string map_name);
	void GoToMap(string map_name, sf::Vector2f pos);
	vector<Map*> maps();
	void Render(sf::RenderWindow *window);
	void Destroy();
private:
	map<string, Map> mm_maps;
	map<string, Map>::iterator mm_mapsIt;
	Map* mm_current_map;
};

