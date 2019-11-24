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

	//Funkcja definiuj¹ca jak ma zostaæ wykonany ruch (ruch do blokady)
	bool WykonajRuch(Koordynaty::Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) override;
	//Funkcja sprawdzaj¹ca czy gra zosta³a zakoñczona przez przejêcie walizki
	Przynaleznosc NaCzyjejStronie(int rozmiarMapy) const;
};

#endif // !WALIZKA_CLASS