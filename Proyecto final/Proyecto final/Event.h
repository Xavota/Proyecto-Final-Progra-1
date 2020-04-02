#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Player.h"
#include "Map_Manager.h"
using namespace std;
class Event
{
public:
	enum Tag {
		dialog_box, set_speed, go_to_map, to_win
	};
	struct Info { // Información necesaria para ejecutar el evento
		Info() {};
		Info(vector<void*> v) { v1 = v; };
		vector<void*> v1; // Un vector de punteros void para almacenar la información que sea
	};
	Event();
	Event(Tag t, Info i);
	~Event();
	static Event DialogBox(string file_name, int pos); // Devuelve el evento que escribe en la caja de dialogo
	static Event setSpeed(float* speed, Object* player); // Devuelve el evento que cambia la velocidad a un objeto
	static Event goToMap(string* map_name, sf::Vector2i* pos); // Devuelve el evento lleva al jugador a otro mapa
	static Event toWin(); // Devuelve el evento que da la victoria (provicional)
	void Destroy(); // Libera la memoria
private:
	friend class Function;
	Tag tag;
	Info info;
};

