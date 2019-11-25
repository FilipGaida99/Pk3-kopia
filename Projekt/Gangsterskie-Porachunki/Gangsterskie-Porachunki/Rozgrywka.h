#ifndef ROZGRYWKA_CLASS
#define ROZGRYWKA_CLASS

#include "Pionek.h"
#include "Walizka.h"
#include "Gangster.h"
#include "Zapis.h"

//Komendy wyrzucane jako wyj¹tki podczas sprawdzania u¿ycia komend
enum Komenda { Zapisz_Graj, Zapisz_Wyjdz, Wyjdz, Brak };

class Rozgrywka
{
private:
	const int rozmiarMapy;

	//Zmienne steruj¹ce kolejnoœci¹ ruchu po wczytaniu gry
	Przynaleznosc czyjaTura;
	bool ruchWalizkaWykonany;
	int tura;

	//Mapa jako dwuwymiarowa tablica wskaŸników na pionek mapa[Y][X]
	Pionek*** mapa;
	//WskaŸnik na walizke
	Walizka* walizka;
	//Tablice przechowuj¹ce wskaŸniki na pionki danego gracza
	Gangster** gracz1;
	Gangster** gracz2;

	//Zmienna steruj¹ca sposobem rozpoczêcia gry
	bool czyRozpoczacZPliku;
	//Obiekt przechowuj¹cy aktualny plik zapisu oraz udostêpniaj¹cy go
	Zapis plikZapisu;
	//ZaprzjaŸnione operatory przypisania
	friend Zapis& Zapis::operator<<(const Rozgrywka& _rozgrywaka);
	friend Zapis& Zapis::operator>>(Rozgrywka& _ropzgrywka);
	
	//Metoda czyszcz¹ca pozosta³e znaki z bufora
	void WyczyscBufor() const;
	//Metoda usuwaj¹ca wa¿noœæ wielkoœcio liter przez ustawienie wszystkich na wielkie
	char* UsunWielkoscLiter(char* str) const;
	//Metoda koñczy siê wyrzuceniem wyj¹tku w przypadku wyst¹pienia komendy
	void SprawdzUzycieKomendy(const char* strWejsciowy) const;
	//Metoda sprawdza czy gracz bêdzie w stanie poruszyæ którymkolwiek z gangsterów
	bool CzyGangsterzySaZablokowani(Gangster** gangsterzyGracza) const;
	//Metoda bêd¹ca interfejsem wykonwywania ruchu dla danego gracza
	Przynaleznosc WykonajTure(Przynaleznosc czyjaTura, Gangster** gangsterzyGracza);
	//Metoda wypisuj¹ca zwyciêzce na podstawie wyniku tury
	bool SprobujOglosicZwyciezce(Przynaleznosc wynikTury) const;
	//Metoda porusza pionkiem w kierunku odczytanym ze strumienia wejœciowego
	bool PoruszWWprowadzonymKierunku(Pionek* wybranyPionek);
	//Funckja wybiera gangstera na podstawie danych ze strumenia wejœciowego
	Gangster* WybierzGangstera(Gangster** gangsterzyGracza);
public:
	//Konstruktory i destruktory
	Rozgrywka() = delete;
	Rozgrywka(int ileArg, const char* argWierszaPolecen[]);
	~Rozgrywka();

	//Metoda rozpoczynaj¹ca grê
	void Rozpocznij();
	//Metoda wykonuj¹ca naprzemiennie turê gracza pierwszego i drugiego
	bool PetlaGry();
	//Funckja wypisuj¹ca aktualn¹ mapê
	//Parametr czyjeWyswietlic informuje pionki o tym kto wykonuje turê
	void WyswietlMape(Przynaleznosc czyjeWyswietlic = Neutralny) const;
};

#endif // !ROZGRYWKA_CLASS