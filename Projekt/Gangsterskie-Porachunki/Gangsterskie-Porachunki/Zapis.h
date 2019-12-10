#ifndef ZAPIS_CLASS
#define ZAPIS_CLASS

#include <fstream>
#include "Pionek.h"
#include "Gangster.h"

//Do³¹czenie klasy Rozgrywka bez zapêtlenia #include.
class Rozgrywka;
//Klasa wyj¹tku, do wyrzucania b³êdu otwarcia pliku.
class Blad_Pliku {};

class Zapis
{
private:
	static constexpr char domyslnaNazwaPliku[] = "Zapis.dat";
	char* nazwaPliku;

public:
	//Konstruktory i destruktory
	Zapis();
	Zapis(const char* _nazwaPliku);
	~Zapis();

	//Operator przenosz¹cy do zmieniania aktualnie œledzonego pliku zapisu
	Zapis& operator=(Zapis&& rZapis);
	//Operator do zapisywania rozgrywki
	Zapis& operator<<(const Rozgrywka& _rozgrywka);
	//Operator do wczytywania rozgrywki
	Zapis& operator>>(Rozgrywka& _rozgrywka);
};
#endif //!ZAPIS_CLASS