#include "Pionek.h"

using Kierunek = Koordynaty::Kierunek;

bool Pionek::CzyMoznaPrzejscNaPozycje(int pozycjaDocelowaX, int pozycjaDocelowaY, Pionek *** aktualnaMapa, const int rozmiarMapy) const
{
	if (pozycjaDocelowaX < 0 || pozycjaDocelowaX >= rozmiarMapy || pozycjaDocelowaY < 0 || pozycjaDocelowaY >= rozmiarMapy) {
		return false;
	}
	return aktualnaMapa[pozycjaDocelowaY][pozycjaDocelowaX]==nullptr;
}

bool Pionek::CzyMoznaPrzejscNaPozycje(Koordynaty& pozycjaDocelowa, Pionek *** aktualnaMapa, const int rozmiarMapy) const
{
	return CzyMoznaPrzejscNaPozycje(pozycja.x, pozycja.y, aktualnaMapa, rozmiarMapy);
}


Pionek::Pionek(char _znakWyswietlany, int _pozycjaX, int _pozycjaY): znakWyswietlany(_znakWyswietlany), pozycja(Koordynaty(_pozycjaX,_pozycjaY))
{
}


Pionek::~Pionek()
{
}

int Pionek::PozycjaX() const
{
	return pozycja.x;
}

int Pionek::PozycjaY() const
{
	return pozycja.y;
}


bool Pionek::CzyJestZablokowany(Pionek *** aktualnaMapa, const int rozmiarMapy) const
{
	for (int i = pozycja.x - 1; i <= pozycja.x + 1; i++) {
		for (int j = pozycja.y - 1; j <= pozycja.y + 1; j++) {
			if (CzyMoznaPrzejscNaPozycje(i, j, aktualnaMapa, rozmiarMapy)) {
				return false;
			}
		}
	}
	return true;
}

bool Pionek::PoruszOJednoPole(Kierunek kierunekRuchu, Pionek *** aktualnaMapa, const int rozmiarMapy)
{
	Koordynaty nowaPozycja = pozycja + kierunekRuchu;
	if (CzyMoznaPrzejscNaPozycje(nowaPozycja.x, nowaPozycja.y, aktualnaMapa, rozmiarMapy)) {
		aktualnaMapa[nowaPozycja.y][nowaPozycja.x] = this;
		aktualnaMapa[pozycja.y][pozycja.x] = nullptr;
		pozycja = nowaPozycja;
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

