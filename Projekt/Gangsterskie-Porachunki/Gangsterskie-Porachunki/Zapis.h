#ifndef ZAPIS_CLASS
#define ZAPIS_CLASS

#include <fstream>
#include "Pionek.h"
#include "Gangster.h"

//Do��czenie klasy Rozgrywka bez zap�tlenia #include.
class Rozgrywka;
//Klasa wyj�tku, do wyrzucania b��du otwarcia pliku.
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

	//Operator przenosz�cy do zmieniania aktualnie �ledzonego pliku zapisu
	Zapis& operator=(Zapis&& rZapis);
	//Operator do zapisywania rozgrywki
	Zapis& operator<<(const Rozgrywka& _rozgrywka);
	//Operator do wczytywania rozgrywki
	Zapis& operator>>(Rozgrywka& _rozgrywka);
};
#endif //!ZAPIS_CLASS