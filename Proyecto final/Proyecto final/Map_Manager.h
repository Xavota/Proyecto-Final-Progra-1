#pragma once
#include "Map.h"
#include <map>
class Map_Manager
{
private:
	class Map_Pair { // Sustituye al mapa porque me daba problemas
	public:
		Map_Pair(string name, Map m) { map_name = name; map = m; }
		string map_name;
		Map map;
	};
public:
	Map_Manager();
	~Map_Manager();
	void Init(); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte inputs en acciones
	void AddMap(Map m, string map_name); // Agrega un mapa al juego
	void GoToMap(string map_name, sf::Vector2i pos); // Lleva al jugador al mapa indicado en la posición indicada
	vector<Map*> maps(); // Devuelve la lusta de mapas existentes
	Map& getMap(string map_name); // Devuelve un mapa según su nombre
	Map_Pair& getMap(); // Devuelve el mapa actual
	void Render(sf::RenderWindow *window); // Renderiza el mapa activo
	void Destroy(); // Libera la memoria
private:
	//map<string, Map> mm_maps;
	//map<string, Map>::iterator mm_mapsIt;
	vector<Map_Pair> mm_maps;
	Map* mm_current_map;
};

