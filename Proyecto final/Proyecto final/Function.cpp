#include "Function.h"
#include "Game.h"
Function::Function()
{
}

/*Function::Function(sf::RenderWindow * w, vector<Event> e, string n)
{
	Init(w, e, n);
}*/
Function::Function(string func_file_name) 
{
	Init(func_file_name);
}

Function::~Function()
{
}

void Function::Start()
{
	f_Active = true;
}

void Function::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
	if (f_Active) {
		if (key == sf::Keyboard::Return) {
			if (!key_pressed) {
				key_pressed = true;
				EnterPressed = isPressed;
			}
			else if (!isPressed) {
				key_pressed = isPressed;
			}
		}
	}
}

//void Function::Init(sf::RenderWindow* w, vector<Event> e, string n)
void Function::Init(string func_file_name)
{
	/*f_dialogBox = Dialog_box::getInstance();
	f_dialogBox->Init(w, sf::Color::Blue, sf::Color::White, sf::Color::White, "Fonts/Hijakers.otf", 20, .1f);
	events = e;
	f_name = n;
	game = Game::getInstance();*/
	game = Game::getInstance();
	f_dialogBox = Dialog_box::getInstance();
	f_dialogBox->Init(&game->mWindow, sf::Color::Blue, sf::Color::White, sf::Color::White, "Fonts/Hijakers.otf", 20, .1f);
	vector<Event> e;
	int newLine = 1; 
	ifstream func_file;
	while (newLine != 0)
	{
		func_file.open( func_file_name );
		int Line;
		do {
			func_file >> Line;
			if (Line != newLine) {
				string pass;
				getline(func_file, pass);
			}
		} while (Line != newLine && !func_file.eof());
		if (!func_file.eof()) {
			string event_name;
			char c = 0;
			func_file >> event_name;
			if (event_name == "set_speed") {
				func_file >> noskipws;
				while (c != '(')
				{
					func_file >> c;
				}
				func_file >> skipws;
				float * speed = new float();
				func_file >> *speed;
				func_file >> noskipws;
				while (c != '"')
				{
					func_file >> c;
				}
				string obj_name = "";
				func_file >> c;
				while (c != '"')
				{
					obj_name += c;
					func_file >> c;
				}
				func_file >> c;
				func_file >> skipws;
				if (c == ')')
					e.push_back(Event::setSpeed(speed, Object::getObject(obj_name)));
				func_file >> newLine;
			}
			else if (event_name == "dialog_box") {
				func_file >> noskipws;
				while (c != '(')
				{
					func_file >> c;
				}
				while (c != '"')
				{
					func_file >> c;
				}
				string dialog_file_name = "";
				func_file >> c;
				while (c != '"')
				{
					dialog_file_name += c;
					func_file >> c;
				}
				func_file >> c;
				func_file >> skipws;
				int dialog_line;
				func_file >> dialog_line;
				func_file >> noskipws >> c >> skipws;
				if (c == ')')
					e.push_back(Event::DialogBox(dialog_file_name, dialog_line));
				func_file >> newLine;
			}
			else if (event_name == "go_to_map") {
				func_file >> noskipws;
				while (c != '(')
				{
					func_file >> c;
				}
				while (c != '"')
				{
					func_file >> c;
				}
				string* map_name = new string("");
				func_file >> c;
				while (c != '"')
				{
					*map_name += c;
					func_file >> c;
				}
				func_file >> c;
				func_file >> skipws;
				sf::Vector2i* pos = new sf::Vector2i();
				func_file >> *pos;
				func_file >> noskipws >> c;
				if (c == ')')
					e.push_back(Event::goToMap(map_name, pos));
				func_file >> newLine;
			}
			func_file.close();
		}
		else{
			func_file.close();
			cout << "Linea " << Line << "no encontrada en funcion " << func_file_name << endl;
			break;
		}
	}
	events = e;
}

void Function::Update(sf::Time deltaTime)
{
	if (f_Active) {
		switch (events[f_nEvent].tag)
		{
		case Event::Tag::dialog_box:
			TextBox(*((string*)(events[f_nEvent].info.v1[0])));
			break;
		case Event::Tag::set_speed:
			setSpeed(*((float*)(events[f_nEvent].info.v1[0])), ((Object*)(events[f_nEvent].info.v1[1])));
			break;
		case Event::Tag::go_to_map:
			GoToMap(*((string*)(events[f_nEvent].info.v1[0])), *((sf::Vector2i*)(events[f_nEvent].info.v1[1])));
		default:
			break;
		}
		if (f_nEvent == events.size()) {
			f_Active = false;
			f_nEvent = 0;
		}
	}
	f_dialogBox->Update(deltaTime);
}

void Function::Render(sf::RenderWindow* w)
{
	f_dialogBox->Render(w);
}

void Function::Destroy()
{
}

void Function::TextBox(string text)
{
	if (!f_working) {
		f_dialogBox->setActive(true);
		f_dialogBox->Write(text);
		f_working = true;
	}
	else {
		if (EnterPressed) {
			f_dialogBox->Write("");
			f_dialogBox->setActive(false);
			f_working = false;
			f_nEvent++;
			EnterPressed = false;
		}
	}
}

void Function::setSpeed(float speed, Object * player)
{
	player->Speed = speed;
	f_nEvent++;
}

void Function::GoToMap(const string& map_name, sf::Vector2i pos)
{
	try
	{
		game->mm.GoToMap(map_name, pos);
	}
	catch (runtime_error e)
	{
		cerr << e.what() << endl;
	}
	f_nEvent++;
}

istream & operator>>(istream & is, sf::Vector2i& v)
{
	char c = 0;
	is >> noskipws;
	while (c != '{')
	{
		is >> c;
		if (c != ' ' && c != '{') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	is >> skipws;
	int i, j;
	is >> i >> j; 
	if (is.fail())
		return is;
	is >> noskipws >> c;
	while (c != '}') {
		is >> c;
		if (c != ' ' && c != '}') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	is >> skipws;
	v = { i, j };
	return is;
}
