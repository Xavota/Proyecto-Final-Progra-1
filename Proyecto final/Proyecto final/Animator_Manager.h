#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;
class Animator_Manager // Hace posible las animaciones de objetos
{
public:
	enum AnimationTypes {
		idle, movement
	};
	enum AnimationFace {
		up, down, left, right
	};
	class Animation { // Los datos necesarios para mostrar una animaci�n
	public:
		Animation(string file_name, AnimationTypes type, AnimationFace face) { a_file_name = file_name; a_type = type; a_face = face; }
	private:
		friend class Player;
		friend class Object;
		friend class Animator_Manager;
		friend class Trigger;
		vector<sf::Vector2u> a_coords;
		string a_file_name;
		string a_name;
		AnimationTypes a_type;
		AnimationFace a_face;
		sf::Texture a_texture;
		int x, y;
		float a_velocity;
	};
	Animator_Manager();
	~Animator_Manager();
	void setAnimation(Animation& anim); // Agerga una animaci�n
	void SetState(const string& a); // Setea el estado actual para activar esa animaci�n dando su nombre
	void SetState(Animation a); // Setea el estado actual para activar esa animaci�n dando la animaci�n 
	void SetState(AnimationTypes type, AnimationFace face); // Setea el estado actual para activar esa animaci�n dando su tipo y direcci�n
	void SetState(AnimationTypes type); // Setea el estado actual para activar esa animaci�n dando tipo y manteniendo la direcci�n
	void SetState(AnimationFace face); // Setea el estado actual para activar esa animaci�n dando su direcci�n y manteniendo su tipo
	void SetVelocity(float v); // Setea la velocidad de los fotogramas de la animaci�n
	void SetTexture(sf::Texture * texture, int x, int y); // Setea la textura donde est� la animaci�n
	string getState(); // Devuelve el nombre del estado actual
	Animation& getAnimation(const string& name); // Devuelve la animaci�n seg�n su nombre
	Animation& getAnimation(AnimationTypes type, AnimationFace face); // Devuelve la animaci�n seg�n su tipo y direcci�n
	Animation& getAnimation(); // Devuelve la animaci�n actual
	void Init(sf::RectangleShape& AM_a_o); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclio
	void Render(); // Renderiza lo necesario
	void Destroy(); // Libera la memoria
	float Time = 0;
private:
	vector<Animation> AM_Animations;
	vector<Animation>::iterator AM_AnimIt;
	string AM_state = "";
	sf::RectangleShape* AM_animated_object;
	sf::Texture AM_texture;
	sf::Vector2u AM_texture_size;
	float AM_velocity;
	int AM_foto_gram;
};
