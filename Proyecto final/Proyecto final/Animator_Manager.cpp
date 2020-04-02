#include "Animator_Manager.h"

Animator_Manager::Animator_Manager()
{
}

Animator_Manager::~Animator_Manager()
{
}

void Animator_Manager::setAnimation(Animation& anim) // Lee el archivo donde está la animación y agrega los datos que usa
{
	ifstream anim_file{ anim.a_file_name };
	string texture_name_file;
	getline(anim_file, texture_name_file);
	anim.a_texture.loadFromFile(texture_name_file);
	anim_file >> anim.x >> anim.y;
	anim_file >> anim.a_velocity;
	char c;
	anim_file >> noskipws >> c >> skipws;
	getline(anim_file, anim.a_name);
	while (!(anim_file.eof()))
	{
		unsigned int x, y;
		anim_file >> x >> y;
		anim.a_coords.push_back({ x, y });
	}
	AM_Animations.push_back(anim);
}

void Animator_Manager::SetState(const string& a) // revisa que el nombre de la animación exista y la cambia
{
	for (AM_AnimIt = AM_Animations.begin(); AM_AnimIt != AM_Animations.end(); AM_AnimIt++) {
		if (AM_AnimIt->a_name == a) {
			string last_state = AM_state != "" ? AM_state : a;
			if (AM_state != "") {
				last_state = AM_state;
			}
			else {
				last_state = a;
				AM_foto_gram = 0;
			}
			AM_state = a;
			if (AM_AnimIt->a_type == getAnimation(last_state).a_type) { // Si el tipo de animación es el mismo que la anterior, mantiene el fotograma en que estaba
				AM_foto_gram = AM_foto_gram;
			}
			else { // Si no, lo reinicia
				AM_foto_gram = 0;
				Time = 0;
			}
			SetTexture(&AM_AnimIt->a_texture, AM_AnimIt->x, AM_AnimIt->y);
			AM_animated_object->setTextureRect(sf::IntRect(AM_texture_size.x * AM_AnimIt->a_coords[AM_foto_gram].x, AM_texture_size.y * AM_AnimIt->a_coords[AM_foto_gram].y, AM_texture_size.x, AM_texture_size.y));
			return;
		}
	}
	cout << "Estado no existente" << endl;
}

void Animator_Manager::SetState(Animation a) // Setea la animción recibida, en caso de existir
{
	SetState(a.a_name);
}

void Animator_Manager::SetState(AnimationTypes type, AnimationFace face) // Setea la animción según su tipo y dirección, en caso de existir
{
	SetState(getAnimation(type, face));
}

void Animator_Manager::SetState(AnimationTypes type) // Setea la animción según su tipo y manteniendo la dirección, en caso de existir
{
	SetState(getAnimation(type, getAnimation().a_face));
}

void Animator_Manager::SetState(AnimationFace face) // Setea la animción según su dirección y manteniendo su tipo, en caso de existir
{
	SetState(getAnimation(getAnimation().a_type, face));
}

void Animator_Manager::SetVelocity(float v) // Setea la velocidad de los fotogramas de la animación
{
	AM_velocity = v;
}

void Animator_Manager::SetTexture(sf::Texture * texture, int x, int y)  // Setea la textura donde se encuentra la animación, sabiendo la cantidad de iamgenes de la misma
{
	AM_animated_object->setTexture(texture);
	AM_texture_size = AM_animated_object->getTexture()->getSize();
	AM_texture_size.x /= x;
	AM_texture_size.y /= y;
}

string Animator_Manager::getState() // Regresa el nombre del estado actual
{
	return AM_state;
}

Animator_Manager::Animation& Animator_Manager::getAnimation(const string& name) // Regresa la animación según el nombre dado, en caso de haber una
{
	for (AM_AnimIt = AM_Animations.begin(); AM_AnimIt != AM_Animations.end(); AM_AnimIt++) {
		if (AM_AnimIt->a_name == name) {
			return *AM_AnimIt;
		}
	}
	throw runtime_error("Estado no existente");
}

Animator_Manager::Animation & Animator_Manager::getAnimation(AnimationTypes type, AnimationFace face) // Regresa la animación según el tipo y dirección dados, en caso de haber una
{
	for (AM_AnimIt = AM_Animations.begin(); AM_AnimIt != AM_Animations.end(); AM_AnimIt++) {
		if (AM_AnimIt->a_type == type && AM_AnimIt->a_face == face) {
			return *AM_AnimIt;
		}
	}
	throw runtime_error("Estado no existente");
}

Animator_Manager::Animation & Animator_Manager::getAnimation() // Regresa la animación actual 
{
	return getAnimation(AM_state);
}

void Animator_Manager::Init(sf::RectangleShape& AM_a_o) // Inicializa el objeto a animar
{
	AM_animated_object = &AM_a_o;
}

void Animator_Manager::Update(sf::Time deltaTime) // Cada ciclo
{
	Time += deltaTime.asSeconds(); // Suma el tiempo
	Animation current_anim = getAnimation();
	if (Time > current_anim.a_velocity) { // Si llega al tiempo de la velocidad de fotogramas avanza al siguiente
		AM_foto_gram = (AM_foto_gram + 1) % current_anim.a_coords.size();
		Time = 0; 
		AM_animated_object->setTextureRect(sf::IntRect(AM_texture_size.x * current_anim.a_coords[AM_foto_gram].x, AM_texture_size.y * current_anim.a_coords[AM_foto_gram].y, AM_texture_size.x, AM_texture_size.y));
	}
}

void Animator_Manager::Render() // No renderiza nada porque el objeto ya se tiene que renderizar solo
// Esta función existe para mantener estructura
{
}

void Animator_Manager::Destroy() // Libera la memoria
{
	if (AM_animated_object != nullptr) {
		delete AM_animated_object;
		AM_animated_object = nullptr;
	}
}