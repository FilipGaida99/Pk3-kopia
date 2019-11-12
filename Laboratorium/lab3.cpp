// PK3-lab3-2019.cpp : Defines the entry point for the console application. 
// Programowanie Komputerów 3 12.11.2019 (Jolanta Kawulok)
// Laboratorium 3 (Dziedziczenie: aspekty statyczne) 
// 

#include <iostream>
using namespace std;


//=========================================================================================================================
// ============================================ klasa CMeble ==============================================================
//=========================================================================================================================

class CMeble {

	char* nazwa;
	double wys, szer, gl;

	//zad 5
	static int liczba;


public:

	// zad 1 a
	CMeble(const char* _nazwa, double _wys, double _szer, double _gl): nazwa(new char[strlen(_nazwa) + 1]), wys(_wys), szer(_szer), gl(_gl)
	{
		cout << "Jestem K. wieloargumentowy CMeble" << endl;
		// ... uzupelnij
		strcpy(nazwa, _nazwa);

		//zad. 5
		liczba++;
	}

	// zad 1 b) kopiuj¹cy
	//cout << "Jestem K. kopiujacy CMeble" << endl;
	CMeble(const CMeble& mebel) : nazwa(new char[strlen(mebel.nazwa) + 1]), wys(mebel.wys), szer(mebel.szer), gl(mebel.gl)
	{
		cout << "Jestem K. kopiujacy CMeble" << endl;
		strcpy(nazwa, mebel.nazwa);

		//zad. 5
		liczba++;
	}

	// zad 1 c) przenosz¹cy
	//cout << "Jestem K. przenoszacy CMeble" << endl;
	CMeble(CMeble && rmebel) :wys(rmebel.wys), szer(rmebel.szer), gl(rmebel.gl)
	{
		cout << "Jestem K. przenoszacy CMeble" << endl;

		nazwa = rmebel.nazwa;
		rmebel.nazwa = nullptr;

		//zad. 5
		liczba++;
	}

	// zad 1 d) destruktor	//
	virtual ~CMeble()
	{
		if (nazwa)
		{ 
			cout << "Jestem destruktor CMeble: " << nazwa << endl;
			delete[] nazwa;
		}
		else
			cout << "Jestem destruktor CMeble: " << endl;

		//zad. 5
		liczba--;

	}

	// zad 1 e) Stwórz operator przypisania
	CMeble & operator=(const CMeble & mebel) {
		cout << "Jestem operator przypisania CMeble" << endl;

		if (this == &mebel)
			return *this;
		else
		{
			delete[] nazwa;
			nazwa = new char[strlen(mebel.nazwa) + 1];
			strcpy(nazwa, mebel.nazwa);
			wys = mebel.wys;
			szer = mebel.szer;
			gl = mebel.gl;
		}
		cout << "Jestem operator przypisania CMeble" << endl;

	}

	// zad 1 f) Stwórz zaprzyjaŸniony operator<< s³u¿¹cy do wypisania wartoœci pól prywatnych
	friend ostream & operator<<(ostream & s, const CMeble & ob);


	static void ilenas() {
		cout << "Jest " << liczba << " mebli" << endl;
	}

};

ostream & operator<<(ostream & s, const CMeble & mebel)
{
	s << "Nazwa: " << mebel.nazwa << ", szer: " << mebel.szer << ", wys: " << mebel.wys << ", gl: " << mebel.gl;
	return s;
}


//  Napisz klasê CKrzesla, która jest publiczn¹ pochodn¹ klasy CMeble. 
//=========================================================================================================================
// ============================================ klasa CKrzesla ============================================================
//=========================================================================================================================

class CKrzesla : public CMeble {
// a)	
	int numerWzoru;
public:
	
// b)
//cout << "Jestem K. wieloarg CKrzesla" << endl;
//cout << "Jestem K. kopiujacy CKrzesla" << endl;
//cout << "Jestem K. przenoszacy CKrzesla" << endl;
//cout << "Jestem destruktor CKrzesla" << endl;
	CKrzesla(const char* _nazwa, int x, int y, int z, int _numer) :CMeble(_nazwa, x, y, z), numerWzoru(_numer) {
		cout << "Jestem K. wieloarg CKrzesla" << endl;
	}


	CKrzesla(const CKrzesla & krzeslo) :CMeble(krzeslo), numerWzoru(krzeslo.numerWzoru) {
		cout << "Jestem K. kopiuj¹cy CKrzesla" << endl;
	}

	CKrzesla(CKrzesla && krzeslo) :CMeble(move(krzeslo)), numerWzoru(krzeslo.numerWzoru) {
		cout << "Jestem K. przenoszacy CKrzesla" << endl;

	}
	~CKrzesla()
	{
		cout << "Jestem destruktor CKrzesla" << endl;

	}

// c) 
//cout << "Jestem operator przypisania CKrzesla" << endl;

	CKrzesla& operator=(const CKrzesla & krzeslo)
	{
		cout << "Jestem operator przypisania CKrzesla" << endl;
		if (this == &krzeslo)
			return *this;

		CMeble::operator=(krzeslo);
		numerWzoru = krzeslo.numerWzoru;
		return *this;


	}

// d)  ZaprzyjaŸniony operator<< s³u¿¹cy do wypisania wartoœci pól prywatnych


	friend ostream & operator<<(ostream & s, const CKrzesla & krzeslo);

};



ostream & operator<<(ostream & s, const CKrzesla & krzeslo)
{
	s << *dynamic_cast<const CMeble*>(&krzeslo) << ", numer wzoru: " << krzeslo.numerWzoru;
	return s;
}

//zad. 5
int CMeble::liczba = 0;





//  Napisz klasê CTaborety, która jest publiczn¹ pochodn¹ klasy CKrzesla. 
//=========================================================================================================================
// ============================================ klasa CTaborety ============================================================
//=========================================================================================================================

class CTaborety : public CKrzesla {
	// a)
	char* nazwaMaterialu;

public:
	
	// b)
//cout << "Jestem K. kopiujacy CTaborety" << endl;
//cout << "Jestem K. przenoszacy CTaborety" << endl;
//cout << "Jestem destruktor CTaborety" << endl;
//cout << "Jestem operator przypisania CTaborety" << endl;
	CTaborety(const char* nazwa, int x, int y, int z, int _num, const char* mat) :CKrzesla(nazwa, x, y, z, _num), nazwaMaterialu(new char[strlen(mat) + 1])
	{
		cout << "Jestem K. wieloarg CTaborety" << endl;
		strcpy(nazwaMaterialu, mat);
	};


	CTaborety(const CTaborety & taboret) :CKrzesla(taboret), nazwaMaterialu(new char[strlen(taboret.nazwaMaterialu) + 1]){
		cout << "Jestem K. kopiuj¹cy CTaborety" << endl;

		strcpy(nazwaMaterialu, taboret.nazwaMaterialu);
	};


	CTaborety(CTaborety && rtaboret) :CKrzesla(move(rtaboret)) {

		cout << "Jestem K. przenoszacy CTaborety" << endl;
		nazwaMaterialu = rtaboret.nazwaMaterialu;
		rtaboret.nazwaMaterialu = nullptr;

	};

	~CTaborety() {
		cout << "Jestem destruktor CTaborety" << endl;
		if (nazwaMaterialu)
			delete[] nazwaMaterialu;
	}


	CTaborety& operator=(const CTaborety & taboret)
	{
		cout << "Jestem operator przypisania CTaborety" << endl;
		if (this == &taboret)
			return *this;

		nazwaMaterialu = new char[strlen(taboret.nazwaMaterialu) + 1];
		strcpy(nazwaMaterialu, taboret.nazwaMaterialu);
		return *this;


	}
//ZaprzyjaŸniony operator<< s³u¿¹cy do wypisania wartoœci pól prywatnych
	friend ostream & operator<<(ostream & s, const CTaborety & ob);

};

ostream & operator<<(ostream & s, const CTaborety & taboret)
{
	s << *dynamic_cast<const CKrzesla*>(&taboret) << ", nazwa materialu: " << taboret.nazwaMaterialu;
	return s;
}








int main()
{
	//zad. 5
	CMeble::ilenas();

	cout << "zad_1" << endl;
	// zad 1 g) Poka¿ tworzenie nowego obiektu statycznie i dynamicznie, wraz z wyœwietlaniem pól.
	CMeble m1("komoda", 80, 120, 40);
	cout << "m1: " << m1 << endl;
	// dynamicznie
	CMeble* m2 = new CMeble("szafa", 200, 60, 40);
	cout << "m2: " << m2 << endl; // czy sie wyswietla?


	{
		CMeble m3 = move(m1);
		cout << "m3: " << m3 << endl;
	}



	cout << "\n\nzad_2" << endl;
	// zad 2 	e) Uruchom tworzenie nowego obiektu, 
	 CKrzesla k1a("male_krzeslo", 30, 25, 25, 1234);
	 CKrzesla k1b("duze_krzeslo", 50, 30, 30, 4444);

	// Skopiuj k2 z k1a
	 CKrzesla k2(k1a);
	cout << "k2: " << k2 << endl;


	//// Przenieœ k3 z k1a
	CKrzesla k3=move(k1a);
	//
	//{
	//	// Przypisz k4 z k1b
		CKrzesla k4 = k1b;
		cout << "k4: " << k4 << endl;
	//



	cout << "\n\nzad_3" << endl;
	// zad 3 c) Uruchom tworzenie nowego obiektu, kopiowanie i przenoszenie (CTaborety)
	 CTaborety t1a("taboret_A", 40, 30, 30, 9999, "metal");
	 CTaborety t1b("taboret_B", 50, 35, 35, 9998, "drewno");
	// 	t1a = t1a;



	// Skopiuj t2 z t1a
	// .....
	 CTaborety t2(t1a);

	// Przenieœ t3 z t1a
	 CTaborety t3=move(t1a);

	// Przypisz t4 z t1b
	// ....
	 CTaborety t4 = t1b;


	 cout << "t2: " << t2 << endl;
	 cout << "t4: " << t4 << endl;



	cout << "\n\nzad_4" << endl;
	// zad 4
	// Tablica wzkaznikow na 3 obikety dynamicznie stworzone
	// CMeble("mebel dod", 10, 10, 10);
	// CKrzesla("krzeslo dod", 20, 20, 20, 999);
	// CTaborety("taboret dod", 30, 30, 30, 333, "brzoza");
	

	CMeble ** tab = new CMeble*[3];
	tab[0] = new CMeble("mebel dod", 10, 10, 10);
	tab[1] = new CKrzesla("krzeslo dod", 20, 20, 20, 999);
	tab[2] = new CTaborety("taboret dod", 30, 30, 30, 333, "brzoza");

	//zad. 5
	CMeble::ilenas();

	for (int i = 0; i < 3; i++) {
		cout << *tab[i] << endl;
	}

	for (int i = 0; i < 3; i++) {
		delete tab[i];
	}
	
	delete[] tab;

	//zad. 5
	CMeble::ilenas();

	cout << "\n\nKONIEC" << endl;

	delete m2;

	return 0;
}
