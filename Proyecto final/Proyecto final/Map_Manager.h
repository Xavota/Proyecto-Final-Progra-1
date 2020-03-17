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
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void AddMap(Map m, string map_name);
	void GoToMap(string map_name, sf::Vector2i pos);
	vector<Map*> maps();
	Map& getMap(string map_name);
	void Render(sf::RenderWindow *window);
	void Destroy();
private:
	class Map_Pair {
	public:
		Map_Pair(string name, Map m) { map_name = name; map = m; }
		string map_name;
		Map map;
	};
private:
	//map<string, Map> mm_maps;
	//map<string, Map>::iterator mm_mapsIt;
	vector<Map_Pair> mm_maps;
	Map* mm_current_map;
};

