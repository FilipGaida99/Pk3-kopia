#ifndef ROZGRYWKA_CLASS
#define ROZGRYWKA_CLASS

#include "Pionek.h"
#include "Walizka.h"
#include "Gangster.h"
#include "Zapis.h"

//Komendy wyrzucane jako wyjπtki podczas sprawdzania uøycia komend.
enum Komenda { Zapisz_Graj, Zapisz_Wyjdz, Wyjdz, Brak };

class Rozgrywka
{
private:
	const int rozmiarMapy;

	Przynaleznosc czyjaTura;
	bool ruchWalizkaWykonany;
	int tura;

	//Mapa jako dwuwymiarowa tablica wskaünikÛw na pionek mapa[Y][X].
	Pionek*** mapa;
	Walizka* walizka;
	//Tablice przechowujπce wskaüniki na pionki danego gracza.
	Gangster** gracz1;
	Gangster** gracz2;

	bool czyRozpoczacZPliku;
	Zapis plikZapisu;
	friend Zapis& Zapis::operator<<(const Rozgrywka& _rozgrywaka);
	friend Zapis& Zapis::operator>>(Rozgrywka& _ropzgrywka);
	

	void WyczyscBufor() const;
	char* UsunWielkoscLiter(char* str) const;
	void SprawdzUzycieKomendy(const char* strWejsciowy) const;
	bool CzyGangsterzySaZablokowani(Gangster** gangsterzyGracza) const;
	Przynaleznosc WykonajTure(Przynaleznosc czyjaTura, Gangster** gangsterzyGracza);
	bool PoruszWWprowadzonymKierunku(Pionek* wybranyPionek);
	Gangster* WybierzGangstera(Gangster** gangsterzyGracza);
public:
	Rozgrywka() = delete;
	Rozgrywka(int ileArg, const char* argWierszaPolecen[]);
	~Rozgrywka();

	bool Rozpocznij();
	bool PetlaGry();
	bool SprobujOglosicZwyciezce(Przynaleznosc wynikTury) const;
	void WyswietlMape(Przynaleznosc czyjeWyswietlic = Neutralny) const;
};

#endif // !ROZGRYWKA_CLASS