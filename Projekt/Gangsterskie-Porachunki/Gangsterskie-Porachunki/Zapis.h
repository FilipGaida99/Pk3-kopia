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

	template <class T>
	void OdczytajKlaseZBin(std::ifstream& plik, T ** ptrDoWczytania, Pionek*** mapa);

public:
	Zapis();
	Zapis(const char* _nazwaPliku);
	~Zapis();

	Zapis& operator=(Zapis&& rZapis);
	Zapis& operator<<(const Rozgrywka& _rozgrywka);
	Zapis& operator>>(Rozgrywka& _rozgrywka);
};
#endif //!ZAPIS_CLASS