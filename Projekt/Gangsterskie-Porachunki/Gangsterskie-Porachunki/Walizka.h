#ifndef WALIZKA_CLASS
#define WALIZKA_CLASS

#include "Pionek.h"
class Walizka :
	public Pionek
{
public:
	//Konstruktory i destruktory
	Walizka();
	Walizka(int _pozycjaX, int _pozycjaY);
	~Walizka();

	//Metoda definiuj�ca jak ma zosta� wykonany ruch (ruch do blokady)
	bool WykonajRuch(Koordynaty::Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) override;
	//Metoda sprawdzaj�ca czy gra zosta�a zako�czona przez przej�cie walizki
	Przynaleznosc NaCzyjejStronie(int rozmiarMapy) const;
};

#endif // !WALIZKA_CLASS