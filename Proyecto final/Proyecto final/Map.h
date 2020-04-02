#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include "Object.h"
#include "NPC.h"
#include "Animator_Manager.h"
#include "s_string.h"
class Function_Manager;
class Game;
using namespace std;
class Map
{
public:
	class ID { // El identificador de los números para las coordenadas de la textura que representan
	public:
		ID() {};
		ID(int id, sf::Vector2f coords) { ID_id = id; ID_coords = coords; }
		int ID_id;
		sf::Vector2f ID_coords;
	};
	class Layer { // La información de cada capa del mapa
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
	void Init(sf::Vector2f size, vector<Layer> layers, sf::RenderWindow* w); // Inicializa las variables
	void AddObject(Object* obj); // Agrega un objeto al mapa
	void AddNPC(NPC* npc); // Agrega un NPC al mapa
	Object& GetObject(string obj_name); // Devuelve un objeto dentro del mapa según su nombre
	NPC& GetNPC(string npc_name); // Devuelve un NPC dentro del mapa según su nombre
	void Update(sf::Time deltaTime); // Cada ciclo
	void handleInputs(sf::Keyboard::Key key, bool ispressed); // Convierte los inputs en acciones
	void GoToMap(sf::Vector2i pos); // Activa el mapa y aparece al jugador en la posición
	void OutOfMap(); // Indica que saliste del mapa
	bool isActive(); // ¿Está activo el mapa?
	void setMapTriggers(string triggers_file_name); // Crea los triggers con sus funciones del mapa
	void Render(sf::RenderWindow* window); // Renderiza cada capa, NPC y objeto del mapa
	void Destroy(); // Libera la memoria
private:
	ID findID(const vector<ID>& ids, int id) { // Busca en una lista de ids un id en específico
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
istream& operator>>(istream& is, Map::ID& id); // Operador sobrecargado para leer IDs