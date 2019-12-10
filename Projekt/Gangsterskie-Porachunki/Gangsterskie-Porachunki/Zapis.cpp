#include "Zapis.h"
#include <string.h>
#include "Rozgrywka.h"

using namespace std;

constexpr char Zapis::domyslnaNazwaPliku[];

template<class T>
void Zapis::OdczytajKlaseZBin(std::ifstream & plik, T ** ptrDoWczytania, Pionek *** mapa) const
{
	T tymczasowy;
	if (Pionek* pionek = dynamic_cast<Pionek*>(&tymczasowy)) {
		plik >> pionek;
		mapa[tymczasowy.PozycjaY()][tymczasowy.PozycjaX()] = *ptrDoWczytania = new T(tymczasowy);
	}
}

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
		for (int i = 0; i < _rozgrywka.rozmiarMapy; i++) {
			plik << _rozgrywka.gracz1[i] << _rozgrywka.gracz2[i];
		}
		plik << _rozgrywka.walizka;
		plik.write((char*)&_rozgrywka.tura, sizeof(int));
		plik.write((char*)&_rozgrywka.ruchWalizkaWykonany, sizeof(bool));
		plik.write((char*)&_rozgrywka.czyjaTura, sizeof(Przynaleznosc));

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
		for (int i = 0; i < _rozgrywka.rozmiarMapy; i++) {
			OdczytajKlaseZBin<Gangster>(plik, &_rozgrywka.gracz1[i], _rozgrywka.mapa);
			OdczytajKlaseZBin<Gangster>(plik, &_rozgrywka.gracz2[i], _rozgrywka.mapa);
		}
		OdczytajKlaseZBin<Walizka>(plik, &_rozgrywka.walizka, _rozgrywka.mapa);
		plik.read((char*)&_rozgrywka.tura, sizeof(int));
		plik.read((char*)&_rozgrywka.ruchWalizkaWykonany, sizeof(bool));
		plik.read((char*)&_rozgrywka.czyjaTura, sizeof(Przynaleznosc));

		plik.close();
	}
	else {
		throw Blad_Pliku();
	}
	return *this;
}
