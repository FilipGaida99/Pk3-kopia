#ifndef ROZGRYWKA_CLASS
#define ROZGRYWKA_CLASS

#include "Pionek.h"
#include "Walizka.h"
#include "Gangster.h"
#include "Zapis.h"

//Komendy wyrzucane jako wyj�tki podczas sprawdzania u�ycia komend
enum Komenda { Zapisz_Graj, Zapisz_Wyjdz, Wyjdz, Brak };

class Rozgrywka
{
private:
	const int rozmiarMapy;

	//Zmienne steruj�ce kolejno�ci� ruchu po wczytaniu gry
	Przynaleznosc czyjaTura;
	bool ruchWalizkaWykonany;
	int tura;

	//Mapa jako dwuwymiarowa tablica wska�nik�w na pionek mapa[Y][X]
	Pionek*** mapa;
	//Wska�nik na walizke
	Walizka* walizka;
	//Tablice przechowuj�ce wska�niki na pionki danego gracza
	Gangster** gracz1;
	Gangster** gracz2;

	//Zmienna steruj�ca sposobem rozpocz�cia gry
	bool czyRozpoczacZPliku;
	//Obiekt przechowuj�cy aktualny plik zapisu oraz udost�pniaj�cy go
	Zapis plikZapisu;
	//Zaprzja�nione operatory przypisania
	friend Zapis& Zapis::operator<<(const Rozgrywka& _rozgrywaka);
	friend Zapis& Zapis::operator>>(Rozgrywka& _ropzgrywka);
	
	//Metoda czyszcz�ca pozosta�e znaki z bufora
	void WyczyscBufor() const;
	//Metoda usuwaj�ca wa�no�� wielko�cio liter przez ustawienie wszystkich na wielkie
	char* UsunWielkoscLiter(char* str) const;
	//Metoda ko�czy si� wyrzuceniem wyj�tku w przypadku wyst�pienia komendy
	void SprawdzUzycieKomendy(const char* strWejsciowy) const;
	//Metoda sprawdza czy gracz b�dzie w stanie poruszy� kt�rymkolwiek z gangster�w
	bool CzyGangsterzySaZablokowani(Gangster** gangsterzyGracza) const;
	//Metoda b�d�ca interfejsem wykonwywania ruchu dla danego gracza
	Przynaleznosc WykonajTure(Przynaleznosc czyjaTura, Gangster** gangsterzyGracza);
	//Metoda wypisuj�ca zwyci�zce na podstawie wyniku tury
	bool SprobujOglosicZwyciezce(Przynaleznosc wynikTury) const;
	//Metoda porusza pionkiem w kierunku odczytanym ze strumienia wej�ciowego
	bool PoruszWWprowadzonymKierunku(Pionek* wybranyPionek);
	//Funckja wybiera gangstera na podstawie danych ze strumenia wej�ciowego
	Gangster* WybierzGangstera(Gangster** gangsterzyGracza);
public:
	//Konstruktory i destruktory
	Rozgrywka() = delete;
	Rozgrywka(int ileArg, const char* argWierszaPolecen[]);
	~Rozgrywka();

	//Metoda rozpoczynaj�ca gr�
	void Rozpocznij();
	//Metoda wykonuj�ca naprzemiennie tur� gracza pierwszego i drugiego
	bool PetlaGry();
	//Funckja wypisuj�ca aktualn� map�
	//Parametr czyjeWyswietlic informuje pionki o tym kto wykonuje tur�
	void WyswietlMape(Przynaleznosc czyjeWyswietlic = Neutralny) const;
};

#endif // !ROZGRYWKA_CLASS