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
	mm.AddMap(Map({ 20.f, 20.f }, { Map::Layer{ "Maps/Layers/Inicio/Layer1.txt", 1 },
		Map::Layer{ "Maps/Layers/Inicio/Layer2.txt", 2 } }, &mWindow), "Inicio");
	mm.AddMap(Map({ 10.f, 10.f }, { Map::Layer{ "Maps/Layers/Casa/Layer1.txt", 1 },
		Map::Layer{ "Maps/Layers/Casa/Layer2.txt", 2 },
		Map::Layer{ "Maps/Layers/Casa/Layer3.txt", 3 } }, &mWindow), "Casa");
	mm.getMap("Inicio").AddNPC(new NPC({ 6.f, 2.f }, { 
		Animator_Manager::Animation{"Animations/Animations/Generico/Idle_down.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::down},
		Animator_Manager::Animation{"Animations/Animations/Generico/Idle_up.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::up}, 
		Animator_Manager::Animation{"Animations/Animations/Generico/Idle_left.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::left}, 
		Animator_Manager::Animation{"Animations/Animations/Generico/Idle_right.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::right} },
		"Generico"));
	g_player = new Player({ 0.f, 0.f }, { 
		Animator_Manager::Animation{"Animations/Animations/Principal/Movement_down.txt", Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::down},
		Animator_Manager::Animation{"Animations/Animations/Principal/Movement_up.txt", Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::up} ,
		Animator_Manager::Animation{"Animations/Animations/Principal/Movement_left.txt", Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::left} ,
		Animator_Manager::Animation{"Animations/Animations/Principal/Movement_right.txt", Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::right} ,
		Animator_Manager::Animation{"Animations/Animations/Principal/Idle_down.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::down} ,
		Animator_Manager::Animation{"Animations/Animations/Principal/Idle_up.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::up} ,
		Animator_Manager::Animation{"Animations/Animations/Principal/Idle_left.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::left} ,
		Animator_Manager::Animation{"Animations/Animations/Principal/Idle_right.txt", Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::right} },
		"Principal");
	/*mm.getMap("Inicio").FM->CreateFunction(Trigger::onTriggerEnter({ 2, 2 }, { 4, 4 }), Function("Function_Manager/Functions/Inicial/Inicial.txt"));
	mm.getMap("Inicio").FM->CreateFunction(Trigger::onTriggerExit({ 2, 2 }, { 4, 4 }), Function("Function_Manager/Functions/Inicial/Inicial.txt"));
	mm.getMap("Inicio").FM->CreateFunction(Trigger::onInteract(&mm.getMap("Inicio").GetNPC("Generico")), Function("Function_Manager/Functions/Inicial/Inicial.txt"));
	mm.getMap("Inicio").FM->CreateFunction(Trigger::onInteract({ 4, 3 }), Function("Function_Manager/Functions/Inicial/Ir a casa.txt"));
	mm.getMap("Casa").FM->CreateFunction(Trigger::onMapEnter(&mm.getMap("Casa")), Function("Function_Manager/Functions/Casa/Inicial.txt"));
	mm.getMap("Casa").FM->CreateFunction(Trigger::onInteract({ 5, 10 }), Function("Function_Manager/Functions/Casa/Ir a mapa.txt"));*/
	mm.getMap("Inicio").setMapTriggers("Function_Manager/Triggers/Inicial.txt");
	mm.getMap("Casa").setMapTriggers("Function_Manager/Triggers/Casa.txt");
	mm.GoToMap("Inicio", { 0, 0 });
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
	g_player->handleInputs(key, isPressed);
	mm.handleInputs(key, isPressed);
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
	mm.Update(deltaTime);
	g_player->Update(deltaTime);
}

void Game::render()
{
	mWindow.clear();
	mm.Render(&mWindow);
	g_player->Render(&mWindow);
	mm.Render(&mWindow);
	mWindow.display();
}

void Game::Destroy()
{
	mm.Destroy();
	g_player->Destroy();
}
