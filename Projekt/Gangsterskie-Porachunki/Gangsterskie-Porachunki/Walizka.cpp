#include "Walizka.h"

using Kierunek = Koordynaty::Kierunek;

Walizka::Walizka(): Walizka(-1, -1)
{
}

Walizka::Walizka(int _pozycjaX, int _pozycjaY): Pionek('$', _pozycjaX, _pozycjaY)
{
}


Walizka::~Walizka()
{
}

bool Walizka::WykonajRuch(Kierunek kierunekRuchu, Pionek *** aktualnaMapa, const int rozmiarMapy)
{
	bool czyUdaloSieWykonac = false;
	while (PoruszOJednoPole(kierunekRuchu, aktualnaMapa, rozmiarMapy)) {
		czyUdaloSieWykonac = true;
	}
	return czyUdaloSieWykonac;
}

Przynaleznosc Walizka::NaCzyjejStronie(int rozmiarMapy) const
{
	if (pozycja.x == 0) {
		return Pierwszy;
	}
	if (pozycja.x == rozmiarMapy - 1) {
		return Drugi;
	}
	return Neutralny;
}
