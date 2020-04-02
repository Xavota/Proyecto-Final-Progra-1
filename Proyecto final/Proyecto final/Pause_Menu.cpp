#include "Pause_Menu.h"
#include "Game.h"

Pause_Menu::Pause_Menu()
{
}

Pause_Menu::~Pause_Menu()
{
}

void Pause_Menu::Init(sf::RenderWindow* window)
{
	game = Game::getInstance();
	pm_window = window;
	pm_box.setPosition(pm_window->getView().getCenter() + sf::Vector2f(5.f - pm_window->getSize().x / 2, 5.f - pm_window->getSize().y / 2));
	pm_box.setSize({ pm_window->getSize().x / 4.f, 300.f});
	pm_box.setFillColor(sf::Color(game->box_color.r, game->box_color.g, game->box_color.b, 127.5f));
	pm_edge.setFillColor(sf::Color::Transparent);
	pm_edge.setOutlineThickness(5);
	pm_edge.setOutlineColor(game->edge_color);
	pm_edge.setSize(pm_box.getSize() + sf::Vector2f(-5.f, -5.f));
	pm_edge.setPosition(pm_box.getPosition() + sf::Vector2f(2.5f, 2.5f));
	vector<string> texts = { "Resume", "Inventory", "Equipment", "Magic", "Save game", "Load game", "Exit game" };
	pm_texts_font.loadFromFile("Fonts/Hijakers.otf");
	pm_bm.Init();
	for (int i = 0; i < texts.size(); i++){
		/*pm_buttons.push_back(Button(pm_box.getPosition() + (i != 0 ? sf::Vector2f(20.f, pm_buttons[i - 1].btn_text.getPosition().y + pm_buttons[i - 1].btn_text.getGlobalBounds().height + 20.f) : sf::Vector2f(20.f, 20.f)),
			texts[i], Button::left, "Fonts/Hijakers.otf", 15));
		pm_buttons[i].setFont("Fonts/Hijakers.otf");
		pm_buttons[i].setSize({ pm_box.getSize().x - 30.f, pm_buttons[i].btn_text.getGlobalBounds().height + 10.f });
		if (pm_texts_height < pm_buttons[i].getSize().y) {
			pm_texts_height = pm_buttons[i].getSize().y;
		}
		pm_buttons[i].setActive(true);*/
		pm_bm.AddButton(Button(pm_box.getPosition() + (i != 0 ? sf::Vector2f(20.f, pm_bm.bm_btns[i - 1].btn_text.getPosition().y + pm_bm.bm_btns[i - 1].btn_text.getGlobalBounds().height + 20.f) : sf::Vector2f(20.f, 20.f)),
			texts[i], Button::left, "Fonts/Hijakers.otf", 15));
		pm_bm.bm_btns[i].setFont("Fonts/Hijakers.otf");
		pm_bm.bm_btns[i].setSize({ pm_box.getSize().x - 30.f, pm_bm.bm_btns[i].btn_text.getGlobalBounds().height + 10.f });
		if (pm_texts_height < pm_bm.bm_btns[i].getSize().y) {
			pm_texts_height = pm_bm.bm_btns[i].getSize().y;
		}
	}
	pm_bm.SetActive(true);
	pm_money_box.setSize({ pm_window->getSize().x / 4.f, 50.f });
	pm_money_box.setPosition(pm_window->getView().getCenter() + sf::Vector2f(5.f - pm_window->getSize().x / 2, -5.f + pm_window->getSize().y / 2) - sf::Vector2f{ 0, pm_money_box.getSize().y });
	pm_money_box.setFillColor(sf::Color(game->box_color.r, game->box_color.g, game->box_color.b, 127.5f));
	pm_money_edge.setFillColor(sf::Color::Transparent);
	pm_money_edge.setOutlineThickness(5);
	pm_money_edge.setOutlineColor(game->edge_color);
	pm_money_edge.setSize(pm_money_box.getSize() + sf::Vector2f(-5.f, -5.f));
	pm_money_edge.setPosition(pm_money_box.getPosition() + sf::Vector2f(2.5f, 2.5f));
}

void Pause_Menu::Update(sf::Time deltaTime)
{
	int btn_pressed = pm_bm.Update(deltaTime);
	switch (btn_pressed)
	{
	case 0:
		game->pause = false;
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		game->Save(0);
		break;
	case 5:
		game->Load(0);
		break;
	case 6:
		game->mWindow.close();
		break;
	default:
		break;
	}
	for (int i = 0; i < pm_bm.bm_btns.size(); i++) {
		pm_bm.bm_btns[i].setPosition((i != 0 ? pm_bm.bm_btns[i - 1].getPosition() + sf::Vector2f(0.f, pm_bm.bm_btns[i - 1].getSize().y + 10.f) : pm_box.getPosition() + sf::Vector2f(15.f, 15.f)));
		pm_bm.bm_btns[i].setSize({ pm_box.getSize().x - 30.f, pm_texts_height });
		pm_bm.bm_btns[i].Update(deltaTime);
	}
	pm_box.setPosition(pm_window->getView().getCenter() + sf::Vector2f(5.f - pm_window->getSize().x / 2, 5.f - pm_window->getSize().y / 2));
	pm_box.setSize({ pm_window->getSize().x / 4.f, pm_bm.bm_btns.size() * (pm_texts_height + 10.f) + 30.f });
	pm_edge.setSize(pm_box.getSize() + sf::Vector2f(-5.f, -5.f));
	pm_edge.setPosition(pm_box.getPosition() + sf::Vector2f(2.5f, 2.5f));
	pm_money_box.setSize({ pm_window->getSize().x / 4.f, 50.f });
	pm_money_box.setPosition(pm_window->getView().getCenter() + sf::Vector2f(5.f - pm_window->getSize().x / 2, -5.f + pm_window->getSize().y / 2) - sf::Vector2f{ 0, pm_money_box.getSize().y });
	pm_money_edge.setSize(pm_money_box.getSize() + sf::Vector2f(-5.f, -5.f));
	pm_money_edge.setPosition(pm_money_box.getPosition() + sf::Vector2f(2.5f, 2.5f));
}

void Pause_Menu::handleInputs(sf::Keyboard::Key key, bool ispressed)
{
	if (game->pause) {
		pm_bm.handleInputs(key, ispressed);
	}
}

void Pause_Menu::Render(sf::RenderWindow * window)
{
	if (game->pause) {
		window->draw(pm_box);
		window->draw(pm_edge);
		pm_bm.Render(window);
		window->draw(pm_money_box);
		window->draw(pm_money_edge);
	}
}

void Pause_Menu::Destroy()
{
}
