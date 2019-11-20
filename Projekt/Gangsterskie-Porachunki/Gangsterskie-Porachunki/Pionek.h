#ifndef PIONEK_CLASS
#define PIONEK_CLASS

#include "Koordynaty.h"

enum Przynaleznosc { Pierwszy, Drugi, Neutralny };

class Pionek
{

private:
	char znakWyswietlany;

	bool CzyMoznaPrzejscNaPozycje(int pozycjaDocelowaX, int pozycjaDocelowaY, Pionek*** aktualnaMapa, const int rozmiarMapy) const;
	bool CzyMoznaPrzejscNaPozycje(Koordynaty& pozycjaDocelowa, Pionek*** aktualnaMapa, const int rozmiarMapy) const;

protected: 
	Koordynaty pozycja;
public:
	Pionek() = delete;
	Pionek(char _znakWyswietlany, int _pozycjaX, int _pozycjaY);
	virtual ~Pionek();

	int PozycjaX() const;
	int PozycjaY() const;

	bool CzyJestZablokowany(Pionek*** aktualnaMapa, const int rozmiarMapy) const;
	bool PoruszOJednoPole(Koordynaty::Kierunek kierunekRuchu,  Pionek*** aktualnaMapa, const int rozmiarMapy);
	virtual bool WykonajRuch(Koordynaty::Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) = 0;
	virtual char WyswietlZnak(Przynaleznosc czyjeWyswietlic) const;

};

#endif // !PIONEK_CLASS