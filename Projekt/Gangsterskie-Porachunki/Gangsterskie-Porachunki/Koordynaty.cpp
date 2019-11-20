#include "Koordynaty.h"

#include <string.h>


Koordynaty::Koordynaty() : Koordynaty(-1, -1)
{
}

Koordynaty::Koordynaty(int _x, int _y) : x(_x), y(_y)
{
}


Koordynaty::~Koordynaty()
{
}

Koordynaty::Kierunek Koordynaty::KierunekZStr(const char * kierunekStr)
{
	if (strcmp(kierunekStr, "N") == 0) {
		return N;
	}
	if (strcmp(kierunekStr, "NE") == 0) {
		return NE;
	}
	if (strcmp(kierunekStr, "E") == 0) {
		return E;
	}
	if (strcmp(kierunekStr, "SE") == 0) {
		return SE;
	}
	if (strcmp(kierunekStr, "S") == 0) {
		return S;
	}
	if (strcmp(kierunekStr, "SW") == 0) {
		return SW;
	}
	if (strcmp(kierunekStr, "W") == 0) {
		return W;
	}
	if (strcmp(kierunekStr, "NW") == 0) {
		return NW;
	}
	return NILL;
}

Koordynaty Koordynaty::operator+(Kierunek kierunekRuchu)
{
	Koordynaty _tymczasoweKoordynaty(*this);
	_tymczasoweKoordynaty += kierunekRuchu;
	return _tymczasoweKoordynaty;
}

Koordynaty & Koordynaty::operator+=(Kierunek kierunekRuchu)
{
	switch (kierunekRuchu)
	{
	case N:
	case NE:
	case NW:
		y--;
		break;
	case S:
	case SE:
	case SW:
		y++;
		break;
	default:
		break;
	}
	switch (kierunekRuchu) {
	case E:
	case NE:
	case SE:
		x++;
		break;
	case W:
	case NW:
	case SW:
		x--;
		break;
	default:
		break;
	}
	return *this;
}
