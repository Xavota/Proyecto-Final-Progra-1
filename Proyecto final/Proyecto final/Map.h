#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include "Object.h"
#include "NPC.h"
#include "Animator_Manager.h"
class Function_Manager;
class Game;
using namespace std;
class Map
{
public:
	class ID {
	public:
		ID() {};
		ID(int id, sf::Vector2f coords) { ID_id = id; ID_coords = coords; }
		int ID_id;
		sf::Vector2f ID_coords;
	};
	class Layer {
	public:
		Layer(string layout_file, int layer) { l_layout_file = layout_file; l_layer = layer; };
		string l_layout_file;
		int l_layer;
		int x = 0, y = 0;
		vector<ID> ids;
	};
	Map();
	Map(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow* w);
	~Map();
	void Init(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow* w);
	void AddObject(Object* obj);
	void AddNPC(NPC* npc);
	Object& GetObject(string obj_name);
	NPC& GetNPC(string npc_name);
	void Update(sf::Time deltaTime);
	void handleInputs(sf::Keyboard::Key key, bool ispressed);
	void GoToMap(sf::Vector2i pos);
	void OutOfMap();
	bool isActive();
	void setMapTriggers(string triggers_file_name);
	void Render(sf::RenderWindow* window);
	void Destroy();
private:
	ID findID(const vector<ID>& ids, int id) {
		for (ID z : ids) {
			if (z.ID_id == id)
				return z;
		}
		return ID(0, { 0, 0 });
	}
	bool inMap = false;
	sf::Texture map_tiles;
	vector<sf::Texture> map_textures_grids;
	vector<vector<vector<sf::RectangleShape>>> map_tiles_grids;
	sf::Vector2f map_size;
	sf::RenderWindow* window;
	sf::View map_view;
	vector<Layer> map_layers;
	bool RenderFase1 = true;
public:
	Function_Manager* FM;
private:
	friend class Object;
	friend class Trigger;
	Game* game;
	vector<Object*> map_objs;
	vector<NPC*> map_npcs;
};
istream& operator>>(istream& is, Map::ID& id);