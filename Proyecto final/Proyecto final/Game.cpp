#include "Game.h"
Game* Game::instance = nullptr; // Pone la instancia original en nullptr
Game * Game::getInstance() // Devuelve la instancia existente del Game
{
	if (instance == nullptr)
		instance = new Game();
	return instance;
}

Game::Game()
{
}

void Game::Init() // Inicia las variables, crea todo lo necesario para que funcione el juego
{
	mWindow.create(sf::VideoMode(640, 640), "SFML Application");
	mm.AddMap(Map({ 20.f, 20.f }, { Map::Layer{ "Maps/Layers/Inicio/Layer1.txt", 1 },
		Map::Layer{ "Maps/Layers/Inicio/Layer2.txt", 2 },
		Map::Layer{ "Maps/Layers/Inicio/Layer3.txt", 2 } }, &mWindow), "Inicio");
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
	mm.getMap("Inicio").setMapTriggers("Function_Manager/Triggers/Inicial.txt");
	mm.getMap("Casa").setMapTriggers("Function_Manager/Triggers/Casa.txt");
	mm.GoToMap("Inicio", { 0, 0 });
	pm.Init(&mWindow);
}

void Game::run() // Inicia el juego
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) // El game loop
	{
		processEvents();                              // Procesa eventos
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);                     // Hace el update
		}
		render();                                     // Renderiza
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) // Convierte inputs en acciones, carga el handleInputs de todos sus objetos que lo necesiten
{
	if (!pause) {
		g_player->handleInputs(key, isPressed);
		mm.handleInputs(key, isPressed);
	}
	else {
		pm.handleInputs(key, isPressed);
	}
	if (key == sf::Keyboard::Escape) {
		if (!keyPressed) {
			escPressed = isPressed;
			keyPressed = isPressed;
		}
		else if (!isPressed) {
			keyPressed = isPressed;
		}
	}
}

void Game::Save(int file) // Guarda el juego en el archivo del número dado
{
	ofstream Save_file;
	Save_file.open("Saves/" + to_string(file) + ".txt");

	Save_file << mm.getMap().map_name << endl;
	Save_file << g_player->p_shape.getPosition().x << " " << g_player->p_shape.getPosition().y << endl;
	Save_file.close();
}

void Game::Load(int file) // Carga el juego desde el archivo del número dado
{
	ifstream Load_file;
	Load_file.open("Saves/" + to_string(file) + ".txt");
	string map_name;
	Load_file >> map_name;
	float posX, posY;
	Load_file >> posX >> posY;
	Load_file.close();
	mm.GoToMap(map_name, { 0, 0 });
	g_player->p_shape.setPosition({ posX, posY });
}

void Game::processEvents() // Procesa los eventos del juego
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

void Game::update(sf::Time deltaTime) // Cada cilco de juego, carga cada update de los objetos que tiene
{
	if (!pause) { // Si no está pausado
		mm.Update(deltaTime);
		g_player->Update(deltaTime);
	}
	pm.Update(deltaTime);
	if (escPressed) { // Si presionas el escape, pausa o despausa el juego
		pause = !pause;
		escPressed = false;
	}
}

void Game::render() // Renderiza todo lo que necesita el juego
{
	mWindow.clear();
	mm.Render(&mWindow);
	g_player->Render(&mWindow);
	mm.Render(&mWindow);
	pm.Render(&mWindow);
	mWindow.display();
}

void Game::Destroy() // Libera la memora
{
	mm.Destroy();
	g_player->Destroy();
	pm.Destroy();
	if (g_player != nullptr) {
		delete g_player;
		g_player = nullptr;
	}
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}
