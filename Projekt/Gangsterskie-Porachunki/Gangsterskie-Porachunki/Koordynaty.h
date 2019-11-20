#ifndef KOORDYNATY_CLASS
#define KOORDYNATY_CLASS

class Koordynaty
{
public:
	enum Kierunek { N, NE, E, SE, S, SW, W, NW, NILL };

	int x;
	int y;

	Koordynaty();
	Koordynaty(int _x, int _y);
	~Koordynaty();

	static Kierunek KierunekZStr(const char* kierunekStr);

	Koordynaty operator+(Kierunek kierunekRuchu);
	Koordynaty& operator+=(Kierunek kierunekRuchu);

};

#endif // !KOORDYNATY_CLASS