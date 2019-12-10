#include "Gangster.h"

using namespace std;
using Kierunek = Koordynaty::Kierunek;

Gangster::Gangster(): Gangster('E', -1, -1, Neutralny, -1)
{
}

Gangster::Gangster(char _znakWyswietlany, int _pozycjaX, int _pozycjaY, Przynaleznosc _gracz, int _id): Pionek(_znakWyswietlany, _pozycjaX, _pozycjaY), czyjJest(_gracz), id(_id)
{
}


Gangster::~Gangster()
{
}

bool Gangster::WykonajRuch(Kierunek kierunekRuchu, Pionek *** aktualnaMapa, const int rozmiarMapy)
{
	return PoruszOJednoPole(kierunekRuchu, aktualnaMapa, rozmiarMapy);
}

char Gangster::WyswietlZnak(Przynaleznosc czyjeWyswietlic) const
{
	if (czyjeWyswietlic == czyjJest) {
		return id + '1';
	}
	return Pionek::WyswietlZnak(czyjeWyswietlic);
}

bool Gangster::Zapisz(ofstream& plik) const
{
	if (!Pionek::Zapisz(plik)) {
		return false;
	}
	plik.write((const char*)&czyjJest, sizeof(Przynaleznosc));
	plik.write((const char*)&id, sizeof(int));
	return true;
}

bool Gangster::Wczytaj(ifstream& plik)
{
	if (!Pionek::Wczytaj(plik)) {
		return false;
	}
	plik.read((char*)&czyjJest, sizeof(Przynaleznosc));
	plik.read((char*)&id, sizeof(int));
	return true;
}
