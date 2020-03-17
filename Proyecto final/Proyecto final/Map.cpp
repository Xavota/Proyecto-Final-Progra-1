#include "Map.h"
#include "Game.h"
#include "Function_Manager.h"

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
		ifstream lay_layout{ map_layers[i].l_layout_file };
		string lay_ident_file;
		getline(lay_layout, lay_ident_file);
		ifstream lay_ident{ lay_ident_file };
		string file_texture;
		getline(lay_ident, file_texture);
		map_textures_grids.push_back(sf::Texture());
		if (!map_textures_grids[i].loadFromFile(file_texture)) cout << "Mala textura";
		lay_ident >> map_layers[i].x >> map_layers[i].y;
		while (!(lay_ident.eof()))
		{
			ID id;
			lay_ident >> id;
			map_layers[i].ids.push_back(id);
		}
		lay_ident.close();
		float xx = 0, yy = 0;
		map_tiles_grids.push_back(vector<vector<sf::RectangleShape>>());
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
	FM = new Function_Manager();
}

void Map::AddObject(Object* obj)
{
	map_objs.push_back(obj);
}

void Map::AddNPC(NPC* npc)
{
	map_npcs.push_back(npc);
}

Object & Map::GetObject(string obj_name)
{
	for (Object* obj : map_objs) {
		if (obj->o_name == obj_name)
			return *obj;
	}
	throw runtime_error("Object not found");
}

NPC & Map::GetNPC(string npc_name)
{
	for (NPC* npc : map_npcs) {
		if (npc->o_name == npc_name)
			return *npc;
	}
	throw runtime_error("NPC not found");
}

void Map::Update(sf::Time deltaTime)
{
	if (inMap) {
		sf::Vector2f camera_left_up = window->getView().getCenter() - sf::Vector2f{ window->getSize().x / 2.f, window->getSize().y / 2.f };
		sf::Vector2f camera_right_down = window->getView().getCenter() + sf::Vector2f{ window->getSize().x / 2.f, window->getSize().y / 2.f };
		if (window->getSize().x > map_size.x * game->pixels) {
			map_view.setCenter(map_size.x * game->pixels / 2, map_view.getCenter().y);
		}
		else if (camera_left_up.x <= 0.f
			&& game->g_player->p_shape.getPosition().x + game->g_player->p_shape.getSize().x / 2 <= window->getView().getCenter().x)
		{
			map_view.setCenter(window->getSize().x / 2 - .01f, map_view.getCenter().y);
		}
		else if (camera_right_down.x > map_size.x * game->pixels
			&& game->g_player->p_shape.getPosition().x + game->g_player->p_shape.getSize().x / 2 >= window->getView().getCenter().x)
		{
			map_view.setCenter(map_size.x * game->pixels - window->getSize().x / 2 + .01f, map_view.getCenter().y);
		}
		else {
			map_view.setCenter(game->g_player->p_shape.getPosition().x + game->g_player->p_shape.getSize().x / 2, map_view.getCenter().y);
		}
		if (window->getSize().y > map_size.y * game->pixels) {
			map_view.setCenter(map_view.getCenter().x, map_size.y * game->pixels / 2);
		}
		else if (camera_left_up.y < 0.f
			&& game->g_player->p_shape.getPosition().y + game->g_player->p_shape.getSize().y / 2 <= window->getView().getCenter().y)
		{
			map_view.setCenter(map_view.getCenter().x, window->getSize().y / 2 - .01f);
		}
		else if (camera_right_down.y > map_size.y * game->pixels
			&& game->g_player->p_shape.getPosition().y + game->g_player->p_shape.getSize().y / 2 >= window->getView().getCenter().y)
		{
			map_view.setCenter(map_view.getCenter().x, map_size.y * game->pixels - window->getSize().y / 2 + .01f);
		}
		else {
			map_view.setCenter(map_view.getCenter().x, game->g_player->p_shape.getPosition().y + game->g_player->p_shape.getSize().y / 2);
		}
		window->setView(map_view);
		for (NPC * npc : map_npcs) {
			npc->Update(deltaTime);
		}
		for (Object * obj : map_objs) {
			obj->Update(deltaTime);
		}
		FM->Update(deltaTime);
	}
}

void Map::handleInputs(sf::Keyboard::Key key, bool ispressed)
{
	if (inMap) {
		for (NPC * npc : map_npcs) {
			npc->handleInputs(key, ispressed);
		}
		for (Object * obj : map_objs) {
			obj->handleInputs(key, ispressed);
		}
		FM->handleInputs(key, ispressed);
	}
}

void Map::GoToMap(sf::Vector2i pos)
{
	inMap = true;
	game->g_player->p_shape.setPosition(pos.x * game->pixels, pos.y * game->pixels);
	game->g_player->o_posAnterior = game->g_player->p_shape.getPosition();
}

void Map::OutOfMap()
{
	inMap = false;
}

bool Map::isActive()
{
	return inMap;
}

void Map::setMapTriggers(string triggers_file_name)
{
	ifstream triggers_file{ triggers_file_name };
	while (!triggers_file.eof())
	{
		string trigger_type;
		char c = 0;
		triggers_file >> trigger_type;
		if (trigger_type == "on_trigger_enter") {
			triggers_file >> noskipws;
			while (c != '(')
			{
				triggers_file >> c;
			}
			triggers_file >> skipws;
			sf::Vector2i pos_init, pos_finale;
			triggers_file >> pos_init >> pos_finale;
			triggers_file >> noskipws;
			while (c != ')')
			{
				triggers_file >> c;
			}
			while (c != '"')
			{
				triggers_file >> c;
			}
			string func_file_name = "";
			triggers_file >> c;
			while (c != '"')
			{
				func_file_name += c;
				triggers_file >> c;
			}
			triggers_file >> skipws;
			FM->CreateFunction(Trigger::onTriggerEnter(pos_init, pos_finale), Function(func_file_name));
		}
		if (trigger_type == "on_trigger_exit") {
			triggers_file >> noskipws;
			while (c != '(')
			{
				triggers_file >> c;
			}
			triggers_file >> skipws;
			sf::Vector2i pos_init, pos_finale;
			triggers_file >> pos_init >> pos_finale;
			triggers_file >> noskipws;
			while (c != ')')
			{
				triggers_file >> c;
			}
			while (c != '"')
			{
				triggers_file >> c;
			}
			string func_file_name = "";
			triggers_file >> c;
			while (c != '"')
			{
				func_file_name += c;
				triggers_file >> c;
			}
			triggers_file >> skipws;
			FM->CreateFunction(Trigger::onTriggerExit
(pos_init, pos_finale), Function(func_file_name));
		}
		if (trigger_type == "on_interact") {
			bool onPos = false;
			sf::Vector2i pos;
			string Obj_name;
			triggers_file >> noskipws;
			while (c != '(')
			{
				triggers_file >> c;
			}
			triggers_file >> c;
			if (c == '{') {
				onPos = true;
				triggers_file.putback(c);
				triggers_file >> skipws;
				triggers_file >> pos;
			}
			else if (c == '"') {
				triggers_file >> c;
				while (c != '"')
				{
					Obj_name += c;
					triggers_file >> c;
				}
				triggers_file >> skipws;
			}
			triggers_file >> noskipws;
			while (c != ')')
			{
				triggers_file >> c;
			}
			while (c != '"')
			{
				triggers_file >> c;
			}
			string func_file_name = "";
			triggers_file >> c;
			while (c != '"')
			{
				func_file_name += c;
				triggers_file >> c;
			}
			triggers_file >> skipws;
			if (onPos)
				FM->CreateFunction(Trigger::onInteract(pos), Function(func_file_name));
			else
				FM->CreateFunction(Trigger::onInteract(Object::getObject(Obj_name)), Function(func_file_name));
		}
	}
}

void Map::Render(sf::RenderWindow * window)
{
	if (inMap) {
		if (RenderFase1) {
			for (int i = 0; i < map_tiles_grids.size(); i++) {
				if (map_layers[i].l_layer != 3) {
					for (vector<sf::RectangleShape> y : map_tiles_grids[i]) {
						for (sf::RectangleShape w : y) {
							w.setTexture(&map_textures_grids[i]);
							window->draw(w);
						}
					}
				}
			}
			RenderFase1 = false;
		}
		else {
			for (int i = 0; i < map_tiles_grids.size(); i++) {
				if (map_layers[i].l_layer == 3) {
					for (vector<sf::RectangleShape> y : map_tiles_grids[i]) {
						for (sf::RectangleShape w : y) {
							w.setTexture(&map_textures_grids[i]);
							window->draw(w);
						}
					}
				}
			}
			for (NPC * npc : map_npcs) {
				npc->Render(window);
			}
			for (Object * obj : map_objs) {
				obj->Render(window);
			}
			FM->Render(window);
			RenderFase1 = true;
		}
	}
}

void Map::Destroy()
{
	for (NPC * npc : map_npcs) {
		npc->Destroy();
	}
	for (Object * obj : map_objs) {
		obj->Destroy();
	}
	FM->Destroy();
}

istream & operator>>(istream & is, Map::ID& id)
{
	int i = 0;
	float u = 0, v = 0;
	is >> i >> u >> v;
	id.ID_id = i;
	id.ID_coords = { u, v };
	return is;
}