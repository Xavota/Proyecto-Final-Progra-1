#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
using namespace std;
class Animator_Manager
{
public:
	enum AnimationTypes {
		idle, movement
	};
	struct Animation {
		vector<sf::Vector2u> a_coords;
		string a_name;
		AnimationTypes a_type;
	};
	Animator_Manager();
	~Animator_Manager();
	void setAnimation(vector<sf::Vector2u> coords, string name, AnimationTypes am_type);
	void SetState(const string& a);
	void SetVelocity(float v);
	void SetTexture(const string& AM_location, int x, int y);
	string getState();
	Animation& getAnimation(const string& name);
	void Init(sf::RectangleShape& AM_a_o, float v, const string& AM_location, int x, int y);
	void Update(sf::Time deltaTime);
	void Render();
	void Destroy();
private:
	vector<Animation> AM_Animations;
	vector<Animation>::iterator AM_AnimIt;
	string AM_state = "";
	sf::RectangleShape* AM_animated_object;
	sf::Texture AM_texture;
	sf::Vector2u AM_texture_size;
	float AM_velocity;
	float Time;
	int AM_foto_gram;
};
