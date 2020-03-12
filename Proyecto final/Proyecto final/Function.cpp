#include "Function.h"
#include "Game.h"
Function::Function()
{
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

void Function::Init(sf::RenderWindow* w, vector<Event> e, string n)
{
	f_dialogBox = Dialog_box::getInstance();
	f_dialogBox->Init(w, sf::Color::Blue, sf::Color::White, sf::Color::White, "Fonts/Drawingfree.ttf", 40, .1f);
	events = e;
	f_name = n;
	game = Game::getInstance();
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
			setSpeed(*((float*)(events[f_nEvent].info.v1[0])), ((Player*)(events[f_nEvent].info.v1[1])));
			break;
		case Event::Tag::go_to_map:
			GoToMap(*((string*)(events[f_nEvent].info.v1[0])), *((sf::Vector2f*)(events[f_nEvent].info.v1[1])));
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

void Function::setSpeed(float speed, Player * player)
{
	player->Speed = speed;
	f_nEvent++;
}

void Function::GoToMap(const string& map_name, sf::Vector2f pos)
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
