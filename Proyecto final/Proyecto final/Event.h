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
		dialog_box, set_speed, go_to_map
	};
	struct Info {
		Info() {};
		Info(vector<void*> v) { v1 = v; };
		vector<void*> v1;
	};
	Event();
	Event(Tag t, Info i);
	~Event();
	static Event DialogBox(string file_name, int pos);
	static Event setSpeed(float* speed, Player* player);
	static Event goToMap(string* map_name, sf::Vector2f* pos);
private:
	friend class Function;
	Tag tag;
	Info info;
};

