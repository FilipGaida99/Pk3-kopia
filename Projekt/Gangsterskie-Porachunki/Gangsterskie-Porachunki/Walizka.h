#ifndef WALIZKA_CLASS
#define WALIZKA_CLASS

#include "Pionek.h"
class Walizka :
	public Pionek
{
public:
	Walizka();
	Walizka(int _pozycjaX, int _pozycjaY);
	~Walizka();

	bool WykonajRuch(Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) override;
	Przynaleznosc NaCzyjejStronie(int rozmiarMapy);
};

#endif // !WALIZKA_CLASS