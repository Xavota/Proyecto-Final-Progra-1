#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;
class Animator_Manager
{
public:
	enum AnimationTypes {
		idle, movement
	};
	enum AnimationFace {
		up, down, left, right
	};
	class Animation {
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
	void setAnimation(Animation& anim);
	void SetState(const string& a);
	void SetState(Animation a);
	void SetState(AnimationTypes type, AnimationFace face);
	void SetState(AnimationTypes type);
	void SetState(AnimationFace face);
	void SetVelocity(float v);
	void SetTexture(sf::Texture * texture, int x, int y);
	string getState();
	Animation& getAnimation(const string& name);
	Animation& getAnimation(AnimationTypes type, AnimationFace face);
	Animation& getAnimation();
	void Init(sf::RectangleShape& AM_a_o);
	void Update(sf::Time deltaTime);
	void Render();
	void Destroy();
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
	void getLine(istream& is, string& s);
};
