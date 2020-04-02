#include "Function.h"
#include "Game.h"
Function::Function()
{
}

Function::Function(string func_file_name) 
{
	Init(func_file_name);
}

Function::~Function()
{
}

void Function::Start() // Activa la función
{
	f_Active = true;
}

void Function::handleInputs(sf::Keyboard::Key key, bool isPressed) // Convierte los inputs en acciones
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

void Function::Init(string func_file_name) // Inicializa la función desde un archivo
{
	game = Game::getInstance();
	f_dialogBox = Dialog_box::getInstance();
	f_dialogBox->Init(&game->mWindow, sf::Color::Blue, sf::Color::White, sf::Color::White, .1f);
	vector<Event> e;
	int newLine = 1; 
	ifstream func_file;
	while (newLine != 0) // Mientras la siuiente línea no sea 0, continua
	{
		func_file.open( func_file_name );
		int Line;
		do {
			func_file >> Line;
			if (Line != newLine) {
				string pass;
				getline(func_file, pass);
			}
		} while (Line != newLine && !func_file.eof()); // Lee cada función, desde su nombre, que esté entre paréntesis, los parámeros y la línea siguiente
		if (!func_file.eof()) { 
			string event_name;
			char c = 0;
			Event ev;
			func_file >> event_name;
			func_file >> noskipws;
			while (c != '(')
			{
				func_file >> c;
			}
			func_file >> skipws;
			if (event_name == "set_speed") {
				float * speed = new float();
				func_file >> *speed;
				s_string obj_name;
				func_file >> obj_name >> noskipws;
				ev = Event::setSpeed(speed, Object::getObject(obj_name.str));
			}
			else if (event_name == "dialog_box") {
				s_string dialog_file_name;
				func_file >> dialog_file_name;
				int dialog_line;
				func_file >> dialog_line >> noskipws;
				ev = Event::DialogBox(dialog_file_name.str, dialog_line);
			}
			else if (event_name == "go_to_map") {
				s_string s_map_name;
				func_file >> s_map_name;
				string* map_name = new string(s_map_name.str);
				sf::Vector2i* pos = new sf::Vector2i();
				func_file >> *pos >> noskipws;
				ev = Event::goToMap(map_name, pos);
			}
			else if (event_name == "win") {
				ev = Event::toWin();
			}
			do
			{
				func_file >> c;
				if (c != ')' && c != ' ' || func_file.fail()) {
					func_file.clear();
					cout << "set_speed: argumentos no validos" << endl;
					break;
				}
				else if (c == ')') {
					e.push_back(ev);
				}
			} while (c != ')');
			func_file >> skipws;
			func_file >> newLine;
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

void Function::Update(sf::Time deltaTime) // Cada ciclo
{
	if (f_Active) { // Si la función está activa, va evento por evento ejecutandolos
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
			break;
		case Event::Tag::to_win:
			Win();
			break;
		default:
			break;
		}
		if (f_nEvent == events.size()) {
			f_Active = false;
			f_nEvent = 0;
		}
	}
	f_dialogBox->Update(deltaTime); // Hace el update del cuadro de texto
}

void Function::Render(sf::RenderWindow* w) // Renderiza los objetos necesarios para las funciones
{
	f_dialogBox->Render(w);
}

void Function::Destroy() // Limpia la memoria
{
	f_dialogBox->Destroy();
	if (game != nullptr) {
		game = nullptr;
	}
	if (f_dialogBox != nullptr) {
		f_dialogBox = nullptr;
	}
	for (Event& ev : events) {
		ev.Destroy();
	}
}

void Function::TextBox(string text) // Función de escribit en el cuadro de diálogo
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

void Function::setSpeed(float speed, Object * player) // Función de setear la velocidad de un objeto
{
	player->Speed = speed;
	f_nEvent++;
}

void Function::GoToMap(const string& map_name, sf::Vector2i pos) // Función para ir a un mapa
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

void Function::Win() // Función para ganar (provicional)
{
	game->mWindow.close();
	sf::RenderWindow Win_cam{ sf::VideoMode{100, 100}, "You win" };
	sf::Text Win_text;
	sf::Font Win_text_font;
	Win_text.setString("You Win");
	Win_text_font.loadFromFile("Fonts/Hijakers.otf");
	Win_text.setFont(Win_text_font);
	Win_text.setCharacterSize(30);
	Win_text.setPosition({ Win_cam.getSize().x / 2 - Win_text.getGlobalBounds().width / 2, Win_cam.getSize().y / 2 - Win_text.getGlobalBounds().height / 2 });
	while (Win_cam.isOpen()) {
		sf::Event event;
		while (Win_cam.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Win_cam.close();
				break;
			}
		}
		Win_cam.clear();
		Win_cam.draw(Win_text);
		Win_cam.display();
	}
}

istream & operator>>(istream & is, sf::Vector2i& v) // La sobrecarga del operador para leer vector2i
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
