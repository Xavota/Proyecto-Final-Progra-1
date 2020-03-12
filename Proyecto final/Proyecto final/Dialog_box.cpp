#include "Dialog_box.h"



Dialog_box::Dialog_box()
{
}


Dialog_box::~Dialog_box()
{
}

void Dialog_box::setBoxColor(sf::Color box_color)
{
	db_box_color = box_color;
	db_Rectangle.setFillColor(sf::Color::Color(db_box_color.r, db_box_color.g, db_box_color.b, 127.5f));
}

void Dialog_box::setEdgeColor(sf::Color edge_color)
{
	db_edge_color = edge_color;
	for (int i = 0; i < 4; i++) {
		db_edge[i].setFillColor(db_edge_color);
	}
}

void Dialog_box::setTextColor(sf::Color text_color)
{
	db_text_color = text_color;
	db_text.setFillColor(db_text_color);
}

void Dialog_box::setTextFont(const string & text_font_file)
{
	db_text_font.loadFromFile(text_font_file);
	db_text.setFont(db_text_font);
}

void Dialog_box::setTexSize(int text_size)
{
	db_text.setCharacterSize(text_size);
}

void Dialog_box::setTextVelocity(float text_velocity)
{
	db_text_velocity = text_velocity;
}

void Dialog_box::setActive(bool active)
{
	db_Rectangle.setFillColor(active ? sf::Color::Color(db_box_color.r, db_box_color.g, db_box_color.b, 127.5f) : sf::Color::Transparent);
	for (int i = 0; i < 4; i++) {
		db_edge[i].setFillColor(active ? db_edge_color : sf::Color::Transparent);
	}
	db_text.setFillColor(active ? db_text_color : sf::Color::Transparent);
	db_active = active;
}

void Dialog_box::Write(const string & text)
{
	db_text.setString("");
	db_text_text = text;
	db_writing = true;
	letter = 0;
}

void Dialog_box::Init(sf::RenderWindow * window, sf::Color box_color, sf::Color edge_color, sf::Color text_color, const string& text_font_file, int text_size, float text_velocity)
{
	db_game_window = window;
	db_Rectangle.setSize({ db_game_window->getSize().x - 10.f, 75.f});
	db_Rectangle.setOrigin(0, db_Rectangle.getSize().y);
	db_Rectangle.setPosition({5.f, db_game_window->getSize().y - 5.f});
	for (int i = 0; i < 4; i++) {
		db_edge[i].setSize(i % 2 == 0 ? sf::Vector2f(db_game_window->getSize().x - 5.f, 5.f) : sf::Vector2f(5.f, 80.f));
		db_edge[i].setPosition(db_Rectangle.getPosition() + sf::Vector2f(i != 1 ? -2.5f : db_game_window->getSize().x - 10.f, i != 2 ? -77.5f : -2.5f));
	}
	db_text.setPosition(db_Rectangle.getPosition() + sf::Vector2f(15.f, -75.f));
	setBoxColor(box_color);
	setEdgeColor(edge_color);
	setTextColor(text_color);
	setTextFont(text_font_file);
	setTexSize(text_size);
}

void Dialog_box::Update(sf::Time deltaTime)
{
	if (db_active && db_writing) {
		Time += deltaTime.asSeconds();
		if (Time >= db_text_velocity) {
			db_text.setString(db_text.getString() + db_text_text[letter]);
			letter++;
		}
		if (letter == db_text_text.size()) {
			db_writing = false;
			db_text_text = "";
			letter = 0;
		}
		Time = 0;
	}
	db_Rectangle.setPosition({ db_game_window->getView().getCenter().x + 5.f - db_game_window->getSize().x / 2, db_game_window->getView().getCenter().y - 5.f  + db_game_window->getSize().y / 2 });
	for (int i = 0; i < 4; i++) {
		db_edge[i].setPosition(db_Rectangle.getPosition() + sf::Vector2f(i != 1 ? -2.5f : db_game_window->getSize().x - 10.f, i != 2 ? -77.5f : -2.5f));
	}
	db_text.setPosition(db_Rectangle.getPosition() + sf::Vector2f(15.f, -75.f));
}

void Dialog_box::Render(sf::RenderWindow * window)
{
	window->draw(db_Rectangle);
	for (int i = 0; i < 4; i++) {
		window->draw(db_edge[i]);
	}
	window->draw(db_text);
}

void Dialog_box::Destroy()
{
}
