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
	Gangster();
	Gangster(char _znakWyswietlany, int _pozycjaX, int _pozycjaY, Przynaleznosc _gracz, int _id);
	~Gangster();

	bool WykonajRuch(Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) override;
	char WyswietlZnak(Przynaleznosc czyjeWyswietlic) override;
};

#endif // !GANGSTER_CLASS