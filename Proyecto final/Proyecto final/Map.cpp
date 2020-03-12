#include "Map.h"
#include "Game.h"


Map::Map()
{
}

Map::Map(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow * w)
{
	Init(size, layers, w);
}


Map::~Map()
{
}

void Map::Init(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow* w)
{
	game = Game::getInstance();
	map_size = size;
	map_layers = layers;
	for (int i = 0; i < map_layers.size(); i++) {
		ifstream lay_ident{ map_layers[i].l_ident_file };
		string file_texture;
		getline(lay_ident, file_texture);
		map_textures_grids.push_back(sf::Texture());
		if (!map_textures_grids[i].loadFromFile(file_texture)) cout << "Mala textura";
		lay_ident >> map_layers[i].x >> map_layers[i].y;
		while (!(lay_ident.eof()))
		{
			int id = 0;
			float u = 0, v = 0;
			lay_ident >> id >> u >> v;
			map_layers[i].ids.push_back(ID{ id, sf::Vector2f{u, v} });
		}
		lay_ident.close();
	}
	for (int i = 0; i < map_layers.size(); i++){
		float xx = 0, yy = 0;
		map_tiles_grids.push_back(vector<vector<sf::RectangleShape>>());
		ifstream lay_layout{map_layers[i].l_layout_file};
		while (!(lay_layout.eof())) {
			string line;
			getline(lay_layout, line);
			stringstream ss_line{ line };
			map_tiles_grids[i].push_back(vector<sf::RectangleShape>());
			while (!(ss_line.eof())) {
				int id = 0;
				ss_line >> id;
				if (id != 0) {
					map_tiles_grids[i][map_tiles_grids[i].size() - 1].push_back(sf::RectangleShape{ {game->pixels, game->pixels} });
					map_tiles_grids[i][map_tiles_grids[i].size() - 1][map_tiles_grids[i][map_tiles_grids[i].size() - 1].size() - 1].setTexture(&map_textures_grids[i]);
					map_tiles_grids[i][map_tiles_grids[i].size() - 1][map_tiles_grids[i][map_tiles_grids[i].size() - 1].size() - 1].setTextureRect
						(sf::IntRect((map_textures_grids[i].getSize().x / map_layers[i].x) * findID(map_layers[i].ids, id).ID_coords.x, 
						(map_textures_grids[i].getSize().y / map_layers[i].y) * findID(map_layers[i].ids, id).ID_coords.y, 
						(map_textures_grids[i].getSize().x / map_layers[i].x), (map_textures_grids[i].getSize().y / map_layers[i].y)));
					map_tiles_grids[i][map_tiles_grids[i].size() - 1][map_tiles_grids[i][map_tiles_grids[i].size() - 1].size() - 1].setPosition
						(xx * game->pixels, yy * game->pixels);
				}
				xx++;
			}
			yy++;
			xx = 0;
		}
		lay_layout.close();
	}
	window = w;
	map_view.setSize(window->getSize().x, window->getSize().y);
}

void Map::Update(sf::Time deltaTime)
{
	if (inMap) {
		sf::Vector2f camera_left_up = window->getView().getCenter() - sf::Vector2f{ window->getSize().x / 2.f, window->getSize().y / 2.f };
		sf::Vector2f camera_right_down = window->getView().getCenter() + sf::Vector2f{ window->getSize().x / 2.f, window->getSize().y / 2.f };
		float extra_x = 0, extra_y = 0;
		if (!(camera_left_up.x <= 0.f
			&& game->g_player->p_shape.getPosition().x + game->g_player->p_shape.getSize().x / 2 < window->getView().getCenter().x
			|| camera_right_down.x >= map_size.x * game->pixels
			&& game->g_player->p_shape.getPosition().x + game->g_player->p_shape.getSize().x / 2 > window->getView().getCenter().x)) 
		{
			map_view.setCenter(game->g_player->p_shape.getPosition().x + game->g_player->p_shape.getSize().x / 2, map_view.getCenter().y);
		}
		if (!(camera_left_up.y <= 0.f 
			&& game->g_player->p_shape.getPosition().y + game->g_player->p_shape.getSize().y / 2 < window->getView().getCenter().y 
			|| camera_right_down.y >= map_size.y * game->pixels 
			&& game->g_player->p_shape.getPosition().y + game->g_player->p_shape.getSize().y / 2 > window->getView().getCenter().y)) 
		{
			map_view.setCenter(map_view.getCenter().x, game->g_player->p_shape.getPosition().y + game->g_player->p_shape.getSize().y / 2);
		}
		window->setView(map_view);
	}
}

void Map::handleInput(sf::Keyboard::Key key, bool ispressed)
{
}

void Map::GoToMap(sf::Vector2f pos)
{
	inMap = true;
	game->g_player->p_shape.setPosition(pos * game->pixels);
	game->g_player->o_posAnterior = (pos * game->pixels);
}

void Map::OutOfMap()
{
	inMap = false;
}

bool Map::isActive()
{
	return inMap;
}

void Map::Render(sf::RenderWindow * window)
{
	if (inMap) {
		for (int i = 0; i < map_tiles_grids.size(); i++) {
			for (vector<sf::RectangleShape> y : map_tiles_grids[i]) {
				for (sf::RectangleShape w : y) {
					w.setTexture(&map_textures_grids[i]);
					window->draw(w);
				}
			}
		}
	}
}

void Map::Destroy()
{
}
