#include "Zapis.h"
#include <string.h>
#include "Rozgrywka.h"

using namespace std;

constexpr char Zapis::domyslnaNazwaPliku[];

Zapis::Zapis() : Zapis(domyslnaNazwaPliku)
{
}

Zapis::Zapis(const char * _nazwaPliku) : nazwaPliku(new char[strlen(_nazwaPliku) + 1])
{
	strcpy(nazwaPliku, _nazwaPliku);
}


Zapis::~Zapis()
{
	if(nazwaPliku) delete[] nazwaPliku;
}

Zapis & Zapis::operator=(Zapis && rZapis)
{
	char* tymczasowyPtr = nazwaPliku;
	nazwaPliku = rZapis.nazwaPliku;
	rZapis.nazwaPliku = tymczasowyPtr;
	return *this;
}

Zapis& Zapis::operator<<(const Rozgrywka& _rozgrywka)
{
	ofstream plik(nazwaPliku, ios::binary);
	if (plik) {
		//Zapis pionków
		for (int i = 0; i < _rozgrywka.rozmiarMapy; i++) {
			plik << _rozgrywka.gracz1[i] << _rozgrywka.gracz2[i];
		}
		plik << _rozgrywka.walizka;

		//Zapis zmiennych steruj¹cych
		plik.write((char*)&_rozgrywka.tura, sizeof(_rozgrywka.tura));
		plik.write((char*)&_rozgrywka.ruchWalizkaWykonany, sizeof(_rozgrywka.ruchWalizkaWykonany));
		plik.write((char*)&_rozgrywka.czyjaTura, sizeof(_rozgrywka.czyjaTura));

		plik.close();
	}
	else {
		throw Blad_Pliku();
	}
	return *this;
}

Zapis& Zapis::operator>>(Rozgrywka& _rozgrywka)
{
	ifstream plik(nazwaPliku, ios::binary);
	if (plik) {
		//Odczyt pionków
		for (int i = 0; i < _rozgrywka.rozmiarMapy; i++) {
			plik >> _rozgrywka.gracz1[i] >> _rozgrywka.gracz2[i];
		}
		plik >> _rozgrywka.walizka;

		//Odczyt zmiennych steruj¹cych
		plik.read((char*)&_rozgrywka.tura, sizeof(_rozgrywka.tura));
		plik.read((char*)&_rozgrywka.ruchWalizkaWykonany, sizeof(_rozgrywka.ruchWalizkaWykonany));
		plik.read((char*)&_rozgrywka.czyjaTura, sizeof(_rozgrywka.czyjaTura));

		plik.close();
	}
	else {
		throw Blad_Pliku();
	}
	return *this;
}
