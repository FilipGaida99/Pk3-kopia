#include "Rozgrywka.h"
#include <iostream>

using namespace std;

int main(int ileArg, const char* arg[])
{
	try {
		Rozgrywka rozgrywka{ ileArg, arg };

		rozgrywka.Rozpocznij();
		while (rozgrywka.PetlaGry());
	}
	catch (Blad_Pliku) {
		cout << "Nie udalo sie otworzyc pliku z zapisem." << endl;
	}
	catch (Komenda) {
		cout << "Wyjscie z gry." << endl;
	}
	catch (...) {
		cout << "Nie oczekiwany blad. Sprobuj ponownie." << endl;
	}

	cout << "Nacisnij dowolny klawisz by zakonczyc" << endl;
	getchar();

    return 0;
}

