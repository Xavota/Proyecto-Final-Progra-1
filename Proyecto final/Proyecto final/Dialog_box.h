#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;
class Dialog_box
{
public:
	static Dialog_box* getInstance();
	~Dialog_box();
	void setBoxColor(sf::Color box_color);
	void setEdgeColor(sf::Color edge_color);
	void setTextColor(sf::Color text_color);
	void setTextFont(const string& text_font_file);
	void setTexSize(int text_size);
	void setTextVelocity(float text_velocity);
	void setActive(bool active);
	void Write(const string& text);
	void Init(sf::RenderWindow * window, sf::Color box_color, sf::Color edge_color, sf::Color text_color, const string& text_font_file, int text_size, float text_velocity);
	void Update(sf::Time deltaTime);
	string AdjustText(string s);
	void Render(sf::RenderWindow* window);
	void Destroy();
private:
	static Dialog_box* instance;
	Dialog_box();
	sf::RectangleShape db_Rectangle;
	sf::Vector2f db_Normal_Size;
	sf::Color db_box_color, db_edge_color, db_text_color;
	vector<sf::RectangleShape> db_edge{ sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape() };
	sf::Text db_text;
	sf::Font db_text_font;
	sf::RenderWindow * db_game_window;
	float db_text_velocity = 0, Time = 0, db_y_size = 0;
	string db_text_text;
	bool db_active = false, db_writing = false;
	int letter = 0;
};

