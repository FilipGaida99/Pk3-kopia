
#include <iostream>
#include "CBudynek.h"
int main()
{
	CBudynek ob1;
	CBudynek ob2{ ob1 };
	int* tab = new int[3];
	tab[0] = 1;
	tab[1] = 2;
	tab[2] = 3;
	char napis[] = "Gliwice";
	CBudynek objarg = CBudynek(napis,tab,3 );
	objarg.Wypisz();
	CBudynek*ob3 = &ob1;
	CBudynek* ob4 = new CBudynek{ ob1 };
	CBudynek ob40(std::move(ob2));
	delete ob4;
}
