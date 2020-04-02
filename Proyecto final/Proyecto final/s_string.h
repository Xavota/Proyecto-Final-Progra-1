#pragma once
#include <iostream>
#include <string>
using namespace std;
class s_string // Un seudo string, para leer desde un archivo
{
public:
	s_string();
	~s_string();
	string str;
};
istream& operator>>(istream& is, s_string& ss); // El operador sobrecargado para leer el seudo string
