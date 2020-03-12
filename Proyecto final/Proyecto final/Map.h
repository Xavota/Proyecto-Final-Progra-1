#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
class Game;
using namespace std;
class Map
{
private:
	class ID {
	public:
		ID(int id, sf::Vector2f coords) { ID_id = id; ID_coords = coords; }
		int ID_id;
		sf::Vector2f ID_coords;
	};
public:
	class Layer {
	public:
		Layer(string ident_file, string layout_file, int layer) { l_ident_file = ident_file; l_layout_file = layout_file; l_layer = layer; };
		string l_ident_file, l_layout_file;
		int l_layer;
		int x = 0, y = 0;
		vector<ID> ids;
	};
	Map();
	~Map();
	void Init(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow* w);
	void Update(sf::Time deltaTime);
	void GoToMap(sf::Vector2f pos);
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
	Game* game;
};

