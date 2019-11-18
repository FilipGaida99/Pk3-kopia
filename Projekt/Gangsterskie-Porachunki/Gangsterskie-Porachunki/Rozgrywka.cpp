#include "Rozgrywka.h"
#include <iostream>

using namespace std;

void Rozgrywka::WyczyscBufor()
{
	char pozostalosc;
	do {
		pozostalosc = getchar();
	} while (pozostalosc != '\n' && pozostalosc!=EOF);
}

char * Rozgrywka::UsunWielkoscLiter(char * str)
{
	if (str == nullptr) {
		return nullptr;
	}
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

void Rozgrywka::SprawdzUzycieKomendy(const char * strWejsciowy)
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

bool Rozgrywka::CzyGangsterzySaZablokowani(Gangster ** gangsterzyGracza)
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

		//Sprawdzenie czy walizka nie przesz�a na czyje� pole startowe
		{
			Przynaleznosc ktoPrzechwycilWalizke = walizka->NaCzyjejStronie(rozmiarMapy);
			if (ktoPrzechwycilWalizke != Neutralny) {
				return ktoPrzechwycilWalizke;
			}
		}
	}
	ruchWalizkaWykonany = true;

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

bool Rozgrywka::PoruszWWprowadzonymKierunku(Pionek * wybranyPionek)
{
	constexpr int rozmiarDanychWejsciowych = 4;
	char* daneWejsciowe = new char[rozmiarDanychWejsciowych];
	Pionek::Kierunek kierunekRuchu;
	while (true) {
		cin.getline(daneWejsciowe, rozmiarDanychWejsciowych - 1);
		//Sprawdzenie czy nie wprowadzono pustego ci�gu
		if (daneWejsciowe[0] == '\0') {
			continue;
		}

		UsunWielkoscLiter(daneWejsciowe);
		try {
			SprawdzUzycieKomendy(daneWejsciowe);
			kierunekRuchu = Pionek::KierunekZStr(daneWejsciowe);
			if (kierunekRuchu != Pionek::NILL) {
				break;
			}
			cout << "Podano niepoprawna wartosc. Podaj N, NE, E, SE, S, SW, W, NW: ";
			WyczyscBufor();
			cin.clear();
		}
		//Obs�uga komend
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

Rozgrywka::Rozgrywka(int ileArg, const char* argWierszaPolecen[]): rozmiarMapy(5), mapa(new Pionek**[rozmiarMapy]), tura(1), czyRozpoczacZPliku(false)
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
	}
	gracz1 = new Gangster*[rozmiarMapy];
	gracz2 = new Gangster*[rozmiarMapy];
}

Rozgrywka::~Rozgrywka()
{
	delete walizka;
	for (int i = 0; i < rozmiarMapy; i++) {
		delete[] mapa[i];
		delete gracz1[i];
		delete gracz2[i];
	}
	delete[] mapa;
	delete[] gracz1;
	delete[] gracz2;
}

bool Rozgrywka::Rozpocznij()
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
	return true;
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
			plikZapisu << *this;
			cout << "\n\n\n\n\n\n\n\n";
			return true;
		}
	}
	WyswietlMape();
	
	return false;
}

bool Rozgrywka::SprobujOglosicZwyciezce(Przynaleznosc wynikTury)
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

void Rozgrywka::WyswietlMape(Przynaleznosc czyjeWyswietlic)
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
