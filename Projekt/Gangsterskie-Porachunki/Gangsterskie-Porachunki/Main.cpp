#include "Rozgrywka.h"
#include <iostream>

//#include "vld.h"

using namespace std;

int main(int ileArg, const char* arg[])
{
	Rozgrywka rozgrywka{ ileArg, arg };
	try {
		rozgrywka.Rozpocznij();
		while (rozgrywka.PetlaGry());
	}
	catch (Blad_Pliku) {
		cout << "Nie udalo sie otworzyc pliku z zapisem." << endl;
	}
	catch (Komenda) {
		cout << "Konczenie dzialania gry." << endl;
	}
	catch (...) {
		cout << "Nie oczekiwany blad. Sprobuj ponownie." << endl;
	}
    return 0;
}

