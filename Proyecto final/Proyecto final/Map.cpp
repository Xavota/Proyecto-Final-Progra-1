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

void Map::Init(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow* w) // Inicializa las variables necesarias
{
	game = Game::getInstance();
	map_size = size;
	map_layers = layers;
	for (int i = 0; i < map_layers.size(); i++) { // Lee los archivos de cada layer para agregar los cuadros del mapa y darles la textura correspondiente
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

void Map::AddObject(Object* obj) // Agrega un objeto al mapa
{
	map_objs.push_back(obj);
}

void Map::AddNPC(NPC* npc) // Agrega un NPC al mapa
{
	map_npcs.push_back(npc);
}

Object & Map::GetObject(string obj_name) // Regresa un objeto según su nombre si existe
{
	for (Object* obj : map_objs) {
		if (obj->o_name == obj_name)
			return *obj;
	}
	throw runtime_error("Object not found");
}

NPC & Map::GetNPC(string npc_name) // Regresa un NPC según su nombre si existe
{
	for (NPC* npc : map_npcs) {
		if (npc->o_name == npc_name)
			return *npc;
	}
	throw runtime_error("NPC not found");
}

void Map::Update(sf::Time deltaTime) // Cada ciclo
{
	if (inMap) { // Si está en el mapa
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

void Map::handleInputs(sf::Keyboard::Key key, bool ispressed) // Convierte los inputs en acciones, llama los inputs de sus objetos
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

void Map::GoToMap(sf::Vector2i pos) // Te lleva al mapa actual en la posición dada
{
	inMap = true;
	game->g_player->p_shape.setPosition(pos.x * game->pixels, pos.y * game->pixels);
	game->g_player->o_posAnterior = game->g_player->p_shape.getPosition();
}

void Map::OutOfMap() // Te saca del mapa
{
	inMap = false;
}

bool Map::isActive() // ¿El mapa está activo?
{
	return inMap;
}

void Map::setMapTriggers(string triggers_file_name) // Agrega los triggers del mapa desde el archivo
{
	ifstream triggers_file{ triggers_file_name };
	while (!triggers_file.eof())
	{
		string trigger_type;
		char c = 0;
		Trigger trig;
		triggers_file >> trigger_type;
		triggers_file >> noskipws;
		while (c != '(' && !triggers_file.eof())
		{
			triggers_file >> c;
		}
		triggers_file >> skipws;
		if (trigger_type == "on_trigger_enter") {
			sf::Vector2i pos_init, pos_finale;
			triggers_file >> pos_init >> pos_finale;
			trig = Trigger::onTriggerEnter(pos_init, pos_finale);
		}
		else if (trigger_type == "on_trigger_exit") {
			sf::Vector2i pos_init, pos_finale;
			triggers_file >> pos_init >> pos_finale;
			trig = Trigger::onTriggerExit(pos_init, pos_finale);
		}
		else if (trigger_type == "on_interact") {
			triggers_file >> noskipws >> c >> skipws;
			if (c == '{') {
				triggers_file.putback(c);
				sf::Vector2i pos;
				triggers_file >> pos;
				trig = Trigger::onInteract(pos);
			}
			else if (c == '"') {
				triggers_file.putback(c);
				s_string Obj_name;
				triggers_file >> Obj_name;
				trig = Trigger::onInteract(Object::getObject(Obj_name.str));
			}
		}
		else if (trigger_type == "on_map_enter") {
			trig = Trigger::onMapEnter(this);
		}
		else {
			string rest;
			triggers_file >> noskipws;
			while (!triggers_file.eof()) {
				triggers_file >> c;
				rest += c;
			}
			triggers_file >> skipws;
			if (rest != "") {
				cout << rest <<  ": no detectado como funcion" <<  endl;
			}
			break;
		}
		triggers_file >> noskipws;
		while (c != ')')
		{
			triggers_file >> c;
		}
		triggers_file >> skipws;
		s_string func_file_name;
		triggers_file >> func_file_name;
		FM->CreateFunction(trig, Function(func_file_name.str));
	}
}

void Map::Render(sf::RenderWindow * window) // Renderiza todo el mapa
{
	if (inMap) { // Si está en el mapa
		if (RenderFase1) { // Si es la primera fase de renderizado (por debajo del jugador)
			for (int i = 0; i < map_tiles_grids.size(); i++) { // Por cada capa del mapa
				if (map_layers[i].l_layer != 3) { // Si la layer no es 3 (por arriba del jugador)
					for (vector<sf::RectangleShape> y : map_tiles_grids[i]) { // Dibuja cada tile de la capa
						for (sf::RectangleShape w : y) {
							w.setTexture(&map_textures_grids[i]);
							window->draw(w);
						}
					}
				}
			}
			RenderFase1 = false;
		}
		else { // Si es la segunda fase de renderizado (por arriba del jugador)
			for (int i = 0; i < map_tiles_grids.size(); i++) { // Por cada capa del mapa
				if (map_layers[i].l_layer == 3) { // Si la layer no es 3 (por arriba del jugador)
					for (vector<sf::RectangleShape> y : map_tiles_grids[i]) { // Dibuja cada tile de la capa
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

void Map::Destroy() // Libera la memoria
{
	for (NPC * npc : map_npcs) {
		npc->Destroy();
		if (npc != nullptr) {
			delete npc;
			npc = nullptr;
		}
	}
	for (Object * obj : map_objs) {
		obj->Destroy();
		if (obj != nullptr) {
			delete obj;
			obj = nullptr;
		}
	}
	FM->Destroy();
	if (FM != nullptr) {
		delete FM;
		FM = nullptr;
	}
	if (game != nullptr) {
		game = nullptr;
	}
}

istream & operator>>(istream & is, Map::ID& id) // Sobrecarga del operador para lee un id
{
	int i = 0;
	float u = 0, v = 0;
	is >> i >> u >> v;
	id.ID_id = i;
	id.ID_coords = { u, v };
	return is;
}