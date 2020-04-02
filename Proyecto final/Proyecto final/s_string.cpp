#include "s_string.h"

s_string::s_string()
{
}

s_string::~s_string()
{
}

istream & operator>>(istream & is, s_string& ss) // Sobrecarga del operador para leer un seudo string como si el compilador lo leyera desde el código (osea "entre comillas")
{
	char c = 0;
	is >> noskipws;
	while (c != '"')
	{
		is >> c;
		if (c != ' ' && c != '"' && c != '\n') {
			is.clear(ios_base::failbit);
			return is;
		}
	}
	ss.str = "";
	is >> c;
	while (c != '"')
	{
		ss.str += c;
		is >> c;
	}
	is >> skipws;
}
