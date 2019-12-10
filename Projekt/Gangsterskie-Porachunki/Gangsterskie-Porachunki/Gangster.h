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

	//Metoda definiuj¹ca jak ma zostaæ wykonany ruch (ruch o jedno pole)
	bool WykonajRuch(Koordynaty::Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) override;
	//Metoda decyduj¹ca o wyœwietlanym znaku
	char WyswietlZnak(Przynaleznosc czyjeWyswietlic) const override;
	//Metoda s³u¿aca do zapisu klasy binarnego
	virtual bool Zapisz(std::ofstream& plik) const override;
	//Metoda s³u¿¹ca do odczytu klasy z pliku binarnego
	virtual bool Wczytaj(std::ifstream& plik) override;
};

#endif // !GANGSTER_CLASS