// PK3-lab5-2019.cpp : Defines the entry point for the console application.
//
// Programowanie Komputerów 3  (Jolanta Kawulok)
// Laboratorium 5 (Dziedziczenie wielobazowe) 
// 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;


class CZwierze
{
public:
	string nazwa;
	double pred;
	virtual void zjedz() = 0;

	// Wstaw w odpowiednie miejsce
	//cout << "K. domyslny CZwierze" << endl;
	//cout << "K. 2arg CZwierze, par: " << nazwa.c_str() << ", " << pred << endl; 
	//cout << "Destruktor CZwierze, par: " << nazwa.c_str() << ", " << pred << endl;
	CZwierze() {
		cout << "K. domyslny CZwierze" << endl;
	}

	CZwierze(string _nazwa, double _pred) : nazwa(_nazwa), pred(_pred) {
		cout << "K. 2arg CZwierze, par: " << nazwa.c_str() << ", " << pred << endl;
	}

	virtual ~CZwierze() {

		cout << "Destruktor CZwierze, par: " << nazwa.c_str() << ", " << pred << endl;
	}
};



//cout << "K. domyslny CSsak: " << nazwa.c_str() << ", " << pred << endl;
//cout << "K. 2arg CSsak, par: " << nazwa.c_str() << ", " << pred << endl;
//cout << "Destruktor CSsak, par: " << nazwa.c_str() << ", " << pred << endl;

class CSsak : virtual CZwierze 
{
public:
	int waga;
	void zjedz() {
		cout << "Ssak " << nazwa.c_str() << "je." << endl;
	}

	CSsak() {
		nazwa = "DSsak";
		pred = 1;
		waga = 999;
		cout << "K. domyslny CSsak: " << nazwa.c_str() << ", " << pred << endl;

	}

	CSsak(string _nazwa, double _pred) {
		nazwa = _nazwa;
		pred = _pred;
		waga = 999;
		cout<< "K. 2arg CSsak, par: " << nazwa.c_str() << ", " << pred << endl;
	}

	~CSsak() {
		cout << "Destruktor CSsak, par: " << nazwa.c_str() << ", " << pred << endl;
	}

};


class CPtak: virtual CZwierze
{
	int waga;
public:
	
	void zjedz() {
		cout << "Ptak " << nazwa.c_str() << "je"<< endl;
	}

	CPtak(): CZwierze("DPtak", 2.0), waga(999) {
		cout << "K. domyslny CPtak: " << nazwa.c_str() << ", " << pred << endl;
	}

	CPtak(string _nazwa, double _pred): CZwierze(_nazwa, _pred), waga(999) {
		cout << "K. 2arg CPtak, par: " << nazwa.c_str() << ", " << pred << endl;
	}

	~CPtak() {
		cout << "Destruktor CPtak, par: " << nazwa.c_str() << ", " << pred << endl;
	}

};

//cout << "K. domyslny CPtak: " << nazwa.c_str() << ", " << pred << endl;
//cout << "K. 2arg CPtak, par: " << nazwa.c_str() << ", " << pred << endl;
//cout << "Destruktor CPtak, par: " << nazwa.c_str() << ", " << pred << endl;



//cout << "K. domyslny CNietoperz" << endl;
//cout << "Destruktor CNietoperz" << endl;

class CNietoperz : public CSsak, public CPtak, virtual CZwierze {
public:

	CNietoperz() {
		cout << "K. domyslny CNietoperz" << endl;
	}

	CNietoperz(string _nazwa, double _pred) : CSsak(_nazwa,_pred), CPtak(_nazwa, _pred) {
		cout << "Konstruktor Nietoperz 2 arg:" << _nazwa<<" , " << _pred << endl;
	}

	~CNietoperz() {
		cout << "Destruktor CNietoperz" << endl;
	}

	void zjedz() {

	}
};








// #########################################################################################################
// #########################################################################################################
// #########################################################################################################

int main()
{
	cout << "==== zad_1 ====" << endl;
	////  1.5 Odkomentuj w pliku tworzenie obiektów. Zwróć uwagę na wyświetlane pytania.
	{
	CSsak s;
	CSsak s2("slon", 20);
	cout << endl;
	}
	{
	cout << "\n..............." << endl;
	CPtak p0a;
	CPtak p0b("koliber", 79);
	cout << endl;
	}
	cout << "\n..............." << endl;
	cout << "!!!! PRZYPATRZ SIE PARAMETROM POWYZSZYCH KONST. DOMYSLNYM I DESTRUKTOROM DLA CSSAK A PTAK !!!!" << endl << endl;



	cout << "\n... Sprawdzenie destruktora ... \n";
//	CZwierze* wskp0 = new CPtak;
//	delete wskp0;
	cout << "...\n\n";





	cout << "\n**********************************" << endl;
	{
	cout << "**** Dla zad 1.4.  oraz dla zad 3 ****" << endl;
	CNietoperz n ;

	}
	cout << "\t!!!! PRZYPATRZ SIE POWYZSZYM KONST. DOMYSLNYM DLA NIETOPERZA !!!!" << endl;
	cout << "\tJakie sa wartosci domyslne??? " << endl;
	cout << "\n**********************************" << endl << endl ;





	cout << "==== zad_2 ====" << endl;
	CNietoperz n0;
	//n0.zjedz(); Dodać metodę zjedz(). 
	n0.CSsak::zjedz();
	n0.CPtak::zjedz();

	//ZAD3
	//a.Zwierze, ssak, zwierze, ptak, nietoperz
	//b. Zwierze, ssak, zwierze, ptak, nietoperz
	//c. zwierze, zwierze, ssak, ptak, nietoperz i jest wypełniona śmieciami
	//d. zwierze ssak, ptak, nietoprzez i jest Dssakiem

	//ZAD4
	//n0.waga
	//Nie rozwiązuje ponieważ Klasa posiada 2 pola o takiej samej nazwie, więc wymagane jest użycie przestrzei nazw.

	cout << "\n\n==== zad_5 ====" << endl;
	cout << "CZwierze " << sizeof(CZwierze) << endl;
	cout << "CSsak " << sizeof(CSsak) << endl;
	cout << "CPtak " << sizeof(CPtak) << endl;
	cout << "CNietoperz " << sizeof(CNietoperz) << endl;
	//a 48 56 56 112
	//b 48 64 56 120
	//c 48 56 64 120
	//d 48 64 64 72

	cout << "\n\n==== zad_6 ====" << endl;
	/*{
	CNietoperz n("gacek", 112);
	}
	cout << "======" << endl;*/
	//ZAD6
	//a domyslny ssak ptak nietoperz.
	//b domyslny zwierze, ssak, zwierze, ptak nietoperz.
	//c virtual SSak zwierze, ssak, zwierze, ptak nietoperz.
	//c virtual Ptak  zwierze, zwierze ssaka, ssak, ptak, nietoperz
	//CNietoperz n1("Nietoperz", 0);

	cout << "\n\n==== zad_7 ====" << endl;
		{
	CZwierze* wsk = new CNietoperz; 
	delete wsk;
	}  
	//Gdy CZwierze virtual nie można przypisać
	//Gdy jest public wywołuje się normalnie i jest 2 razy konstuktor Czwierze


	cout << "\n\nKONIEC" << endl << endl;

	return 0;
}
