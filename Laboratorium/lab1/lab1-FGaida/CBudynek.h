#ifndef BUDYNEK_CLASS
#define BUDYNEK_CLASS


class CBudynek
{
private:
	char* nazwa;
	int* lata;
	int wielkoscTablicy;
	int zapelnienieTablicy;
public:
	CBudynek();
	CBudynek(char* _nazwa, int* _lata, int zapelnienie);
	CBudynek(const CBudynek& ref);
	CBudynek(CBudynek&& rref);
	~CBudynek();

	void Wypisz();

};

#endif // !BUDYNEK_CLASS