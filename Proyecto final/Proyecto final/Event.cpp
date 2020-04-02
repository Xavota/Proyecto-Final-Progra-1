#include "Event.h"

Event::Event()
{
}

Event::Event(Tag t, Info i)
{
	tag = t;
	info = i;
}

Event::~Event()
{
}

Event Event::DialogBox(string file_name, int pos) // Toma el texto del archivo indicado y en la posición dada y crea un evento para escribir ese texto en un cuadro de dialogo
{
	string *a = new string(), b;
	ifstream text{ file_name };
	if (!text) {
		text.close();
		return Event{ Tag::dialog_box, Info{{(void*)(new string("Text not found"))}} };
	}
	int count;
	bool correcto = false;
	while (!(text.eof())) {
		text >> count;
		if (count == pos) {
			char c = 0;
			text >> noskipws;
			text >> c >> c;
			while (!(text.eof())) {
				if (c == '\n')
					break;
				*a += c;
				text >> c;
			}
			text >> skipws;
			correcto = true;
			break;
		}
		getline(text, b);
	}
	text.close();
	if (!correcto)
		return Event{ Tag::dialog_box, Info{{(void*)(new string("Text not found"))}} };
	return Event{ Tag::dialog_box, Info{{(void*)(a)}} };
}

Event Event::setSpeed(float* speed, Object* player) // Crea el evento para setear la velocidad a un objeto
{
	return Event{ Tag::set_speed, Info{{(void*)(speed), (void*)(player)}} };
}

Event Event::goToMap(string * map_name, sf::Vector2i* pos) // Crea el evento para ir a un mapa
{
	return Event(Tag::go_to_map, Info{ {(void*)(map_name), (void*)(pos)} });
}

Event Event::toWin() // Crea el evento para ganar (provicional)
{
	return Event(Tag::to_win, Info{});
}

void Event::Destroy()
{
	/*for (void * z : info.v1) {
		if (z != nullptr) {
			delete z;
			z = nullptr;
		}
	}*/
}
