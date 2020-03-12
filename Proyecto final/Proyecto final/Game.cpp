#include "Game.h"
Game* Game::instance = nullptr;
Game * Game::getInstance()
{
	if (instance == nullptr)
		instance = new Game();
	return instance;
}

Game::Game()
{
}

void Game::Init()
{
	mWindow.create(sf::VideoMode(512, 512), "SFML Application");
	g_npc->Init({ 6.f, 2.f });
	g_npc->p_Animation().Init(g_npc->p_shape, .2f, "CharactersAnimations/May be it is.png", 12, 8);
	g_npc->p_Animation().setAnimation({ sf::Vector2u{1, 0} }, "idle_abajo", Animator_Manager::idle);
	g_npc->p_Animation().SetState("idle_abajo");
	g_player->Init({ 0.f, 0.f });
	FM.Init();
	FM.CreateFunction(&mWindow, { Event::setSpeed(new float(0.f), g_player)
	, Event::DialogBox("DialogosNPC/generico.txt", 1)
	, Event::DialogBox("DialogosNPC/generico.txt", 2)
	, Event::setSpeed(new float(100.f), g_player) }, "Inicio");
	FM.CreateFunction(&mWindow, { Event::goToMap(new string("Inicio"), new sf::Vector2f{ 0.f, 0.f }) }, "Ir a mapa");
	FM.CreateTrigger(Trigger::onTriggerEnter({ 2, 2 }, { 4, 4 }, g_player), "Inicio");
	FM.CreateTrigger(Trigger::onTriggerExit({ 2, 2 }, { 4, 4 }, g_player), "Inicio");
	FM.CreateTrigger(Trigger::onInteract(g_npc, g_player), "Ir a mapa");
	mm.AddMap(Map({ 20.f, 20.f }, vector<Map::Layer>{ Map::Layer{"Maps/Identificators/Principal_layer1.txt", "Maps/Layers/Layer1.txt", 1}, 
		Map::Layer{ "Maps/Identificators/Principal_layer2.txt", "Maps/Layers/Layer2.txt", 2 } }, &mWindow), "Inicio");
	mm.GoToMap("Inicio", { 0.f, 0.f });
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	FM.handleInputs(key, isPressed);
	g_player->handleInputs(key, isPressed);
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	FM.Update(deltaTime);
	mm.Update(deltaTime);
	g_npc->Update(deltaTime);
	g_player->Update(deltaTime);
}

void Game::render()
{
	mWindow.clear();
	mm.Render(&mWindow);
	g_npc->Render(&mWindow);
	g_player->Render(&mWindow);
	FM.Render(&mWindow);
	mWindow.display();
}

void Game::Destroy()
{
}
