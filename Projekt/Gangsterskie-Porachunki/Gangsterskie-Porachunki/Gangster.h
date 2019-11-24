#ifndef GANGSTER_CLASS
#define GANGSTER_CLASS

#include "Pionek.h"


class Gangster :
	public Pionek
{
private:
	Przynaleznosc czyjJest;
	int id;
public:
	//Konstruktory i destruktory
	Gangster();
	Gangster(char _znakWyswietlany, int _pozycjaX, int _pozycjaY, Przynaleznosc _gracz, int _id);
	~Gangster();

	//Funkcja definiuj¹ca jak ma zostaæ wykonany ruch (ruch o jedno pole)
	bool WykonajRuch(Koordynaty::Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) override;
	//Funkcja decyduj¹ca o wyœwietlanym znaku
	char WyswietlZnak(Przynaleznosc czyjeWyswietlic) const override;
};

#endif // !GANGSTER_CLASS