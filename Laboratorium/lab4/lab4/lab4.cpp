// PK3-lab4-2019.cpp : Defines the entry point for the console application.
/* Programowanie Komputerów 3 (2019/2020)
Laboratorium 4 (Polimorfizm)
Jolanta Kawulok */

#include <iostream>

#include <string>
using namespace std;



class CKruszec
{
	double cena;  // informacja o cenie za gram materiału(zł/g) 
	double gest; //informacja o gęstości materiału(g/cm3)
	string rodzaj; // nazwa/rodzaj kruszca

public:
	virtual void meldunek()
	{
		cout << "Meld: Jestem CKruszec " << rodzaj.c_str() << endl; //
	}


	/* a) Konstruktor i destruktor
	- bezargumentowy, parametry domyślne: "wlasny", 0, 0
	- trzyargumentowy(rodzaj, cena, gest)
	- destruktor
	proszę stosować listę inicjalizacyjną
	cout << "konstruktor bezarg CKruszec " << endl; //
	cout << "konstruktor 3arg CKruszec " << rodzaj.c_str() << endl; //
	cout << "destruktor CKruszec " << rodzaj.c_str() << endl; // */

	CKruszec() : rodzaj("wlansy"), cena(0), gest(0)
	{
		cout << "konstruktor bezarg CKruszec " << endl;
	}

	CKruszec(string _rodzaj, double _cena, double _gest) : rodzaj(_rodzaj), cena(_cena), gest(_gest)
	{
		cout << "konstruktor 3arg CKruszec " << rodzaj.c_str() << endl; //
	}

	virtual ~CKruszec()
	{
		cout << "destruktor CKruszec " << rodzaj.c_str() << endl;
	}








	/*	b) Modyfikatory i akcesory dla ceny i gestosci i rodzaju */

	void SetRodzaj(string _rodzaj) {
		rodzaj = _rodzaj;
	}

	string GetRodzaj() const {
		return rodzaj;
	}

	void SetCena(double _cena) {
		cena = _cena;
	}

	double GetCena() const{
		return cena;
	}

	void SetGest(double _gest) {
		gest = _gest;
	}

	double GetGest() const{
		return gest;
	}

};


// zad 2 Abstrakcyjną klasę CSztabka, która jest publiczną pochodną klasy CKruszec
// ==============================================================================================================================
// ================================================ KLASA ABSTRAKYCYJNA CSztabka ================================================
// ==============================================================================================================================

class CSztabka :
	public CKruszec 
{
public:
	virtual double obj() = 0;

	double waga() {
		return obj() * GetGest();
	}
	double cenasztab() {
		return waga() * GetCena();
	}

	void info()
	{
		cout << "INFO: ";
		cout << "rodzaj=" << GetRodzaj();
		cout << ", obj=" << obj();
		cout << ", waga=" << waga();
		cout << ", cena za sztabke=" << cenasztab();
	    cout << endl << endl;
	}



	//Zad 5.
	static double sumwag(CSztabka** tablicaWsk, int rozmiar) {
		double suma = 0;
		for (int i = 0; i < rozmiar; i++) {
			suma += tablicaWsk[i]->waga();

		}
		cout << "Suma wg wynosi: "<<suma;
		return suma;
	}

};





// zad 3 Klasa CProstopadloscian, która jest publiczną pochodną klasy CSztabka. 
// ==============================================================================================================================
// ================================================ KLASA CProstopadloscian =====================================================
// ==============================================================================================================================
// 		cout << "destruktor CProstopadloscian " << nazob.c_str() << endl; //
// 		cout << "konstruktor CProstopadloscian " << nazob.c_str() << endl; //

class CProstopadloscian :
	public CSztabka 
{
	double a, b, c;

	string nazob;
public:
	CProstopadloscian(double _a, double _b, double _c, CKruszec& _kruszec, string nazwa): a(_a), b(_b), c(_c), nazob(nazwa)
	{
		cout << "konstruktor CProstopadloscian " << nazob.c_str() << endl;

		SetGest(_kruszec.GetGest());
		SetCena(_kruszec.GetCena());
		SetRodzaj(_kruszec.GetRodzaj());
	}

	~CProstopadloscian() {
		cout << "destruktor CProstopadloscian " << nazob.c_str() << endl;
	}

	double obj() override {
		return a * b * c;
	}

	void meldunek() override {
		cout << "Jestem prostopadloscian: " << nazob << endl;
	}

};






// zad 4 Klasa CWalec, która jest publiczną pochodną klasy CSztabka.
// ==============================================================================================================================
// ================================================ KLASA CWalec ================================================================
// ==============================================================================================================================
// 		cout << "destruktor CWalec " << nazob.c_str() << endl; //
// 		cout << "konstruktor CWalec " << nazob.c_str() << endl; //

class CWalec :
	public CSztabka {

	double h, r;
	string nazob;
public:
	CWalec(double wys, double promien, const CKruszec& _kruszec, string nazwa): h(wys), r(promien), nazob(nazwa)
	{
		cout << "konstruktor CWalec " << nazob.c_str() << endl;

		SetGest(_kruszec.GetGest());
		SetCena(_kruszec.GetCena());
		SetRodzaj(_kruszec.GetRodzaj());
	}

	~CWalec() 
	{
		cout << "destruktor CWalec " << nazob.c_str() << endl;
	}

	double obj() override 
	{
		return 3.14 * r * r * h;
	}

	void meldunek() override{
		cout << "Jestem walec : " << nazob << endl;
	}
};





// ==============================================================================================================================
// ================================================ MAIN ======= ================================================================
// ==============================================================================================================================
int main()
{
	cout << "\nzad 1" << endl;
	CKruszec mojkruszec;
	CKruszec zloto("zloto", 95, 19.3), srebro("srebro", 2, 10.5), platyna("platyna", 120, 21.1);

	/* zad 1 c) zmien dla mojkruszec: cena na 50, a gestosc na 20 */
	mojkruszec.SetCena(50);
	mojkruszec.SetGest(20);


	cout << "\nzad 3" << endl;
	CProstopadloscian obP1(10.0, 1.0, 3.0, zloto, "obP1");
	obP1.info();
	CProstopadloscian obP2(10.0, 1.0, 3.0, platyna, "obP2");
	obP2.info();
	cout << endl << endl;


	cout << "\nzad 4" << endl;
	CWalec obW1(1.5, 10, srebro, "obW1");
	obW1.info();
	CWalec obW2(1.5, 1, srebro, "obW2");
	obW2.info();




	cout << "\nzad 5" << endl;
	/* Stwórz następnie dwie tablice wskaźników (jedną statycznie, drugą dynamicznie) do obiektów stworzonych wcześniej (4 obiekty)
	i wywołaj na niej metodę zliczania sumy wag. Tablice będą zawierać te same elementy.*/
	CSztabka* tab[4] = { &obP1, &obP2, &obW1, &obW2 };
	CSztabka::sumwag(tab, 4);
	CSztabka** tabdyn = new CSztabka*[4];
	
	tabdyn[0] = &obP1;
	tabdyn[1] = &obP2;
	tabdyn[2] = &obW1;
	tabdyn[3] = &obW2;

	CSztabka::sumwag(tabdyn, 4);
	delete[] tabdyn;



	cout << "\nzad 6" << endl;
	/*a) Stwórz dynamicznie obiekt dodP klasy  CKruszec, a następnie przypisz mu nowy obiekt klasy  CProstopadloscian.
	Następnie wywołaj na niej metodę info()*/

	CKruszec* dodP= new CProstopadloscian(1, 1, 1, mojkruszec, "dodP");    // popraw/uzupełnij 

	dynamic_cast<CSztabka*>(dodP)->info();

	//*b)

	zloto.meldunek();
	obW1.meldunek();
	obP1.meldunek();
	dodP->meldunek();

	delete dodP;

	cout << endl << "KONIEC" << endl;
	
	

	return 0;
}

