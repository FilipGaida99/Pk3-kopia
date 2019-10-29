// PK3-lab2-2019.cpp : Defines the entry point for the console application.
//


#include <string.h>
#include <iostream>
using namespace std;


class CBudynek
{
	char* nazwa; // nazwa
	int* lata; //  lata kontroli budynku
	int dl, zap; // d³ugoœæ i zape³nienie tablicy
	double wys; // wysokosc UWAGA NOWY ELEMENT OD lab1

public:

	CBudynek();
	CBudynek(const char* _nazwa, const double _wys);
	CBudynek(const CBudynek & o);
	~CBudynek();
	void wypisz();



	// zad 2
	// Dodaj 3 prze³adowane operatory porównuj¹ce dwa obiekty klasy
	bool operator==(const CBudynek& o);
	bool operator!=(const CBudynek& o);
	bool operator>(const CBudynek& o);


	// zad 3
	//Dodaj prze³adowany operator przypisania
	// Dodaj 
	//		cout << "Uruchomienie operatora przypisania" << endl;
	CBudynek& operator=(const CBudynek& o);



	// zad 4
	// Dodaj prze³adowany operator przeniesienia 
		// Dodaj 
	//		cout << "Uruchomienie operatora przeniesienia - dziala z move " << endl;
	CBudynek& operator=(CBudynek&& o);


	// zad 5
	// Dodaj prze³adowany operator ‘+=’ (int) dodaj¹cy do tablicy lata zadan¹ wartoœæ
	CBudynek& operator+=(int nowyRok);

	//zad 6
	// Dodaj prze³adowane operatory pre- i post- inkrementacji ( ‘++’), zwiêkszaj¹ce wysokoœæ o 1. (Zwróæ uwagê na ró¿nice w definicjach.)
	CBudynek& operator++();
	CBudynek operator++(int);

	// zad 7
	// Dodaj prze³adowane operator indeksowania, zwracaj¹cy i-ty element tablicy. 
	// (Zwróæ uwagê, aby wartoœæ „i” mieœci³a siê w zakresie tablicy. W przeciwnym razie zwróæ -1)
	int operator[](const int index);



	// zad 8
	// Dodaj prze³adowane operator rzutowania (konwersji) na double, zwracaj¹cy wysokoœæ.

	operator double();
};

// =====================================================================================================================
// zad 1.
CBudynek::CBudynek() : dl(0), zap(0), lata(NULL), wys(0)
{
	cout << "Jestem K. bezarg" << endl;
	nazwa = new char[2];
	strcpy_s(nazwa, 2, "X");
};


// konstruktor dwuargumentowy
CBudynek::CBudynek(const char* _nazwa, const double _wys) :dl(2), zap(0), wys(_wys), nazwa(new char[strlen(_nazwa)+1])
{
	cout << "Jestem K. dwuarg" << endl;
	//nazwa = // uzupe³nij - zaalokuj pamiêæ 
					// i przekopiuj nazwê
	strcpy(nazwa, _nazwa);
	//lata = // uzupe³nij - zaalokuj pamiêæ
	lata = new int[dl];
};


// konstruktor kopiuj¹cy

CBudynek::CBudynek(const CBudynek & o) :dl(o.dl), zap(o.zap), lata(new int[o.dl]), wys(o.wys), nazwa(new char[strlen(o.nazwa)+1])
{
	cout << "Jestem K. kopiujacy" << endl;
	//nazwa = // uzupe³nij - zaalokuj pamiêæ 
					// i przekopiuj nazwêê
	strcpy(nazwa, o.nazwa);

	for (int i = 0; i < o.zap; i++)
		lata[i] = o.lata[i];

};



CBudynek::~CBudynek()
{
	if (nazwa)
	{
		cout << "Destruktor. Usuwam: " << nazwa << endl;
		delete[] nazwa;
	}
	else
		cout << "Destruktor" << endl;

	if (lata)
		delete[] lata;
}


void CBudynek::wypisz()
{
	cout << nazwa << endl << wys << endl << zap << endl;
	for (int i = 0; i < zap; i++)
		cout << lata[i] << endl;

	cout << endl;
}

bool CBudynek::operator==(const CBudynek & o)
{
	return (strcmp(nazwa, o.nazwa)==0) && (wys < o.wys+0.0000001) && (wys > o.wys - 0.0000001);
}

bool CBudynek::operator!=(const CBudynek & o)
{
	return !(*this==o);
}

bool CBudynek::operator>(const CBudynek & o)
{
	return wys>o.wys;
}

CBudynek & CBudynek::operator=(const CBudynek & o)
{
	cout << "Uruchomienie operatora przypisania" << endl;
	if (this == &o) {
		return *this;
	}

	if (nazwa) {
		delete[] nazwa;
	}
	if (lata) {
		delete[] lata;
	}
	nazwa = new char[strlen(o.nazwa) + 1];
	strcpy(nazwa, o.nazwa);
	lata = new int[o.dl];
	for (int i = 0; i < o.zap; i++) {
		lata[i] = o.lata[i];
	}
	dl = o.dl;
	zap = o.zap;
	wys = o.wys;
	return *this;
}

CBudynek & CBudynek::operator=(CBudynek && o)
{
	cout << "Uruchomienie operatora przeniesienia - dziala z move " << endl;
	if (this == &o) {
		return *this;
	}
	char* pc = nazwa;
	nazwa = o.nazwa;
	o.nazwa = pc;
	int* pi = lata;
	lata = o.lata;
	o.lata = pi;

	dl = o.dl;
	zap = o.zap;
	wys = o.wys;

	return *this;
}

CBudynek & CBudynek::operator+=(int nowyRok)
{
	if(dl==zap){
		int* noweLata = new int[dl * 2];
		for (int i = 0; i < zap; i++) {
			noweLata[i] = lata[i];
		}
		delete[] lata;
		lata = noweLata;
		dl *= 2;
	}
	lata[zap++] = nowyRok;
	return *this;
}

CBudynek & CBudynek::operator++()
{
	wys++;
	return *this;
}

CBudynek CBudynek::operator++(int)
{
	CBudynek temp = *this;
	wys++;

	return temp;
}

int CBudynek::operator[](const int index)
{
	if (index < 0 || index >= zap) {
		return -1;
	}
	return lata[index];
}

CBudynek::operator double()
{
	return wys;
}




// =====================================================================================================================
// =====================================================================================================================

int main()
{
	cout << "\n zad 1" << endl;
	CBudynek ob0("dom", 205.6), ob1("ob", 205.6), ob2("ob", 205.6), ob3("ob3", 604.4), ob4;


	ob0.wypisz();
	ob1.wypisz();
	ob2.wypisz();
	ob3.wypisz();
	ob4.wypisz();


	////=============================================================
	cout << "\n zad 2" << endl;
	cout << (ob1 == ob2) << endl << (ob1 != ob0) << endl << (ob1 > ob2) << endl;  // odpowiedzi: T, T, F



	////=============================================================
	cout << "\n zad 3" << endl;
	ob0 = ob0;
	ob4 = ob3;


	////=============================================================
	cout << "\n zad 4" << endl;
	ob0 = move(ob0);
	ob4 = move(ob0);

	////=============================================================
	cout << "\n zad 5" << endl;
	ob4.wypisz();
	ob4 += 2019;
	ob4.wypisz();



	////=============================================================
	cout << "\n zad 6" << endl;
	cout << "Postinkrementacja" << endl;
	CBudynek ob5 = ob4++;	
	ob4.wypisz();
	ob5.wypisz();

	cout << "Preinkrementacja" << endl;
	ob5 = ++ob4;
	ob4.wypisz();
	ob5.wypisz();


	////=============================================================
	cout << "\n zad 7" << endl;
	double y = ob4[0];  //
	cout << "y = " << y << " (powinno byc 2019)" << endl; 
	y = ob4[-1];
	cout << "y = " << y << " (powinno byc -1)" << endl;
	y = ob4[100];
	cout << "y = " << y << " (powinno byc -1)" << endl;


	//////=============================================================
	cout << "\n zad 8" << endl;
	double w = double(ob4);  //  
	cout << "wys = " << w << " (powinno byc 207.6)" << endl;


	cout << endl;
	cout << "KONIEC" << endl << endl;


	return 0;
}

