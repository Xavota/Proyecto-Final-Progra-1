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

Event Event::DialogBox(string file_name, int pos)
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

Event Event::setSpeed(float* speed, Player* player)
{
	return Event{ Tag::set_speed, Info{{{(void*)(speed), (void*)(player)}}} };
}
