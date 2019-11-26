#include "Rozgrywka.h"

#include <iostream>
#include <string.h>
#include "Koordynaty.h"

using namespace std;

void Rozgrywka::WyczyscBufor() const
{
	char pozostalosc;
	do {
		pozostalosc = getchar();
	} while (pozostalosc != '\n' && pozostalosc != EOF);
}

char * Rozgrywka::UsunWielkoscLiter(char * str) const
{
	if (str == nullptr) {
		return nullptr;
	}
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

void Rozgrywka::SprawdzUzycieKomendy(const char * strWejsciowy) const
{
	Komenda komendaWejsciowa = Brak;
	if (!strcmp(strWejsciowy, "WY")) {
		komendaWejsciowa = Wyjdz;
	}
	else if (!strcmp(strWejsciowy, "ZW")) {
		komendaWejsciowa = Zapisz_Wyjdz;
	}
	else if (!strcmp(strWejsciowy, "Z")) {
		komendaWejsciowa = Zapisz_Graj;
	}
	if (komendaWejsciowa != Brak) {
		throw komendaWejsciowa;
	}
}

bool Rozgrywka::CzyGangsterzySaZablokowani(Gangster ** gangsterzyGracza) const
{
	for (int i = 0; i < rozmiarMapy; i++) {
		if (!gangsterzyGracza[i]->CzyJestZablokowany(mapa, rozmiarMapy)) {
			return false;
		}
	}
	return true;
}

Przynaleznosc Rozgrywka::WykonajTure(Przynaleznosc czyjaTura, Gangster ** gangsterzyGracza)
{
	//Pierwsza czêœæ tury, ruch walizk¹
	if (!ruchWalizkaWykonany) {
		WyswietlMape();
		if (walizka->CzyJestZablokowany(mapa, rozmiarMapy)) {
			cout << "Walizka zablokowana" << endl;
			return czyjaTura == Pierwszy ? Drugi : Pierwszy;
		}
		cout << "Podaj kierunek ruchu walizka: ";
		while (!PoruszWWprowadzonymKierunku(walizka)) {
			cout << "Walizka nie moze poruszyc sie w tym kierunku. Podaj nowy kierunek: ";
		}

		//Sprawdzenie czy walizka nie przesz³a na czyjeœ pole startowe
		{
			Przynaleznosc ktoPrzechwycilWalizke = walizka->NaCzyjejStronie(rozmiarMapy);
			if (ktoPrzechwycilWalizke != Neutralny) {
				return ktoPrzechwycilWalizke;
			}
		}
	}
	ruchWalizkaWykonany = true;

	//Druga czêœæ tury, ruch wybranym gangsterem
	if (CzyGangsterzySaZablokowani(gangsterzyGracza)) {
		cout << "Wszyscy gangsterzy zablokowani" << endl;
		return czyjaTura == Pierwszy ? Drugi : Pierwszy;
	}

	WyswietlMape(czyjaTura);
	while (true) {
		Gangster* wybranyGangster;
		wybranyGangster = WybierzGangstera(gangsterzyGracza);
		cout << "Podaj Kierunek ruchu: ";
		if (!PoruszWWprowadzonymKierunku(wybranyGangster)) {
			cout << "Wybrany gangster nie moze poruszyc sie w tym kierunku.\nSprobuj ponownie" << endl;
		}
		else {
			break;
		}
	}
	WyswietlMape();
	ruchWalizkaWykonany = false;
	return Neutralny;
}

bool Rozgrywka::SprobujOglosicZwyciezce(Przynaleznosc wynikTury) const
{
	switch (wynikTury)
	{
	case Pierwszy:
		cout << "\n\nWygral gracz pierwszy!\n\n";
		break;
	case Drugi:
		cout << "\n\nWygral gracz drugi!\n\n";
		break;
	case Neutralny:
	default:
		return false;
	}
	return true;
}

bool Rozgrywka::PoruszWWprowadzonymKierunku(Pionek * wybranyPionek)
{
	constexpr int rozmiarDanychWejsciowych = 4;
	char* daneWejsciowe = new char[rozmiarDanychWejsciowych];
	Koordynaty::Kierunek kierunekRuchu;
	while (true) {
		cin.getline(daneWejsciowe, rozmiarDanychWejsciowych - 1);
		//Sprawdzenie czy nie wprowadzono pustego ci¹gu
		if (daneWejsciowe[0] == '\0') {
			continue;
		}

		UsunWielkoscLiter(daneWejsciowe);
		try {
			SprawdzUzycieKomendy(daneWejsciowe);
			kierunekRuchu = Koordynaty::KierunekZStr(daneWejsciowe);
			if (kierunekRuchu != Koordynaty::NILL) {
				break;
			}
			cout << "Podano niepoprawna wartosc. Podaj N, NE, E, SE, S, SW, W, NW: ";
			WyczyscBufor();
			cin.clear();
		}
		//Obs³uga komend
		catch (Komenda uzytaKomedna) {
			switch (uzytaKomedna)
			{
			case Zapisz_Graj:
				plikZapisu << *this;
				cout << "Gra zostala zapisana. Kontynuuj wprowadzanie Kierunku: ";
				break;
			case Zapisz_Wyjdz:
				plikZapisu << *this;
			case Wyjdz:
				delete[] daneWejsciowe;
				throw uzytaKomedna;
			default:
				break;
			}
		}
	}

	delete[] daneWejsciowe;
	return wybranyPionek->WykonajRuch(kierunekRuchu, mapa, rozmiarMapy);;
}

Gangster * Rozgrywka::WybierzGangstera(Gangster ** gangsterzyGracza)
{
	cout << "Wybierz gangstera: ";
	int numerPionka;
	while (true) {
		cin >> numerPionka;
		if (cin.fail() || numerPionka < 1 || numerPionka > rozmiarMapy) {
			cout << "Wybrano nieprawidlowa liczbe. Wybierz od 1 do " << rozmiarMapy << ": ";
			WyczyscBufor();
			cin.clear();
			continue;
		}
		WyczyscBufor();
		break;
	}
	return gangsterzyGracza[--numerPionka];
}

Rozgrywka::Rozgrywka(int ileArg, const char* argWierszaPolecen[]): rozmiarMapy(5), czyjaTura(Pierwszy), ruchWalizkaWykonany(false), tura(1), mapa(new Pionek**[rozmiarMapy]), walizka(nullptr),
																   gracz1(new Gangster*[rozmiarMapy]), gracz2(new Gangster*[rozmiarMapy]), czyRozpoczacZPliku(false)
{
	if (ileArg >= 3) {
		plikZapisu = move(Zapis(argWierszaPolecen[2]));
		if (!strcmp(argWierszaPolecen[1], "-in")) {
			czyRozpoczacZPliku = true;
		}
	}
	for (int i = 0; i < rozmiarMapy; i++) {
		mapa[i] = new Pionek*[rozmiarMapy];
		for (int j = 0; j < rozmiarMapy; j++) {
			mapa[i][j] = nullptr;
		}

		gracz1[i] = gracz2[i] = nullptr;
	}
}

Rozgrywka::~Rozgrywka()
{
	if(walizka) delete walizka;
	for (int i = 0; i < rozmiarMapy; i++) {
		if(mapa[i]) delete[] mapa[i];
		if(gracz1[i]) delete gracz1[i];
		if(gracz2[i]) delete gracz2[i];
	}
	if(mapa) delete[] mapa;
	if(gracz1) delete[] gracz1;
	if(gracz2) delete[] gracz2;
}

void Rozgrywka::Rozpocznij()
{
	if (czyRozpoczacZPliku) {
		plikZapisu >> *this;
	}
	else {
		const int polowaRozmiaruMapy = (rozmiarMapy / 2);
		for (int i = 0; i < rozmiarMapy; i++) {
			mapa[i][0] = gracz1[i] = new Gangster('O', 0, i, Pierwszy, i);
			mapa[i][rozmiarMapy - 1] = gracz2[i] = new Gangster('X', rozmiarMapy - 1, i, Drugi, i);
		}
		mapa[polowaRozmiaruMapy][polowaRozmiaruMapy] = walizka = new Walizka(polowaRozmiaruMapy, polowaRozmiaruMapy);
	}
}

bool Rozgrywka::PetlaGry()
{
	
	cout << "Tura: " << tura << endl;
	if (czyjaTura != Drugi) {
		cout << "Tura gracza pierwszego" << endl;
	}
	if (czyjaTura == Drugi || !SprobujOglosicZwyciezce(WykonajTure(Pierwszy, gracz1))) {
		cout << "\n\n\n\n\n\n\n\n";
		cout << "Tura gracza drugiego" << endl;
		czyjaTura = Drugi;
		if (!SprobujOglosicZwyciezce(WykonajTure(Drugi, gracz2))) {
			czyjaTura = Pierwszy;
			tura++;
			cout << "\n\n\n\n\n\n\n\n";
			return true;
		}
	}
	WyswietlMape();
	
	return false;
}

void Rozgrywka::WyswietlMape(Przynaleznosc czyjeWyswietlic) const
{
	for (int i = 0; i < rozmiarMapy; i++) {
		for (int j = 0; j < rozmiarMapy; j++) {
			cout << ' ';
			if (mapa[i][j]) {
				cout << mapa[i][j]->WyswietlZnak(czyjeWyswietlic);
			}
			else {
				cout << '.';
			}
			cout << ' ';
		}
		cout << endl;
	}
}
