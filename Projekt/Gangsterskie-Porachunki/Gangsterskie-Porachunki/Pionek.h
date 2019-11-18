#ifndef PIONEK_CLASS
#define PIONEK_CLASS

enum Przynaleznosc { Pierwszy, Drugi, Neutralny };

class Pionek
{
public:
	enum Kierunek{N, NE, E, SE, S, SW, W, NW, NILL};
	
private:
	char znakWyswietlany;

	bool CzyMoznaPrzejscNaPozycje(int pozycjaDocelowaX, int pozycjaDocelowaY, Pionek*** aktualnaMapa, const int rozmiarMapy);
	
protected: 
	int pozycjaX;
	int pozycjaY;
public:
	Pionek() = delete;
	Pionek(char _znakWyswietlany, int _pozycjaX, int _pozycjaY);
	virtual ~Pionek();

	int PozycjaX();
	int PozycjaY();
	bool CzyJestZablokowany(Pionek*** aktualnaMapa, const int rozmiarMapy);
	void UzyskajNowaPozycje(int& pozycjaX, int& pozycjaY, Kierunek kierunekRuchu);
	bool PoruszOJednoPole(Kierunek kierunekRuchu,  Pionek*** aktualnaMapa, const int rozmiarMapy);
	virtual bool WykonajRuch(Kierunek kierunekRuchu, Pionek*** aktualnaMapa, const int rozmiarMapy) = 0;
	virtual char WyswietlZnak(Przynaleznosc czyjeWyswietlic);

	static Kierunek KierunekZStr(const char* kierunekStr);
};

#endif // !PIONEK_CLASS