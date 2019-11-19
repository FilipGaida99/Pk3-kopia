#include "Pionek.h"

#include <string.h>



bool Pionek::CzyMoznaPrzejscNaPozycje(int pozycjaDocelowaX, int pozycjaDocelowaY, Pionek *** aktualnaMapa, const int rozmiarMapy) const
{
	if (pozycjaDocelowaX < 0 || pozycjaDocelowaX >= rozmiarMapy || pozycjaDocelowaY < 0 || pozycjaDocelowaY >= rozmiarMapy) {
		return false;
	}
	return aktualnaMapa[pozycjaDocelowaY][pozycjaDocelowaX]==nullptr;
}


Pionek::Pionek(char _znakWyswietlany, int _pozycjaX, int _pozycjaY): znakWyswietlany(_znakWyswietlany), pozycjaX(_pozycjaX), pozycjaY(_pozycjaY)
{
}


Pionek::~Pionek()
{
}

int Pionek::PozycjaX()
{
	return pozycjaX;
}

int Pionek::PozycjaY()
{
	return pozycjaY;
}


bool Pionek::CzyJestZablokowany(Pionek *** aktualnaMapa, const int rozmiarMapy) const
{
	for (int i = pozycjaX - 1; i <= pozycjaX + 1; i++) {
		for (int j = pozycjaY - 1; j <= pozycjaY + 1; j++) {
			if (CzyMoznaPrzejscNaPozycje(i, j, aktualnaMapa, rozmiarMapy)) {
				return false;
			}
		}
	}
	return true;
}

void Pionek::UzyskajNowaPozycje(int & pozycjaX, int & pozycjaY, Kierunek kierunekRuchu)
{
	switch (kierunekRuchu)
	{
	case Pionek::N:
	case Pionek::NE:
	case Pionek::NW:
		pozycjaY--;
		break;
	case Pionek::S:
	case Pionek::SE:
	case Pionek::SW:
		pozycjaY++;
		break;
	default:
		break;
	}
	switch (kierunekRuchu) {
	case Pionek::E:
	case Pionek::NE:
	case Pionek::SE:
		pozycjaX++;
		break;
	case Pionek::W:
	case Pionek::NW:
	case Pionek::SW:
		pozycjaX--;
		break;
	default:
		break;
	}
}

bool Pionek::PoruszOJednoPole(Kierunek kierunekRuchu, Pionek *** aktualnaMapa, const int rozmiarMapy)
{
	int nowaPozycjaX = pozycjaX;
	int nowaPozycjaY = pozycjaY;
	UzyskajNowaPozycje(nowaPozycjaX, nowaPozycjaY, kierunekRuchu);
	if (CzyMoznaPrzejscNaPozycje(nowaPozycjaX, nowaPozycjaY, aktualnaMapa, rozmiarMapy)) {
		aktualnaMapa[nowaPozycjaY][nowaPozycjaX] = this;
		aktualnaMapa[pozycjaY][pozycjaX] = nullptr;
		pozycjaX = nowaPozycjaX;
		pozycjaY = nowaPozycjaY;
		return true;
	}
	else {
		return false;
	}
}

char Pionek::WyswietlZnak(Przynaleznosc czyjeWyswietlic) const
{
	return znakWyswietlany;
}

Pionek::Kierunek Pionek::KierunekZStr(const char * kierunekStr)
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
