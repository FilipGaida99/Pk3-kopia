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

	//Metoda zwraca kierunek na podstawie dowolnego ci¹gu znaków zakoñczonego '\0'
	static Kierunek KierunekZStr(const char* kierunekStr);

	//Operator przesuwaj¹cy koordynaty zgodnie z kierunkiem
	Koordynaty operator+(Kierunek kierunekRuchu);
	//Operator przesuwaj¹cy koordynaty zgodnie z kierunkiem
	Koordynaty& operator+=(Kierunek kierunekRuchu);

};

#endif // !KOORDYNATY_CLASS