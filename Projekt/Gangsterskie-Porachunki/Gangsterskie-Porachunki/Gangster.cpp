#include "Gangster.h"



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

char Gangster::WyswietlZnak(Przynaleznosc czyjeWyswietlic)
{
	if (czyjeWyswietlic == czyjJest) {
		return id + '1';
	}
	return Pionek::WyswietlZnak(czyjeWyswietlic);
}
