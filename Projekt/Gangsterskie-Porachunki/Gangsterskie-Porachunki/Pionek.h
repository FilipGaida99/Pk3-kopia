#ifndef PIONEK_CLASS
#define PIONEK_CLASS

#include "Koordynaty.h"

enum Przynaleznosc { Pierwszy, Drugi, Neutralny };

class Pionek
{

private:
	//Znak wyœwietlany podczas wyœwietlania mapy (mo¿e byæ pomijany przez funkcje w klasach potomnych)
	char znakWyswietlany;

	//Funkcja zwraca true gdy na wskazanej pozycji nie ma pionka 
	bool CzyMoznaPrzejscNaPozycje(int pozycjaDocelowaX, int pozycjaDocelowaY, Pionek*** aktualnaMapa, const int rozmiarMapy) const;
	bool CzyMoznaPrzejscNaPozycje(Koordynaty& pozycjaDocelowa, Pionek*** aktualnaMapa, const int rozmiarMapy) const;

protected: 
	Koordynaty pozycja;

	//Funkcja porusza pionkiem o jedno pole, wykorzystywane przez klasy potomne do definicji ruchu
	bool PoruszOJednoPole(Koordynaty::Kierunek kierunekRuchu,  Pionek*** aktualnaMapa, const int rozmiarMapy);

public:
	//Konstruktory i destruktory
	Pionek() = delete;
	Pionek(char _znakWyswietlany, int _pozycjaX, int _pozycjaY);
	virtual ~Pionek();

	//Getter pozycji x
	int PozycjaX() const;
	//Getter pozycji y
	int PozycjaY() const;

	//Zwraca true gdy pionek nie ma gdzie siê ruszyæ
	bool CzyJestZablokowany(Pionek*** aktualnaMapa, const int rozmiarMapy) const;
	//Funkcja definiuj¹ca jak ma zostaæ wykonany ruch
	virtual bool WykonajRuch(Koordynaty::Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) = 0;
	//Funkcja decyduj¹ca o wyœwietlanym znaku
	virtual char WyswietlZnak(Przynaleznosc czyjeWyswietlic) const;

};

#endif // !PIONEK_CLASS