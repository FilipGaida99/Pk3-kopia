#ifndef KOORDYNATY_CLASS
#define KOORDYNATY_CLASS

class Koordynaty
{
public:
	enum Kierunek { N, NE, E, SE, S, SW, W, NW, NILL };

	int x;
	int y;

	//Konstruktory i destruktory
	Koordynaty();
	Koordynaty(int _x, int _y);
	~Koordynaty();

	//Metoda zwraca kierunek na podstawie dowolnego ciągu znaków zakończonego '\0'
	static Kierunek KierunekZStr(const char* kierunekStr);

	//Operator przesuwający koordynaty zgodnie z kierunkiem
	Koordynaty operator+(Kierunek kierunekRuchu);
	//Operator przesuwający koordynaty zgodnie z kierunkiem
	Koordynaty& operator+=(Kierunek kierunekRuchu);

};

#endif // !KOORDYNATY_CLASS