#include "CBudynek.h"
#include <iostream>
#include <cstring>

using namespace std;

CBudynek::CBudynek(): nazwa(new char[strlen("Eiffla") + 1]), lata(nullptr), wielkoscTablicy(100), zapelnienieTablicy(0)
{
	cout << "konstrktor domyslny\n";
	strcpy(nazwa, "Eiffla");
}

CBudynek::CBudynek(char * _nazwa, int * _lata, int zapelnienie): nazwa(new char[strlen(_nazwa) + 1]), lata(_lata), wielkoscTablicy(2*zapelnienie), zapelnienieTablicy(zapelnienie)
{
	cout << "konstrktor arg\n";
	strcpy(nazwa, _nazwa);
}

CBudynek::CBudynek(const CBudynek & ref):nazwa(new char[strlen(ref.nazwa) + 1]), lata(new int[ref.wielkoscTablicy]), wielkoscTablicy(ref.wielkoscTablicy), zapelnienieTablicy(ref.zapelnienieTablicy)
{
	cout << "konstrktor kopiujacy\n";
	strcpy(nazwa, ref.nazwa);
	for (int i = 0; i < zapelnienieTablicy; i++) {
		lata[i] = ref.lata[i];
	}
}

CBudynek::CBudynek(CBudynek && rref): nazwa(rref.nazwa), lata(rref.lata), wielkoscTablicy(rref.wielkoscTablicy), zapelnienieTablicy(rref.zapelnienieTablicy)
{
	cout << "kontruktor przenoszacy\n";
	rref.nazwa = nullptr;
	rref.lata = nullptr;
}


CBudynek::~CBudynek()
{
	cout << "destruktor\n";
	if(nazwa) delete[] nazwa;
	if(lata) delete lata;
}

void CBudynek::Wypisz()
{
	cout << "Nazwa: " << nazwa << "\n";
	cout << "Lata kontroli:\n";
	for (int i = 0; i < zapelnienieTablicy; i++) {
		cout <<lata[i]<<"\n";
	}
}
